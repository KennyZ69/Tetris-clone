#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "grid.h"
#include "utils.h"

#define NUM_SHAPES 7
#define NUM_ROTATIONS 4

extern const char shapes_letters[NUM_SHAPES];
extern const char shapes[NUM_SHAPES][NUM_ROTATIONS][4][4];

typedef struct {
	int size;
	int on_grid;
	int row;
	int col;
	int locked_down;
	char shape[NUM_ROTATIONS][4][4];
} Object;

// create and return a pointer to new object for the game
Object *create_object();

// change the shape of the object setting on_grid and locked_down to false
void change_shape(Object *obj, char shape_letter);

// put given object on the grid at given row and col (form top left corner) and set on_grid to true
void put_object(Object *obj, Grid *grid, int row, int col);

#endif
