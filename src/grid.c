#include "../headers/grid.h"
#include <stdbool.h>
#include <stdlib.h>

Grid *create_grid(int rows, int cols) {
    Grid *grid = safe_malloc(sizeof(*grid));
    grid->rows = rows;
    grid->cols = cols;
    grid->content = safe_malloc(rows * cols * sizeof(char));

    flush_grid(grid);

    return grid;
}

int empty_pos(const Grid *grid, int row, int col) {
    return get_block(grid, row, col) == ' ';
}

char get_block(const Grid *grid, int row, int col) {
    return grid->content[row * grid->cols + col];
}

int is_row(const Grid *grid, int row) {
    for (int i = 0; i < grid->cols; i++) {
        if (empty_pos(grid, row, i)) return false;
    }
    return true;
}

void flush_block(Grid *grid, int row, int col) {
    grid->content[row * grid->cols + col] = ' ';
}

void flush_row(Grid *grid, int row) {
    for (int i = 0; i < grid->cols; i++) {
        flush_block(grid, row, i);
    }
}

void flush_grid(Grid *grid) {
    for (int i = 0; i < grid->rows; i++) {
            flush_row(grid, i);
        }
}

void deinit_grid(Grid *grid) {
    free(grid->content);
    free(grid);
}

int valid_pos(const Grid *grid, int row, int col) {
    return (row >= 0 && row < grid->rows && col >= 0 && col < grid->cols);
}

void move_row_down(Grid *grid, int row, int dest_row) {
    for (int i = 0; i < grid->cols; i++) {
        char temp1 = get_block(grid, row, i);
        char temp2 = get_block(grid, dest_row, i);

        grid->content[row * grid->cols + i] = temp2;
        grid->content[dest_row * grid->cols + i] = temp1;
    }
}
