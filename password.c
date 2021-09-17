/* Ncurses password by Tanner Babcock
 * May 29, 2011
 * cc prog.c -lncurses */
#include <ncurses.h>

int main(void) {
	initscr();
	int x, y;
	char passwd[20];
	noecho();
	printw("Enter your password: ");
	for (y = 0; (x = getch()) != 10 && y != 21; y++) {
		/* loop will stop after 20 chars, or when
		 * the user hits enter */
		passwd[y] = x;
		printw("*");
	}
	passwd[y] = '\0';
	printw("\nYour password is: %s\n", passwd);
	getch();
	endwin();
	return 0;
}
