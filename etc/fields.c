/* Ncurses fields program
 * April 13, 2022
 * Compile with -lform -lncurses */
#include <ncurses.h>
#include <form.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static FORM *form;
static FIELD *fields[5];
static WINDOW *body, *wform;

static char *trim(char *s) {
	char *end;

	while (isspace(*s))
		s++;

	if (*s == 0)
		return s;

	end = s + strnlen(s, 128) - 1;

	while (end > s && isspace(*end))
		end--;
	*(end+1) = '\0';

	return s;
}

static void driver(int ch) {
	int i;

	switch (ch) {
		case KEY_F(2):
			form_driver(form, REQ_NEXT_FIELD);
			form_driver(form, REQ_PREV_FIELD);
			move(LINES-3, 2);

			for (i = 0; fields[i]; i++) {
				printw("%s", trim(field_buffer(fields[i], 0)));

				if (field_opts(fields[i]) & O_ACTIVE)
					printw("\"\t");
				else
					printw(": \"");
			}

			refresh();
			pos_form_cursor(form);
			break;
		case KEY_F(3):
			form_driver(form, REQ_DEL_LINE);
			form_driver(form, REQ_END_LINE);
			break;
		case KEY_DOWN:
			form_driver(form, REQ_NEXT_FIELD);
			form_driver(form, REQ_END_LINE);
			break;
		case KEY_UP:
			form_driver(form, REQ_PREV_FIELD);
			form_driver(form, REQ_END_LINE);
			break;
		case KEY_LEFT:
			form_driver(form, REQ_PREV_CHAR);
			break;
		case KEY_RIGHT:
			form_driver(form, REQ_NEXT_CHAR);
			break;

		case KEY_BACKSPACE:
		case 127:
			form_driver(form, REQ_DEL_PREV);
			break;

		case KEY_DC:
			form_driver(form, REQ_DEL_CHAR);
			break;
		default:
			form_driver(form, ch);
			break;
	}

	wrefresh(wform);
}

int main(void) {
	int ch;

	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	body = newwin(24, 80, 0, 0);
	assert(body != NULL);
	box(body, 0, 0);
	wform = derwin(body, 20, 78, 3, 1);
	assert(wform != NULL);
	box(wform, 0, 0);
	mvwprintw(body, 1, 2, "Press F1 to quit and F2 to print fields");

	fields[0] = new_field(1, 10, 0, 0, 0, 0);
	fields[1] = new_field(1, 40, 0, 15, 0, 0);
	fields[2] = new_field(1, 10, 2, 0, 0, 0);
	fields[3] = new_field(1, 40, 2, 15, 0, 0);
	fields[4] = NULL;
	assert(fields[0] != NULL);
	assert(fields[1] != NULL);
	assert(fields[2] != NULL);
	assert(fields[3] != NULL);

	set_field_buffer(fields[0], 0, "label1");
	set_field_buffer(fields[1], 0, "val1");
	set_field_buffer(fields[2], 0, "label2");
	set_field_buffer(fields[3], 0, "val2");

	set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
	set_field_opts(fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
	set_field_opts(fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
	set_field_opts(fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
	set_field_back(fields[1], A_UNDERLINE);
	set_field_back(fields[3], A_UNDERLINE);

	form = new_form(fields);
	assert(form != NULL);
	set_form_win(form, wform);
	set_form_sub(form, derwin(wform, 18, 76, 1, 1));
	post_form(form);

	refresh();
	wrefresh(body);
	wrefresh(wform);

	while ((ch = getch()) != KEY_F(1))
		driver(ch);

	unpost_form(form);
	free_form(form);
	for (int i = 0; i < 4; i++)
		free_field(fields[i]);
	delwin(wform);
	delwin(body);
	endwin();
	return 0;
}

