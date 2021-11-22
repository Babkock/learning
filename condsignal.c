/* Pthread condition
 * November 21, 2021
 * Compile with -lpthread */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#define THREADS 20

int done = 0;
/* number of threads finished */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void *entry(void *id);

int main(void) {
	
	return 0;
}

void *entry(void *id) {
	
}

