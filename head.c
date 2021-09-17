/* Linux head clone
 * June 21, 2012 */
#include <stdio.h>
#include <stdbool.h>
#define printUsage(x) \
	fprintf(stderr, "USAGE: %s [ -x ] [file]\n", argv[0]); \
	fprintf(stderr, "Where x = number of lines\n"); \
	return x \

int main(int argc, char *argv[]) {
	bool nofile = false;
	if (!argv[1]) {
		nofile = true;
	}
	else if ((argv[1][0] == '-') && (!argv[2])) {
		nofile = true;
	}
	
	int lines = -1, cur = 0, x;
	char *filename;
	FILE *in;
	if ((argv[1] != NULL) && (argv[1][0] == '-')) {
		sscanf(argv[1], "-%d", &lines);
		if (!nofile)
			filename = argv[2];
	}
	else {
		lines = 10;
		filename = argv[1];
	}
	
	if (!nofile) {
		if (!(in = fopen(filename, "r"))) {
			fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], filename);
			return 3;
		}
	}
	while ((cur < lines) && ((x = (!nofile) ? fgetc(in) : getchar()) != EOF)) {
		if (x == '\n')
			cur++;
		putchar(x);
	}
	
	return 0;
}
