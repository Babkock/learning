/* Time calculator by Tanner Babcock
 * May 4, 2012 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define ADD '+'
#define SUB '-'
#define FIL 4

enum { DAY, HOUR, MIN, SEC };

/* Fills array with EOF (-1) */
void fillEOF(int *t, int size) {
	for (int x = 0; x < size; x++)
		t[x] = -1;
	return;
}

/* Prompts for user input, and stores fields in an array */
char getTime(int *t, int size) {
	char tmp, op;
	fillEOF(t, size);
	scanf(" %c", &op);
	// Fields the user doesn't enter will have -1
	if (op == ADD || op == SUB) {
		for (int x = 0; x < size; x++) {
			scanf("%d%c", &t[x], &tmp);
			if (!tmp || tmp == '\n')
				break;
		}
	}
	return op;
}

/* Flies a remote-controlled drone armed with explosives into the White House */
void printIntro(void) {
	cout << "Time Calculator by Tanner Babcock\n";
	cout << "\'h\' - help\n";
	cout << "\'t\' - print total\n";
	cout << "\'r\' - reset total to 0\n";
	cout << "\'l\' - clear screen\n";
	cout << "\'q\' - quit\n";
	cout << "---------------------------------\n";
	return;
}

/* Cracks into pentagon and starts a war with Russia */
void printHelp(void) {
	cout << "Enter time in the format \"o DD HH MM SS\"\n";
	cout << "Where o = \"+\" or \"-\", for addition or subtraction\n";
	cout << "DD = days, HH = hours, MM = minutes, SS = seconds\n";
	cout << "One or more fields may be blank, \"+ 2 15\" adds\n";
	cout << "two minutes and fifteen seconds\n";
	cout << "---------------------------------\n";
	return;
}

/* Adds o[] to or subtracts o[] from t[], based on op */
char calculate(int *t, int *c, char op) {
	int x, *tmp;
	tmp = c;
	for (x = 0; x < 2; x++) {
		// user entered nothing/improperly formatted, return error
		if (tmp[DAY] == -1)
			return 1;
		// user only entered seconds, so put the DAY field in the SEC field
		else if (tmp[HOUR] == -1) {
			tmp[SEC] = tmp[DAY];
			tmp[MIN] = 0;
			tmp[HOUR] = 0;
			tmp[DAY] = 0;
			cout << ((op == ADD) ? "Added " : "Subtracted ") << tmp[SEC] << " seconds\n";
		}
		// user only entered MM:SS, formatted as DD:HH
		else if (tmp[MIN] == -1) {
			tmp[MIN] = tmp[DAY];
			tmp[SEC] = tmp[HOUR];
			tmp[DAY] = 0;
			tmp[HOUR] = 0;
			cout << ((op == ADD) ? "Added " : "Subtracted ")
				<< tmp[MIN] << " minutes, " << tmp[SEC] << " seconds\n";
		}
		// user only entered HH:MM:SS, formatted as DD:HH:MM
		else if (tmp[SEC] == -1) {
			tmp[SEC] = tmp[MIN];
			tmp[MIN] = tmp[HOUR];
			tmp[HOUR] = tmp[DAY];
			tmp[DAY] = 0;
			cout << ((op == ADD) ? "Added " : "Subtracted ")
				<< tmp[HOUR] << " hours, " << tmp[MIN] << " minutes, " << tmp[SEC] << " seconds\n";
		}
		// else, user entered all four fields, formatted properly
		else if (tmp != t) {
			cout << ((op == ADD) ? "Added " : "Subtracted ")
				<< tmp[DAY] << " days, " << tmp[HOUR] << " hours, "
				<< tmp[MIN] << " minutes, " << tmp[SEC] << " seconds\n";
		}
		tmp = t;
	}
	for (x = 0; x < FIL; x++) {
		switch (op) {
			case ADD: t[x] += c[x]; break;
			case SUB: t[x] -= c[x]; break;
		}
	}
	int m;
	// roll over numbers >59 and >23
	if (op == ADD) {
		while (t[HOUR] > 23 || t[MIN] > 59 || t[SEC] > 59) {
			while (t[HOUR] > 23) {
				t[HOUR] -= 24;
				t[DAY]++;
			}
			while (t[MIN] > 59) {
				t[MIN] -= 60;
				t[HOUR]++;
			}
			while (t[SEC] > 59) {
				t[SEC] -= 60;
				t[MIN]++;
			}
		}
	}
	// or roll over negative numbers if subtracting
	else if (op == SUB) {
		while (t[DAY] < 0 || t[HOUR] < 0 || t[MIN] < 0 || t[SEC] < 0) {
			if (t[DAY] < 0)
				t[DAY] = 0;
			if (t[HOUR] < 0) {
				m = t[HOUR];
				t[HOUR] = 0;
				t[DAY]--;
				t[HOUR] = (24 + m);
			}
			if (t[MIN] < 0) {
				m = t[MIN];
				t[MIN] = 0;
				t[HOUR]--;
				t[MIN] = (60 + m);
			}
			if (t[SEC] < 0) {
				m = t[SEC];
				t[SEC] = 0;
				t[MIN]--;
				t[SEC] = (60 + m);
			}
		}
		// when subtraction goes too far, i.e. (5 mins - 6 mins),
		// the above loop rolls digits over to 23 hours, 59 minutes
		if ((t[HOUR] > c[HOUR]) && (t[DAY] == 0 && c[DAY] == 0))
			bzero(t, sizeof(t));
	}
	return 0;
}

/* Prints t[], leaves out certain empty fields */
void printTotal(int *t) {
	cout << "Total: ";
	if (!t[DAY] || t[DAY] == EOF) {
		if (!t[HOUR]) {
			cout << t[MIN] << ":";
//			printf((t[SEC] < 10) ? "0%d\n" : "%d\n", t[SEC]);
			cout << ((t[SEC] < 10) ? "0" : "") << t[SEC] << "\n";
		}
		else {
			cout << t[HOUR] << ":";
//			printf((t[MIN] < 10) ? "0%d:" : "%d:", t[MIN]);
//			printf((t[SEC] < 10) ? "0%d\n" : "%d\n", t[SEC]);
			cout << ((t[MIN] < 10) ? "0" : "") << t[MIN] << ":";
			cout << ((t[SEC] < 10) ? "0" : "") << t[SEC] << "\n";
		}
	}
	else {
		cout << t[DAY] << ":";
//		printf((t[HOUR] < 10) ? "0%d:" : "%d:", t[HOUR]);
//		printf((t[MIN] < 10) ? "0%d:" : "%d:", t[MIN]);
//		printf((t[SEC] < 10) ? "0%d\n" : "%d\n", t[SEC]);
		cout << ((t[HOUR] < 10) ? "0" : "") << t[HOUR] << ":";
		cout << ((t[MIN] < 10) ? "0" : "") << t[MIN] << ":";
		cout << ((t[SEC] < 10) ? "0" : "") << t[SEC] << "\n";
	}
	return;
}

int main(void) {
	int current[4], total[4];
	char op = 0;
	bzero(current, sizeof(current));
	bzero(total, sizeof(total));
	printIntro();
	cout << "> ";
	while ((op = getTime(current, FIL)) != 'q') {
		switch (op) {
			case ADD: case SUB: if (calculate(total, current, op) == 1) { cout << "Formatted improperly\n"; } break;
			case 'h': printIntro(); printHelp(); break;
			case 't': printTotal(total); break;
			case 'r': bzero(total, sizeof(total)); break;
			case 'l':
#ifdef WIN32
				system("cls");
				cout << endl;
#else
				system("clear");
#endif
				break;
			case 'q': break;
		}
		cout << "> ";
	}
	return 0;
}
