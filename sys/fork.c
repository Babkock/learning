/* fork example
 * March 1, 2011 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	pid_t brat;
	int x;
	brat = fork();
	if (brat >= 0) {
		if (brat == 0) {
			sleep(2); /* Hey kids! */
			printf("Hey dad!\n");
			sleep(4); /* What do you want to do today? */
			printf("We don\'t know.\n");
			sleep(4); /* Want to go to the matinee? */
			printf("No!\n");
			sleep(4); /* Want to go to the amusement park? */
			printf("No!\n");
			sleep(4); /* Want to go to the punk rock show? */
			printf("Yeah, let\'s go to the punk rock show!\n");
			sleep(2);
			return 0;
		}
		printf("Hey kids!\n");
		sleep(4); /* Hey dad! */
		printf("What do you want to do today?\n");
		sleep(4); /* We don't know. */
		printf("Want to go to the matinee?\n");
		sleep(4); /* No! */
		printf("Want to go to the amusement park?\n");
		sleep(4); /* No! */
		printf("Want to go to the punk rock show?\n");
		wait(&x); /* Yeah, let's go to the punk rock show! */
		return 0;
	}
	else {
		printf("Fork failed\n");
		return 1;
	}
}
