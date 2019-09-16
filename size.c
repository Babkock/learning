/* File size counter by Tanner Babcock
 * August 27, 2010, updated July 25, 2011 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int isdir(char *str) {
	DIR *dir;
	if (access(str, 0) != 0)
		return 2;
	if ((dir = opendir(str)) != NULL) {
		closedir(dir);
		return 1;
	}
	return 0;
}

int getfilesize(FILE* x) {
	fseek(x, 0L, SEEK_END);
	return ftell(x);
}

int main(int argc, char *argv[]) {
	int a, b, e = 0, f;
	FILE *c;
	char *d;
	if ((d = malloc(100 * sizeof(char))) == NULL) {
		fprintf(stderr, "Insufficient memory\n");
		return 3;
	}
	if (!argv[1]) {
		sprintf(d, "%s *", argv[0]);
		system(d);
		free(d);
		d = NULL;
		return 1;
	}
	free(d);
	d = NULL;
	for (a = 1; a < argc; a++) {
		if ((f = isdir(argv[a])) == 2) {
			printf("NULL\t\t%s\n", argv[a]);
			e += 2;
		}
		else if (f == 0) {
			c = (fopen(argv[a], "r"));
			b = getfilesize(c);
			if (b > 9999999)
				printf("%d\t%s\n", b, argv[a]);
			else
				printf("%d\t\t%s\n", b, argv[a]);
			fclose(c);
		}
		else {
			printf("DIR \t\t%s\n", argv[a]);
			e += 4;
		}
	}
	return e;
}
