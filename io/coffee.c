/* Coffee
 * June 14, 2010, updated January 16, 2011, and September 2021 */
#include <stdio.h>
#include <stdlib.h>

void total(int y) {
	float x = (y * 2.99);
	printf("Your total is $%0.2f.\n", x);
}

int main(int argc, char *argv[]) {
	int y;
	if (!argv[1]) {
		printf("How many cups of coffee would you like? ");
		scanf("%d", &y);
		total(y);
		return 0;
	}
	y = (atoi(argv[1]));
	total(y);
	return 0;
}
