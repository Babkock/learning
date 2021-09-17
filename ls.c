/* Directory contents by Tanner Babcock
 * July 11, 2010 */
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void ls(char path[])
{
	DIR *x = opendir(path);
	struct dirent *y = NULL;
	while ((y = readdir(x)))
		printf("%s\n", y->d_name);
	closedir(x);
}

int main(int argc, char *argv[]) {
    if (!argv[1]) {
		ls("./");
		return 0;
	}
	ls(argv[1]);
	return 0;
}

