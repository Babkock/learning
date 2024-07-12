/* Pthread mutex
 * November 21, 2021
 * Compile with -lpthread */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define THREADS 4

int counter;
pthread_mutex_t *lock;

static void *handler(void *arg) {
	pthread_mutex_lock(lock);
	counter++;
	printf("Arg = %s\n", arg);
	printf("Job %d has started\n", counter);
	sleep(2);
	printf("Job %d has finished\n", counter);
	pthread_mutex_unlock(lock);
	return NULL;
}

int main(void) {
	int i, error;

	pthread_t *tid = (pthread_t *)malloc((sizeof(pthread_t) * THREADS));
	lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));

	if (pthread_mutex_init(lock, NULL) != 0) {
		fprintf(stderr, "Cannot init mutex\n");
		return 1;
	}

	for (i = 0; i < 4; i++) {
		error = pthread_create(&tid[i], NULL, &handler, "hello");
		if (error != 0) {
			fprintf(stderr, "Thread can't be created: [%s]\n", strerror(error));
		}
	}
	if (error != 0) {
		free(lock);
		free(tid);
		return 1;
	}

	for (i = 0; i < 4; i++) {
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(lock);
	free(lock);
	free(tid);

	return 0;
}

