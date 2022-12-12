/* Invert bit values
 * December 13, 2021 */
#include <stdio.h>

int invert(int x, int p, int n);

int main(void) {
	int x, p, n;

	printf("Enter x: ");
	scanf("%d", &x);
	printf("Enter position p: ");
	scanf("%d", &p);
	printf("Enter number of bits: ");
	scanf("%d", &n);
	printf("The processed number is: %d\n", invert(x, p, n));

	return 0;
}

int invert(int x, int p, int n) {
	int ref = 0;
	ref = ~ref << n;
	ref = ~ref << p;

	return ((~ref & x) | (ref & ~x));
}

