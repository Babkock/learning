/* FIFO write "speak"
 * October 28, 2021 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "pipe.fifo"

/* Use with tick.c */
int main(void) {
	char s[300];
	int num, fd;

	mknod(FIFO_NAME, S_IFIFO | 0666, 0);

	printf("Waiting for readers\n");
	fd = open(FIFO_NAME, O_WRONLY);
	printf("Got a reader - type some stuff\n");
	while (strcmp(fgets(s, sizeof(s), stdin), "\n") != 0) {
		if ((num = write(fd, s, strlen(s))) == -1)
			perror("write");
		else
			printf("Speak: Wrote %d bytes\n", num);
	}

	return 0;
}

