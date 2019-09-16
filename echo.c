/* Echo command equivalent by Tanner Babcock
 * June 20, 2010 */
#include <stdio.h>

int main(int argc, char *argv[]) {
	int x;
	for (x = 1; x < argc; x++) {
		printf("%s", argv[x]);
		if (x != (argc - 1))
			putchar(' ');
	}
	printf("\n");
	return 0;
}
