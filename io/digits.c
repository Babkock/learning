/* digit counter by Tanner Babcock
 * February 1, 2011 */
#include <stdio.h>

int digits(const char *p) {
	int x;
	for (x = 0; *p != '\0'; p++) {
		if (*p == '0' || *p == '1' || *p == '2' ||
		*p == '3' || *p == '4' || *p == '5' ||
		*p == '6' || *p == '7' || *p == '8' || *p == '9') x++;
	}
	return x;
}

int main(void) {
	int x;
	char y[256];
	printf("Enter a string: ");
	fgets(y, sizeof(y), stdin);
	x = digits(y);
	printf("That string has %d digits.\n", x);
	return 0;
}
