/* Hostname lookup
 * November 22, 2021 */
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
	struct addrinfo *res;
	char *hostname;
	struct sockaddr_in *saddr;

	if (argc < 2) {
		fprintf(stderr, "USAGE: %s [domain name]\n", argv[0]);
		return 1;
	}
	hostname = argv[1];

	if (getaddrinfo(hostname, NULL, NULL, &res) != 0) {
		fprintf(stderr, "Error in resolving hostname \"%s\"\n", hostname);
		return 1;
	}

	saddr = (struct sockaddr_in *)res->ai_addr;
	printf("Address for %s is %s\n", hostname, inet_ntoa(saddr->sin_addr));

	return 0;
}

