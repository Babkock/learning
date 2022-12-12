/* Compare pointers
 * June 29, 2022 */
#include <stdio.h>
#define MAX 3

int main(void) {
	int var[] = {10, 100, 200};
	int i, *ptr, sum = 0;

	ptr = var;
	for (i = 0; ptr <= &var[MAX - 1]; i++) {
		printf("Address of var[%d] = %x\n", i, ptr);
		printf("Value of var[%d] = %d\n", i, *ptr);

		sum += *ptr;
		ptr++;
	}
	printf("Sum: %d\n", sum);

	return 0;
}

