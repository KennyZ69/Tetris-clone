#include <ncurses.h>
#include <time.h>
#include "../headers/game.h"

void save_score(const char *filename, Game *game, time_t duration);

int main() {
    // initscr();            // Start ncurses mode
    // noecho();             // Don't display key presses
    // curs_set(FALSE);      // Hide the cursor
    // keypad(stdscr, TRUE); // Enable arrow key input
    // timeout(100);         // Set game speed (100ms per frame)
    //
    // while (1) {
    //     clear();          // Clear screen
    //     mvprintw(5, 10, "[]");  // Print test block
    //     refresh();        // Update screen
    //
    //     int ch = getch();
    //     if (ch == 'q') break;  // Exit game if 'q' is pressed
    // }
    //
    // endwin();             // End ncurses mode

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
