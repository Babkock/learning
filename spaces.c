/* spaces counter by Tanner Babcock
 * February 1, 2011 */
#include <stdio.h>

int spaces(const char *p) {
	int x;
	for (x = 0; *p != '\0'; p++)
		if (*p == ' ') x++;
	return x;
}

int main() {
	int x;
	char y[256];
	printf("Enter a string: ");
	fgets(y, sizeof(y), stdin);
	x = spaces(y);
	printf("That string has %d spaces.\n", x);
	return 0;
}
