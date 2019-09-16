/* File writer by Tanner Babcock
 * June 9, 2010 */
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (!argv[1]) {
		printf("USAGE: %s [output]\n", argv[0]);
		return 1;
	}
	FILE *out = (fopen(argv[1], "w"));
	int x;
	while ((x = getchar()) != EOF)
		fputc(x, out);
	fclose(out);
	return 0;
}
