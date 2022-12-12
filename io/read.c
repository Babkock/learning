/* File reader by Tanner Babcock
 * June 8, 2010, updated June 26 */
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (!argv[1]) {
		printf("USAGE: %s [input]\n", argv[0]);
		return 1;
	}
	int x;
	FILE *in;
	for (x = 1; x < argc; x++) {
		in = (fopen(argv[x], "r"));
		int y;
		if (!in) {
			fclose(in);
			return 2;
		}
		while ((y = fgetc(in)) != EOF)
			putchar(y);
		fclose(in);
	}
	return 0;
}

