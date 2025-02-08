#include "../headers/game.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Game *init_game() {
    srand(time(NULL));

    Game *game = safe_malloc(sizeof(*game));

    game->grid = create_grid(ROWS, COLS);
    game->curr_obj = create_object();
    game->scene = init_scene(game->grid);
    
    memcpy(game->next_shapes, shapes_letters, NUM_SHAPES);

    reset_game(game);

    return game;
}

void reset_game(Game *game) {
    flush_grid(game->grid);
    game->curr_obj->on_grid = false;

    game->next_idx = 0;
    // update next shape

    game->lvl = 1;
    game->score = 0;
    game->lines = 0;
    game->delay = START_DELAY;

    game->hist_index = 0;

    game->over = false;
    game->paused = false;
}

void next_object(Game *game) {
    if (game->next_idx == 0) {
        // TODO:
        // randomize the next shapes arr
    }

    game->next_shape = game->next_shapes[game->next_idx];
    game->next_idx = (game->next_idx + 1) % NUM_SHAPES; // increase idx for next shape
}
