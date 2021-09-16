#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADS 5

void printHello(void *threadid) {
	long tid;
	tid = (long)threadid;
	printf("Hello world! Thread id: %d\n", tid);
	pthread_exit(NULL);
}

int main(void) {
	pthread_t threads[THREADS];
	int rc, i;
	for (i = 0; i < THREADS; i++) {
		printf("main(): Creating thread %d\n", i);
		rc = pthread_create(&threads[i], NULL, printHello, (void *)i);
		if (rc) {
			printf("Error: Unable to create thread %d", rc);
			return 1;
		}
	}
	pthread_exit(NULL);
	return 0;
}
