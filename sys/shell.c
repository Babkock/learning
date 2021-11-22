/* Simple shell
 * September 18, 2010 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    char x[256], y[256], z[256];
    while (1) {
        getcwd(y, sizeof(y));
        printf("%s$ ", y);
        fgets(x, sizeof(x), stdin);
        if (x[0] == 'c' && x[1] == 'd' && x[2] == ' ') {
            sscanf(x, "cd %s", &z);
            chdir(z);
        }
        else if (strcmp(x, "exit\n") == 0) break;
        else system(x);
    }
    return 0;
}
