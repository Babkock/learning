/* daemon creator
 * November 28, 2021 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

static void theDaemon(void) {
	pid_t pid = fork();

	if (pid < 0)
		exit(1);
	if (pid > 0) // let the parent terminate
		exit(0);

	if (setsid() < 0)
		exit(1);

	signal(SIGCHLD, SIG_IGN);
	signal(SIGHUP, SIG_IGN);

	pid = fork();

	if (pid < 0)
		exit(1);
	if (pid > 0) {
		printf("Daemon PID: %d\n", pid);
		exit(0);
	}

	/* new file permissions */
	umask(0);
	chdir("/");

	int x;
	for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
		close(x);

	openlog("daemon", LOG_PID, LOG_DAEMON);
}

int main(void) {
	theDaemon();

	syslog(LOG_NOTICE, "Daemon started");
	sleep(20);
	syslog(LOG_NOTICE, "Daemon terminated");
	closelog();

	return 0;
}

