#include "../headers/objects.h"
#include <ncurses.h>
#include <string.h>
#include "../headers/controls.h"

const char shapes_letters[NUM_SHAPES] = { 'I', 'J', 'L', 'O', 'S', 'T', 'Z' };

const char shapes[NUM_SHAPES][NUM_ROTATIONS][4][4] = {
        {       /* I */
                {
                        { 1, 1, 1, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 1, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 1, 1, 1, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 1, 0, 0 }
                }
        },
        {       /* J */
                {
                        { 1, 0, 0, 0 },
                        { 1, 1, 1, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 1, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 1, 1, 1, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 1, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                }
        },
        {       /* L */
                {
                        { 0, 0, 1, 0 },
                        { 1, 1, 1, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 1, 1, 1, 0 },
                        { 1, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 1, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                }
        },
        {       /* O */
                {
                        { 1, 1, 0, 0 },
                        { 1, 1, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 1, 1, 0, 0 },
                        { 1, 1, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 1, 1, 0, 0 },
                        { 1, 1, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 1, 1, 0, 0 },
                        { 1, 1, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                }
        },
        {       /* S */
                {
                        { 0, 1, 1, 0 },
                        { 1, 1, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 0, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 1, 0 },
                        { 1, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 1, 0, 0, 0 },
                        { 1, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                }
        },
        {       /* T */
                {
                        { 0, 1, 0, 0 },
                        { 1, 1, 1, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 0, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 1, 1, 1, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 0, 0 },
                        { 1, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                }
        },
        {       /* Z */
                {
                        { 1, 1, 0, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 1, 1, 0, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 0, 0 },
                        { 1, 1, 0, 0 },
                        { 1, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                }
        }
};

Object *create_object() {
        Object *obj = safe_malloc(sizeof(*obj));
        change_shape(obj, 'I');
        return obj;
}

void change_shape(Object *obj, char letter) {
        int size, shape;
        COLOR color;
        switch (letter) {
                case 'I':
                        size = 4;
                        shape = 0;
                        color = blue;
                        break;
                case 'J':
                        size = 3;
                        shape = 1;
                        color = yellow;
                        break;
                case 'L':
                        size = 3;
                        shape = 2;
                        color = white;
                        break;
                case 'O':
                        size = 2;
                        shape = 3;
                        color = green;
                        break;
                case 'S':
                        size = 3;
                        shape = 4;
                        color = red;
                        break;
                case 'T':
                        size = 3;
                        shape = 5;
                        color = cyan;
                        break;
                case 'Z':
                        size = 3;
                        shape = 6;
                        color = magen;
                        break;
                default: 
                        return;
        }

        obj->size = size;
        obj->rotation = 0;
        obj->on_grid = FALSE;
        obj->row = 0;
        obj->col = 0;
        obj->color = color;
        obj->locked_down = FALSE;
        memcpy(obj->shape, shapes[shape], 4 * 4 * NUM_ROTATIONS);
}

void put_object(Grid *grid, Object *obj, int row, int col) {
        if (obj->locked_down || obj->on_grid) return;
        for (int i = 0; i < obj->size; i++) {
                for (int j = 0; j < obj->size; j++) {
                        if (obj->shape[obj->rotation][i][j]) {
                                fill_content(grid, TEXTURE, row + i, col + j);
                        }
                }
        }
        obj->on_grid = TRUE;
        obj->row = row;
        obj->col = col;
}

void remove_object(Grid *grid, Object *obj) {
        if (obj->locked_down || !obj->on_grid) return;

        for (int i = 0; i < obj->size; i++) {
                for (int j = 0; j < obj->size; j++) {
                        if (obj->shape[obj->rotation][i][j]) {
                                flush_block(grid, obj->row + i, obj->col + j);
                        }
                }
        }
        obj->on_grid = FALSE;
}

void rotate_back(Object *obj) {
        int rotation = obj->rotation - 1;
        if (rotation == -1) {
                obj->rotation = NUM_ROTATIONS - 1;
        } else {
                obj->rotation = rotation;
        }
}

void rotate_forward(Object *obj) {
        obj->rotation = (obj->rotation + 1) % NUM_ROTATIONS;
}
