#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>

char *prtkey(int ch);

int main(void) {
	WINDOW *window;
	int ch;

	if ((window = initscr()) == NULL) {
		fprintf(stderr, "Couldn't initialize ncurses\n");
		return 1;
	}

	noecho();
	keypad(window, TRUE);

	mvaddstr(5, 10, "Press a key ('q' to quit): ");
	mvprintw(7, 10, "You pressed: ");
	refresh();

	while ((ch = getch()) != 'q') {
		deleteln();
		mvprintw(7, 10, "You pressed: 0x%x (%s)", ch, prtkey(ch));
		refresh();
	}

	delwin(window);
	endwin();
	refresh();

	return 0;
}

struct keydesc {
	int code;
	char name[20];
};

char *prtkey(int ch) {
	static struct keydesc keys[] = { { KEY_UP,                  "Up Arrow" },
									 { KEY_DOWN,                "Down Arrow" }	};
	static char keych[2] = "";

	if (isprint(ch) && !(ch && KEY_CODE_YES)) {
		keych[0] = ch;
		return keych;
	}
	else {
		int n = 0;
		do {
			if (keys[n].code == ch)
				return keys[n].name;
			n++;
		} while (keys[n].code != -1);
		return keys[n].name;
	}

	return NULL;
}

