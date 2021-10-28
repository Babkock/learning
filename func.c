/* Functions example
 * July 29, 2010 */
#include <stdio.h>
#include <stdlib.h>

int sqar(int x) {
	int y = (x * x);
	return y;
}

int cube(int x) {
	int y = (x * x * x);
	return y;
}

int main(int argc, char *argv[]) {
	int x;
	if (!argv[1]) {
		printf("Number: ");
		scanf("%d", &x);
	}
	if (argv[1]) x = atoi(argv[1]);
	int y = sqar(x);
	int z = cube(x);

	printf("Squared: %d\n", y);
	printf("Cubed: %d\n", z);
	return 0;
}
