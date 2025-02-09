#include "../headers/game.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Actions get_action(int delay);
void update_stats(Game *game);

Game *init_game() {
    srand(time(NULL));

    Game *game = safe_malloc(sizeof(*game));

    char **stats = safe_malloc(sizeof(*stats) * STATS_COUNT);
    for (int i = 0; i < STATS_COUNT; i++) {
        stats[i] = safe_malloc(sizeof(*stats[0]) * STAT_LEN);
    }

    game->grid = create_grid(_ROWS, _COLS);
    // game->curr_obj = create_object();
    game->scene = init_scene(game->grid, true, stats, true, STATS_COUNT);
    
    memcpy(game->next_shapes, shapes_letters, NUM_SHAPES);

    reset_game(game);

    return game;
}

void reset_game(Game *game) {
    flush_grid(game->grid);
    // game->curr_obj->on_grid = false; // WARN: This ends in a segfault because curr_obj hasn't been initialized yet

    game->next_idx = 0;
    next_object(game);

    game->lvl = 1;
    game->score = 0;
    game->lines = 0;
    game->delay = START_DELAY;

    game->hist_index = 0;

    game->over = false;
    game->paused = false;
}

void next_object(Game *game) {
    // if (game->next_idx == 0) {
    //     // TODO:
    //     // randomize the next shapes arr
    // }

    game->next_shape = game->next_shapes[game->next_idx];
    game->next_idx = (game->next_idx + 1) % NUM_SHAPES; // increase idx for next shape
}

void run(Game *game) {
    // int lines;
    // printf("Running the game\n");

    while (!game->over) {
        update_stats(game);
        refresh_scene(game->scene);

        Actions act = get_action(game->delay);
        if (act == PAUSE) {
            game->paused = !game->paused;
        }
    }
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
