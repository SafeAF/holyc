#include <ncurses.h>

int main() {
    int x = 10, y = 10;
    int ch;

    // Initialize ncurses
    initscr();              // Start curses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo typed characters
    keypad(stdscr, TRUE);   // Enable arrow keys
    curs_set(0);            // Hide the cursor

    // Main loop
    while (1) {
        clear(); // Clear the screen

        mvaddch(y, x, '@'); // Draw the character
        refresh();          // Refresh the screen to show changes

        ch = getch();       // Wait for user input

        if (ch == 'q') break;         // Quit
        else if (ch == KEY_UP) y--;
        else if (ch == KEY_DOWN) y++;
        else if (ch == KEY_LEFT) x--;
        else if (ch == KEY_RIGHT) x++;
    }

    // Cleanup
    endwin();
    return 0;
}

