#include "../headers/game.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Actions get_action(int delay);
void update_stats(Game *game);
int spawn_object(Game *game);
void pause(Game *game);
void history_act(Game *game, Actions act);

Game *init_game() {
    srand(time(NULL));

    Game *game = safe_malloc(sizeof(*game));

    char **stats = safe_malloc(sizeof(*stats) * STATS_COUNT);
    for (int i = 0; i < STATS_COUNT; i++) {
        stats[i] = safe_malloc(sizeof(*stats[0]) * STAT_LEN);
    }

    game->grid = create_grid(_ROWS, _COLS);
    game->curr_obj = create_object();
    game->scene = init_scene(game->grid, true, stats, true, STATS_COUNT);
    
    memcpy(game->next_shapes, shapes_letters, NUM_SHAPES);

    reset_game(game);

    return game;
}

void reset_game(Game *game) {
    flush_grid(game->grid);
    game->curr_obj->on_grid = false;

    game->next_idx = 0;
    next_object(game);

    game->lvl = 1;
    game->score = 0;
    game->lines = 0;
    game->delay = START_DELAY;

    set_arr(DOWN, game->history, HISTORY_SIZE);
    game->hist_index = 0;

    game->over = false;
    game->paused = false;
}

void next_object(Game *game) {
    if (game->next_idx == 0) {
        rand_arr(game->next_shapes, NUM_SHAPES);
    }

    game->next_shape = game->next_shapes[game->next_idx];
    game->next_idx = (game->next_idx + 1) % NUM_SHAPES; // increase idx for next shape
}

void run(Game *game) {
    int lines;
    Actions action;

    while (!game->over) {
        if (! game->curr_obj->on_grid) {
            if ( ! spawn_object(game)) {
                game->over = true;
                continue;
            }
        }
        update_stats(game);
        refresh_scene(game->scene);

        if (!in_arr(DOWN, game->history, HISTORY_SIZE)) {
            act(game->grid, game->curr_obj, DOWN);
            history_act(game, DOWN);
        } else {
            action = get_action(game->delay);
            if (action == PAUSE) {
                pause(game);
                continue;
            } else {
                act(game->grid, game->curr_obj, action);
                history_act(game, action);
            }
        }
        if (game->curr_obj->locked_down) {
            lines = remove_line(game); // check whether there is a line to get
            if (lines) {
                game->lines += lines;
                // increase score and levels somehow now
                inc_lvl(game);
                inc_score(game, lines);
            }
        }
    }
}

Actions game_over(Game *game) {
    Actions action;
    game->over = true;

    update_stats(game);
    refresh_scene(game->scene);

    do {
        action = get_action(-1);
    } while (action != NEW_GAME && action != QUIT);

    if (action == NEW_GAME) reset_game(game);

    return action;
}

void deinit_game(Game *game) {

    deinit_grid(game->grid);
    free(game->curr_obj);
    for (int i = 0; i < STATS_COUNT; i++) {
        free(game->scene->stats[i]);
    }
    free(game->scene->stats);

    deinit_scene(game->scene);

    free(game);
}

Actions get_action(int delay) {
    timeout(delay);

    switch (getch()) {
    case 'q':
        return QUIT;
    case KEY_UP:
    case 'k':
        return ROTATE;
    case KEY_DOWN:
    case 'j':
        return DOWN;
    case KEY_LEFT:
    case 'h':
        return LEFT;
    case KEY_RIGHT:
    case 'l':
        return RIGHT;
    case ' ':
        return DROP;
    case 'p':
        return PAUSE;
    case 'n':
        return NEW_GAME;
    case 'x':
        return END_GAME;
    default:
        return DOWN;
    }
}

void update_stats(Game *game) {
    snprintf(game->scene->stats[0], STAT_LEN, "Score: %u", game->score);
    snprintf(game->scene->stats[1], STAT_LEN, "Level: %u", game->lvl);
    snprintf(game->scene->stats[2], STAT_LEN, "Lines: %u", game->lines);
    snprintf(game->scene->stats[3], STAT_LEN, "\n");
    snprintf(game->scene->stats[4], STAT_LEN, "Next: %c", game->next_shape);
    snprintf(game->scene->stats[5], STAT_LEN, "\n");

    if (game->paused || game->over) {
        if (game->paused) {
            snprintf(game->scene->stats[6], STAT_LEN, "Game is PAUSED!");
            snprintf(game->scene->stats[7], STAT_LEN, "Press 'p' to continue or 'x' to end current game");
        } else {
            snprintf(game->scene->stats[6], STAT_LEN, "GAME OVER!");
            snprintf(game->scene->stats[7], STAT_LEN, "Press 'n' for new game or 'q' to quit");
        }
    } else {
        snprintf(game->scene->stats[6], STAT_LEN, "\n");
        snprintf(game->scene->stats[7], STAT_LEN, "\n");
    }
}

int spawn_object(Game *game) {
    set_arr(DOWN, game->history, HISTORY_SIZE);

    change_shape(game->curr_obj, game->next_shape);

    game->curr_obj->row = 0;
    game->curr_obj->col = game->grid->cols / 2 - game->curr_obj->size / 2; // find the middle

    if (!pos_check(game->grid, game->curr_obj, game->curr_obj->row, game->curr_obj->col)) {
        return false;
    }

    put_object(game->grid, game->curr_obj, game->curr_obj->row, game->curr_obj->col);
    next_object(game);
    return true;
}

void history_act(Game *game, Actions action) {
    game->history[game->hist_index] = action;
    game->hist_index = (game->hist_index + 1) % HISTORY_SIZE;
}

void pause(Game *game) {
    game->paused = true;

    update_stats(game);
    refresh_scene(game->scene);

    Actions action;

    do {
        action = get_action(-1);
    } while (action != PAUSE && action != END_GAME);

    if (action == END_GAME) {
        game->over = true;
    }
    game->paused = false;
}

int remove_line(Game *game) {
    int lines = 0;

    for (int i = 0; i < game->grid->rows; i++) {
        if (is_row(game->grid, i)) {
            flush_row(game->grid, i);
            lines++;
            for (int j = i; j > 0; j--) {
                move_row_down(game->grid, j, j - 1);
            }
        }
    }
    return lines;
}

void inc_lvl(Game *game) {
    int lvl = (game->lines / 10) + 1;

    if (lvl <= game->lvl) return;

    game->lvl = lvl;

    if (game->delay > 200) {
        game->delay -= 100;
    } else if (game->delay > 150){
        game->delay -= 5;
    }
}

void inc_score(Game *game, int lines) {
    int points = 0;

    // give points to player based on how many rows at once they got 
    switch (lines) {
        case 1:
            points = 40;
            break;
        case 2:
            points = 240;
            break;
        case 3:
            points = 840;
            break;
        case 4:
            points = 1040;
            break;
        default:
            break;
    }

    game->score += points * (game->lvl + 1);
}
