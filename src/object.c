#include "../headers/objects.h"
#include <string.h>

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
        switch (letter) {
                case 'I':
                        size = 4;
                        shape = 0;
                        break;
                case 'J':
                        size = 3;
                        shape = 1;
                        break;
                case 'L':
                        size = 3;
                        shape = 2;
                        break;
                case 'O':
                        size = 2;
                        shape = 3;
                        break;
                case 'S':
                        size = 3;
                        shape = 4;
                        break;
                case 'T':
                        size = 3;
                        shape = 5;
                        break;
                case 'Z':
                        size = 3;
                        shape = 6;
                        break;
                default: 
                        return;
        }

        obj->size = size;
        obj->rotation = 0;
        obj->on_grid = 0;
        obj->row = 0;
        obj->col = 0;
        obj->locked_down = 0;
        memcpy(obj->shape, shapes[shape], 4 * 4 * sizeof(char));
}

void put_object(Grid *grid, Object *obj, int row, int col) {
        if (obj->locked_down || obj->on_grid) return;
        for (int i = 0; i < obj->size; i++) {
                for (int j = 0; j < obj->size; j++) {
                        if (obj->shape[obj->rotation][i][j]) {
                                grid->content[(row + i) * grid->cols + (col + j)] = TEXTURE;
                        }
                }
        }
        obj->on_grid = 1;
        obj->row = row;
        obj->col = col;
}

void remove_object(Grid *grid, Object *obj) {
        if (obj->locked_down || !obj->on_grid) return;

        for (int i = 0; i < obj->size; i++) {
                for (int j = 0; j < obj->size; j++) {
                        if (obj->shape[obj->rotation][i][j]) {
                                grid->content[(obj->row + i) * grid->cols + (obj->col + j)] = 0;
                        }
                }
        }
        obj->on_grid = 0;
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
