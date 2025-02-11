#ifndef GRID_HEADER
#define GRID_HEADER

#include "utils.h"

#define EMPTY_CONTENT 0;

typedef struct {
	int rows;
	int cols;
	char *content;
} Grid;

// creates and returns a pointer to a new empty Grid of size rows x cols 
Grid *create_grid(int rows, int cols);

// returns true if every block in row is filled
int is_row(const Grid *grid, int row);

void flush_block(Grid *grid, int row, int col);

void flush_row(Grid *grid, int row);

void flush_grid(Grid *grid);

char get_block(const Grid *grid, int row, int col);

int empty_pos(const Grid *grid, int row, int col);

void deinit_grid(Grid *grid);

int valid_pos(const Grid *grid, int row, int col);

void move_row_down(Grid *grid, int row, int dest_row);

void fill_content(Grid *grid, char content, int row, int col);

#endif
