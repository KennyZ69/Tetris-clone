#include "../headers/controls.h"
#include <ncurses.h>
#include <stdbool.h>

int pos_check(const Grid *grid, Object *obj, int row, int col) {
    for (int i = 0; i < obj->size; i++) {
        for (int j = 0; j < obj->size; j++) {
            if (obj->shape[obj->rotation][i][j] && 
                (! valid_pos(grid, row + i, col + j) || ! empty_pos(grid, row + i, col + j))) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

int act(Grid *grid, Object *obj, Actions action) {
    switch (action) {
        case ROTATE:
            return rotate(grid, obj);
        case DOWN:
        case LEFT:
        case RIGHT:
            return move_obj(grid, obj, action);
        case DROP:
            return drop_obj(grid, obj);
        default:
            return 0;
    }
}

int rotate(Grid *grid, Object *obj) {
    remove_object(grid, obj);
    rotate_forward(obj);
    if (! pos_check(grid, obj, obj->row, obj->col)) {
        rotate_back(obj);
        return false;
    }
    put_object(grid, obj, obj->row, obj->col);
    return true;
}

int move_obj(Grid *grid, Object *obj, Actions action) {
    remove_object(grid, obj);
    int row = obj->row;
    int col = obj->col;
    switch (action) {
        case DOWN:
            row++;
            break;
        case LEFT:
            col--;
            break;
        case RIGHT:
            col++;
            break;
        default:
            return FALSE;
    }
    if (! pos_check(grid, obj, row, col)) {
        put_object(grid, obj, row, col);

        if (action == DOWN) {
            obj->locked_down = TRUE;
            obj->on_grid = FALSE;
        }
        return FALSE;
    }
    put_object(grid, obj, row, col); // assigning the position to the object in the func
    return TRUE;
}

int drop_obj(Grid *grid, Object *obj) {
    while (!obj->locked_down) {
        move_obj(grid, obj, DOWN);
    }
    return FALSE;
}
