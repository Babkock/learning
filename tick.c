/* FIFO read "tick"
 * October 28, 2021 */
/* Use with speak.c */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "pipe.fifo"

int main(void) {
	char s[300];
	int num, fd;

	mknod(FIFO_NAME, S_IFIFO | 0666, 0);

	printf("Waiting for writers\n");
	fd = open(FIFO_NAME, O_RDONLY);
	printf("Got a writer\n");

	do {
		if ((num = read(fd, s, 300)) == -1)
			perror("read");
		else {
			s[num] = '\0';
			printf("Tick: Read %d bytes: \"%s\"\n", num, s);
		}
	} while (num > 0);

	return 0;
}

