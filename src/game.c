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
            lines = remove_line(game);
            if (lines) {
                game->lines += lines;
                // increase score and levels somehow now
            }
        }
    }
    return;
}

Actions game_over(Game *game) {
    Actions act;
    game->over = true;

    refresh_scene(game->scene);

    do {
        act = get_action(-1);
    } while (act != NEW_GAME && act != QUIT);

    if (act == NEW_GAME) reset_game(game);

    return act;
}

void deinit_game(Game *game) {

    free(game->curr_obj);
    free(game->scene->stats);

    deinit_grid(game->grid);
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
            snprintf(game->scene->stats[7], STAT_LEN, "Press 'p' to continue or 'q' to quit");
        } else {
            snprintf(game->scene->stats[6], STAT_LEN, "GAME OVER!");
            snprintf(game->scene->stats[7], STAT_LEN, "Press 'n' for new game or 'q' to quit");
        }
    } else {
        snprintf(game->scene->stats[6], STAT_LEN, "\n");
        snprintf(game->scene->stats[7], STAT_LEN, "\n");
    }
}

void update_next_shape(Game *game) {
    if (game->next_idx == 0) {
        rand_arr(game->next_shapes, NUM_SHAPES);
    }
    game->next_shape = game->next_shapes[game->next_idx];
    game->next_idx = (game->next_idx + 1) % NUM_SHAPES;
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
    update_next_shape(game);
    return true;
}

void history_act(Game *game, Actions act) {
    game->history[game->hist_index] = act;
    game->hist_index = (game->hist_index + 1) % HISTORY_SIZE;
}

void pause(Game *game) {
    game->paused = !game->paused;

    update_stats(game);
    refresh_scene(game->scene);

    Actions act;

    do {
        act = get_action(-1);
    } while (act != PAUSE || act != QUIT);

    if (act == QUIT) {
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
                move_row_down(game->grid, i, j - 1);
            }
        }
    }
    return lines;
}
