/* malloc example */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char *p;
	const int len = 20;
	p = (char *)malloc(len * sizeof(char));
	if (p == NULL) {
		fprintf(stderr, "Insufficient memory\n");
		return 1;
	}
	else {
		printf("Enter a string: ");
		fgets(p, len, stdin);
		printf("Address of string: %p\n", (void *)&p);
		printf("The string is: %s", p);
		free(p);
		p = NULL;
	}
	return 0;
}

