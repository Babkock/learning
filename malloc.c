/* malloc example
 * USE THIS AS A MOTHERFUCKING RESOURCE */
#include <stdio.h>
#include <stdlib.h>

int main() {
	char *p;
	const int len = 10;
	p = (char *)malloc(len * sizeof(char));
	if (p == NULL) {
		fprintf(stderr, "Insufficient memory\n");
		return EXIT_FAILURE;
	}
	else {
		printf("Enter a string: ");
		fgets(p, len, stdin);
		printf("Address of string: %p\n", (void *)&p);
		printf("The string is: %s", p);
		free(p);
		p = NULL;
	}
	return EXIT_SUCCESS;
}
