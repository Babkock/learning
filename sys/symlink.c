/* Symbolic links
 * November 28, 2021 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "USAGE: %s [filename] [symbolic link]\n", argv[0]);
		return 1;
	}
	if (symlink(argv[1], argv[2]) != 0) {
		if (errno == EEXIST)
			fprintf(stderr, "ERROR: Symlink output already exists\n");
		else if (errno == EACCES)
			fprintf(stderr, "ERROR: No write permission in directory\n");
		else if (errno == ELOOP)
			fprintf(stderr, "ERROR: Symbolic link loop\n");
		else
			fprintf(stderr, "ERROR: Could not make symbolic link\n");
	}
	else {
		printf("Created symbolic link\n");
	}
	return 0;
}

