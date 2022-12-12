/* Vertical writing with curses
 * December 23, 2011 */
/* Compile with -lncurses */
#include <ncurses.h>

// test

int main(void) {
    WINDOW *w = initscr();
    int x, y, a, b = 0, c = 0;
    getmaxyx(w, y, x);
    clear();
    noecho();
    printw("^C to exit, ^L to clear\n");
    printw("Press any key to continue . . .");
    getch();
    clear();
    while ((a = getch()) != 3) {
        if (a == 12) {
            clear();
            b = 0, c = 0;
            move(b, c);
        }
        else if (b != (y -1)) {
            printw("%c", a);
            b++;
            move(b, c);
        }
        else {
            c++;
            b = 0;
            printw("%c", a);
            move(b, c);
        }
    }
    clear();
    endwin();
    return 0;
}

