/* Simple shell
 * September 18, 2010
 * November 21, 2024 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    char x[256], y[256], z[256];
	char host[60];
	char *user = getlogin();

	if (!user) {
		fprintf(stderr, "Could not get current user\n");
		return 1;
	}

	gethostname(host, sizeof(host));

    while (1) {
        printf("[%s@%s]$ ", user, host);
        fgets(x, sizeof(x), stdin);
        if (x[0] == 'c' && x[1] == 'd' && x[2] == ' ') {
            sscanf(x, "cd %s", z);
            chdir(z);
        }
		else if (x[0] == 'p' && x[1] == 'w' && x[2] == 'd' && x[3] == '\n') {
			getcwd(y, sizeof(y));
			printf("%s\n", y);
		}
        else if (strcmp(x, "exit\n") == 0) break;
        else system(x);
    }
    return 0;
}

