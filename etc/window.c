/* Ncurses window
 * November 28, 2021 */
#include <ncurses.h>

WINDOW *create_newwin(int h, int w, int sy, int sx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[]) {
	WINDOW *win;
	int startx, starty, width, height;
	int c;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	height = 4;
	width = 8;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	printw("Press Enter to exit");
	refresh();

	win = create_newwin(height, width, starty, startx);

	while ((c = getch()) != 10) {
		switch (c) {
			case KEY_LEFT:
				destroy_win(win);	
				if ((startx-1 > 0) && ((startx + width) < COLS))
					win = create_newwin(height, width, starty, --startx);
				break;
			case KEY_RIGHT:
				destroy_win(win);
				if (((startx + width + 1) < COLS) && ((starty + height) < LINES))
					win = create_newwin(height, width, starty, ++startx);
				break;
			case KEY_UP:
				destroy_win(win);
				if ((starty-1 > 0) && ((startx + width) < COLS))
					win = create_newwin(height, width, --starty, startx);
				break;
			case KEY_DOWN:
				destroy_win(win);
				if (((starty + height + 1) < LINES) && ((startx + width) < COLS))
					win = create_newwin(height, width, ++starty, startx);
				break;
		}
		refresh();
	}

	endwin();
	return 0;
}

WINDOW *create_newwin(int h, int w, int sy, int sx) {
	WINDOW *local;
	local = newwin(h, w, sy, sx);
	box(local, 0, 0);
	wrefresh(local);
	return local;
}

void destroy_win(WINDOW *local) {	
	wborder(local, '|', '|', '-', '-', '+', '+', '+', '+');
}

