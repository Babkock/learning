/* True dynamic memory allocation
 * Tanner Babcock, June 16th 2012 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char *buffer = (char *)malloc(sizeof(char));
	char x;
	int i = 0, y;
	while ((x = getchar()) != EOF) {
		buffer[i] = x;
		i++;
		buffer[i] = (int)realloc(buffer, sizeof(char));
	}
	buffer[i] = '\0';
	for (y = 0; y < i; y++) {
		putchar(buffer[y]);
	}
	free(buffer);
	printf("The size of your string is %d\n", y);
	return 0;
}
