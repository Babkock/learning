/* Pthread condition
 * November 21, 2021
 * Compile with -lpthread */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#define THREADS 20

int done = 0;
/* number of threads finished */

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void *entry(void *id);

int main(void) {
	printf("Main thread starting\n");
	pthread_t threads[THREADS];
	for (int t = 0; t < THREADS; t++)
		pthread_create(&threads[t], NULL, entry, (void *)(long)t);

	if (pthread_mutex_init(&lock, NULL) != 0) {
		fprintf(stderr, "Could not initialize mutex\n");
		return 1;
	}

	if (pthread_mutex_lock(&lock) != 0) {
		fprintf(stderr, "Could not lock mutex, error %d\n", errno);
		return 1;
	}
	
	/* while there is at least 1 thread not finished */
	while (done < THREADS) {
		printf("%d threads finished, %d to go\n", done, (int)(THREADS - done));

		/* block until another thread signals cond. the Mutex is released
		 * while blocked, then re-acquired before the call returns */
		if (pthread_cond_wait(&cond, &lock) != 0) {
			fprintf(stderr, "Could not wait, error %d\n", errno);
			return 2;
		}

		printf("Condition was signalled\n");
	}
	
	if (pthread_mutex_unlock(&lock) != 0) {
		fprintf(stderr, "Could not unlock mutex, error %d\n", errno);
		return 1;
	}
	pthread_mutex_destroy(&lock);
	return 0;
}

void *entry(void *id) {
	const int realId = (long)id;

	for (int i = 0; i < 5; i++) {
		printf("Thread %d: working %d / 5\n", realId, i);
		sleep(1);
	}

	/* acquire mutex from main(), then release back to main() after
	 * condition is signalled */
	if (pthread_mutex_lock(&lock) != 0) {
		fprintf(stderr, "Thread %d could not lock mutex, error %d\n", realId, errno);
		abort();
	}

	/* thread is finished */
	done++;
	printf("Thread %d is done. %d threads done. Signalling...\n", realId, done);

	/* wake the sleeping main thread */
	if (pthread_cond_signal(&cond) != 0) {
		fprintf(stderr, "Thread %d could not wake sleeping main, error %d\n", realId, errno);
		abort();
	}
	
	if (pthread_mutex_unlock(&lock) != 0) {
		fprintf(stderr, "Thread %d could not unlock mutex, error %d\n", realId, errno);
		abort();
	}

	return NULL;
}

