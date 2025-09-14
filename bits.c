/* Bitwise operations on input
 * with binary and hex output
 * July 3, 2022 */
#include <stdio.h>
// test

void bits(size_t const size, void const * const ptr) {
	unsigned char *b = (unsigned char *)ptr;
	unsigned char byte;
	int j;

	for (int i = size-1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			printf("%u%c", byte, (((j % 4) == 0) ? ' ' : 1));
		}
	}
	printf("\t\t%x\t%x", *(b + 1), *b);
	putchar('\n');
}

void operation(unsigned short op, const char *str) {
	printf("\n%s\t%d\n= ", str, op);
	bits(sizeof(op), &op);
}

int main(void) {
	unsigned short a, b, c;
	/* Set the variable c each time we call operation()
	 * to avoid stack smashing */

	printf("Size of short: %ld\n", sizeof(short));
	printf("Binary\t\t\t\t\t\tHex\n");
	printf("Enter one number (a): ");
	scanf("%hd", &a);
	bits(sizeof(a), &a);
	
	printf("Enter another number (b): ");
	scanf("%hd", &b);
	bits(sizeof(b), &b);

	c = a & b;   // a and b
	operation(c, "a & b");
	c = a | b;   // a or b
	operation(c, "a | b");

	c = a ^ b;
	operation(c, "a ^ b");
	c = ~a;      // negative a
	operation(c, "~a\t");
	c = ~b;      // negative b
	operation(c, "~b\t");

	printf("\nShift a left 2 bits, then right 2\n");
	c = a << 2;
	operation(c, "a << 2");
	c = a >> 2;
	operation(c, "a >> 2");
	
	printf("\nShift b left 2 bits, then right 2\n");
	c = b << 2;
	operation(c, "b << 2");
	c = b >> 2;
	operation(c, "b >> 2");

	return 0;
}

