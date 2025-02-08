#ifndef SCENE_HEADER
#define SCENE_HEADER

#include "grid.h"
#include "utils.h"

#define VERT_EDGE '|'
#define HOR_EDGE '-'
#define OFFSET 1

// scene is the current scene on screen

typedef struct {
	Grid *grid;
	int edges;
} Scene;


// refresh (draw) the scene in its current state on screen
void refresh_scene(const Scene *scene);

Scene *init_scene(Grid *grid);

void draw_grid(const Scene *scene);

void draw_edges(const Scene *scene);

void deinit_scene(Scene *scene);

void draw_block(const Scene *scene, int row, int col);

#endif
