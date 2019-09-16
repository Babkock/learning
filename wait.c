#include <time.h>

wait(float x) {
	time_t start;
	time_t current;
	time(&start);
	do
		time(&current);
	while (difftime(current,start) < x);
}
