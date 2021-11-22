/* PID and environment variables
 * November 19, 2021 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	pid_t id = getpid();
	pid_t id2 = getppid();

	printf("Process ID: %d\n", id);
	printf("Parent process ID: %d\n", id2);

	printf("SHELL = %s\n", getenv("SHELL"));
	printf("TERM = %s\n", getenv("TERM"));
	printf("USER = %s\n", getenv("USER"));
	printf("PWD = %s\n", getenv("PWD"));
	printf("LANG = %s\n", getenv("LANG"));

	return 0;
}

