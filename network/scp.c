/* Compile with -lssh2
 * Requires libssh2-1-dev package
 * December 14, 2021 */
#include <libssh2.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	unsigned long hostaddr;
	int sock, i, rc, auth_pw = 1;
	struct sockaddr_in sin;
	const char *fingerprint;
	LIBSSH2_SESSION *session;
	LIBSSH2_CHANNEL *channel;

	const char *username = "username";
	const char *password = "password";
	const char *scppath = "/tmp/TEST";

	libssh2_struct_stat fileinfo;
	libssh2_struct_stat_size got = 0;

	if (argc > 1)
		hostaddr = inet_addr(argv[1]);
	else
		hostaddr = htonl(0x7F000001); /* 127.0.0.1 */
	if (argc > 2)
		username = argv[2];
	if (argc > 3)
		password = argv[3];
	if (argc > 4)
		scppath = argv[4];

	rc = libssh2_init(0);
	if (rc) {
		fprintf(stderr, "Could not initialize libssh2 (%d)\n", rc);
		return 1;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);

	sin = (struct sockaddr_in){
		.sin_family = AF_INET,
		.sin_port = htons(22),
		.sin_addr.s_addr = hostaddr
	};
	if (connect(sock, (struct sockaddr*)(&sin), sizeof(struct sockaddr_in)) != 0) {
		fprintf(stderr, "Failed to connect\n");
		return 2;
	}

	session = libssh2_session_init();
	
	return 0;
}

