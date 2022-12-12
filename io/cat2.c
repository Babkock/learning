/* cat high-level
 * December 13, 2021 */
#include <stdio.h>

int main(void) {
	int x;
	while ((x = getchar()) != EOF)
		putchar(x);
	return 0;
}

