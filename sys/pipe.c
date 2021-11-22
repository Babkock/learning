/* Fork and pipe example
 * October 28, 2021 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
	int pfds[2];
	char buf[30];

	pipe(pfds);

	if (!fork()) {
		printf(" Child: Writing to the pipe\n");
		if (write(pfds[1], "test", 5) == -1) {
			fprintf(stderr, "Could not write to pipe\n");
			exit(1);
		}
		printf(" Child: exiting\n");
		exit(0);
	}
	else {
		printf("Parent: Reading from pipe\n");
		read(pfds[0], buf, 5);
		printf("Parent: Read \"%s\"\n", buf);
		wait(NULL);
	}
	return 0;
}

