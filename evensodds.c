/* Evens and odds by Tanner Babcock
 * July 29, 2010 */
#include <stdio.h>

int main(int argc, char *argv[]) {
	int w, x;
	if (!argv[1]) w = 100;
	else w = atoi(argv[1]);
	FILE *y = (fopen("evens", "w"));
	FILE *z = (fopen("odds", "w"));
	for (x = 0; x <= w; x++) {
		if (x % 2 == 0) fprintf(y, "%d\n", x);
		if (x % 2 != 0) fprintf(z, "%d\n", x);
	}
	fclose(y);
	fclose(z);
	return 0;
}
