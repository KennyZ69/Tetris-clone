#include "../headers/scene.h"
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

    // TODO:
    // make also stats for the scene (as in infos)
    // I mean inside the header and apply it into the init_game()

    initscr();
    curs_set(false);
    keypad(stdscr, true);
    noecho();
    cbreak();
    start_color();
    refresh();

    return scene;
}

void draw_edges(const Scene *scene) {
    attron(COLOR_PAIR(BLUE));
    for (int i = 0; i < scene->grid->rows + OFFSET * 2; i++) {
        mvaddch(i, 0, VERT_EDGE);
        mvaddch(i, scene->grid->cols + OFFSET, VERT_EDGE);
    }
    for (int i = 0; i < scene->grid->cols; i++) {
        mvaddch(0, i + OFFSET, HOR_EDGE);
        mvaddch(scene->grid->rows + OFFSET, i + OFFSET, HOR_EDGE);
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
    int offset = scene->grid->cols + 1 + (scene->edges) ? OFFSET * 2 : 0;

    for (int i = 0; i < scene->stats_lines; i++) {
        mvaddstr(i, offset, scene->stats[i]);
    }
}

void clear_stats(const Scene *scene) {
    int offset = scene->grid->cols + 1 + (scene->edges) ? OFFSET * 2 : 0;

    for (int i = 0; i < scene->stats_lines; i++) {
        move(i, offset);
        clrtoeol();
    }
}
