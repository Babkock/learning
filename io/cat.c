/* cat low-level
 * December 13, 2021 */
#include <stdio.h>
#include <unistd.h>

int main(void) {
	char buf[256];
	int n;

	while ((n = read(0, buf, 256)) > 0)
		write(1, buf, n);
	return 0;
}

