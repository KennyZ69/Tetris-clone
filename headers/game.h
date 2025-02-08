#ifndef GAME_HEADER
#define GAME_HEADER

#include "utils.h"
#include "grid.h"
#include "objects.h"
#include "scene.h"
#include "action.h"
#include <stdbool.h>

// typedef int bool;
// #define true 1;
// #define false 0;

#define ROWS 20
#define COLS 10
#define START_DELAY 750
#define HISTORY_SIZE 5

typedef struct {
	Grid *grid;
	Scene *scene;
	Object *curr_obj;
	uint8 score;
	uint8 lvl;
	uint8 lines;
	char next_shape;
	char next_shapes[NUM_SHAPES];
	int over;
	int paused;
	int delay;
	int next_idx;

	int hist_index;
	// Actions history[HISTORY_SIZE];
	int history[HISTORY_SIZE];
} Game;

// allocate space for initialized game and return pointer to it
Game *init_game();

// set the is_over to true and wait for user input either start a new game or quit
Actions game_over(Game *game);

void run(Game *game);

void deinit_game(Game *game);
 
void reset_game(Game *game);

void next_object(Game *game);

#endif
