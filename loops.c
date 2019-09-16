/* Loops example by Tanner Babcock
 * June 6, 2010 */
#include <stdio.h>
#include <time.h>

void wait(float seconds) {
	time_t start;
	time_t current;
	time(&start);
	do
		time(&current);
	while (difftime(current,start) < seconds);
}

int main() {
	char a[] = "Loop A - wait";
	char b[] = "Loop B - wait";
	char c[] = "seconds.";
	int x, y;
	printf("Beginning loop...\n");
	for (x = 1; x < 6; x++) {
		printf("   %s %d %s\n", a, x, c);
		wait(x);
		if (x == 5)
			printf("...ending loop.");
	}
	printf(" Beginning loop...\n");
	for (y = 5; y > 0; y--) {
		printf("   %s %d %s\n", b, y, c);
		wait(y);
		if (y == 1)
			printf("...ending loop.");
	}
	printf(" Done.\n");
	return 0;
}
