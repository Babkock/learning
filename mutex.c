/* Pthread mutex
 * November 21, 2021
 * Compile with -lpthread */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void *handler(void *arg) {
	pthread_mutex_lock(&lock);
	counter++;
	printf("Job %d has started\n", counter);
	sleep(2);
	printf("Job %d has finished\n", counter);
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(void) {
	int i, error;

	if (pthread_mutex_init(&lock, NULL) != 0) {
		fprintf(stderr, "Cannot init mutex\n");
		return 1;
	}

	for (i = 0; i < 2; i++) {
		error = pthread_create(&(tid[i]), NULL, &handler, NULL);
		if (error != 0) {
			fprintf(stderr, "Thread can't be created: [%s]\n", strerror(error));
		}
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_mutex_destroy(&lock);

	return 0;
}

