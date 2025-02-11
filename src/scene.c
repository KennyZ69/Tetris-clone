#include "../headers/scene.h"
#include "../headers/game.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

Scene *init_scene(Grid *grid, int edges, char **stats, int full, int stats_lines) {
    Scene *scene = safe_malloc(sizeof(*scene));

    scene->grid = grid;
    scene->edges = edges;
    scene->stats = stats;
    scene->stats_lines = stats_lines;
    scene->full = full;

    initscr();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    start_color();
    refresh();

    if (scene->full) {
        init_pair(1, COLOR_RED,     COLOR_RED);
        init_pair(2, COLOR_GREEN,   COLOR_GREEN);
        init_pair(3, COLOR_YELLOW,  COLOR_YELLOW);
        init_pair(4, COLOR_BLUE,    COLOR_BLUE);
        init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
        init_pair(6, COLOR_CYAN,    COLOR_CYAN);
        init_pair(7, COLOR_WHITE,   COLOR_WHITE);
    } else {
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_CYAN,    COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
        }

    return scene;
}

void draw_edges(const Scene *scene) {
    attron(COLOR_PAIR(BLUE));
    for (int i = 0; i < _ROWS + OFFSET * 2; i++) {
	if (i == 0 || i == _ROWS + OFFSET) {
		mvaddch(i, 0, '(');
		mvaddch(i, _COLS + OFFSET, ')');
	} else {
		mvaddch(i, 0, VERT_EDGE);
		mvaddch(i, _COLS + OFFSET, VERT_EDGE);
	}
    }
    for (int i = 0; i < _COLS ; i++) {
        mvaddch(0, i + OFFSET, HOR_EDGE);
        mvaddch(_ROWS + OFFSET, i + OFFSET, HOR_EDGE);
    }
    attroff(COLOR_PAIR(BLUE));
}

void refresh_scene(const Scene *scene) {
    if (scene->edges) draw_edges(scene);

    clear_stats(scene);
    draw_stats(scene);

    draw_grid(scene);

    refresh();
}

void deinit_scene(Scene *scene) {
    free(scene);
    endwin();
}

void draw_block(const Scene *scene, int row, int col) {
    int offset;
    char next_block;
    chtype curr_block;
     
    offset = (scene->edges) ? OFFSET : 0;
    curr_block = mvinch(row + offset, col + offset);

    next_block = get_block(scene->grid, row, col);

    if (next_block == (curr_block & A_CHARTEXT)) {
        return;
    } else if (empty_pos(scene->grid, row, col)) {
        mvaddch(row + offset, col + offset, ' ');
    } else {
        mvaddch(row + offset, col + offset, next_block);
    }
}

void draw_grid(const Scene *scene) {
    for (int i = 0; i < scene->grid->rows; i++) {
        for (int j = 0; j < scene->grid->cols; j++) {
            draw_block(scene, i, j);
        }
    }
}

void draw_stats(const Scene *scene) {
    int offset = scene->grid->cols + 1 + OFFSET * 2;

    for (int i = 0; i < scene->stats_lines; i++) {
        mvaddstr(i, offset, scene->stats[i]);
    }
}

void clear_stats(const Scene *scene) {
    int offset = scene->grid->cols + 1 + OFFSET * 2;

    for (int i = 0; i < scene->stats_lines; i++) {
        move(i, offset);
        clrtoeol();
    }
}
