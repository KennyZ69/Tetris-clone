#ifndef CONTROLS_HEADER
#define CONTROLS_HEADER

#include "grid.h"
#include "objects.h"
#include "action.h"

// check whether the position for next oncoming object is valid and empty
int pos_check(const Grid *grid, Object *obj, int row, int col);

int act(Grid *grid, Object *obj, Actions action);

int drop_obj(Grid *grid, Object *obj);

int rotate(Grid *grid, Object *obj);

int move_obj(Grid *grid, Object *obj, Actions action);

#endif
