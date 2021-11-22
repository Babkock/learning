/* Backwards string example by Tanner Babcock
 * September 18, 2010, updated July 26, 2011, August 17, 2021 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int x;
	char *y;
	if ((y = malloc(256)) == NULL) {
		fprintf(stderr, "Insufficient memory\n");
		return 1;
	}
	fgets(y, 256, stdin);
	for (x = (strlen(y) - 2); x >= 0; x--)
		putchar(y[x]);
	free(y);
	putchar('\n');
	return 0;
}
