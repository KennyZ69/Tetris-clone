#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include "../headers/game.h"

void save_score(const char *filename, Game *game, time_t duration);

int main() {

    time_t start, end;

    Game *game = init_game();
    do {
        start = time(NULL);
        run(game);
        end = time(NULL);

        save_score("scores.txt", game, end - start);

    } while (game_over(game) == NEW_GAME);

    deinit_game(game);

    return 0;
}

void save_score(const char *filename, Game *game, time_t duration) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    fprintf(file, "Score: %d\n", game->score);
    fprintf(file, "Lines: %d\n", game->lines);
    fprintf(file, "Level: %d\n", game->lvl);
    fprintf(file, "Duration: %02li:%02li\n", duration / 60, duration % 60);
    fprintf(file, "------------------------\n");

    fclose(file);
}
