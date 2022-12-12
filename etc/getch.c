#include <ncurses.h>

int main(int argc, char *argv[]) {
	initscr();
	printw("Press any key, or Enter to exit\n");
	noecho();
	int x;
	while ((x = getch()) != 10) {
		printw("%c -> %d\n", x);
	}
	return 0;
}

