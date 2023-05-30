/* TCP client
 * August 15, 2021 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUF 256
#define PORT 5001

/* Execute like this to connect to server:
 * $ ./client 127.0.0.1 5001 */
int main(int argc, char **argv) {
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char hostname[BUF];
	char buffer[BUF];

	portno = ((argc < 3) ? PORT : atoi(argv[2]));
	bzero(hostname, BUF);
	sprintf(hostname, "%s", ((argc < 2) ? "127.0.0.1" : argv[1]));

	if (argc < 3) {
		printf("Using default port %d\n", PORT);
	}
	if (argc < 2) {
		printf("Using default host 127.0.0.1\n");
	}

	/* create a socket point */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Error opening socket\n");
		return 1;
	}

	if (!(server = gethostbyname(hostname))) {
		fprintf(stderr, "Error: No such host '%s'\n", hostname);
		return 2;
	}

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	/* connect to the server */
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		fprintf(stderr, "Error connecting\n");
		return 3;
	}

	/* ask for a message from the user, this message will be read by the server */
	printf("Please enter a message for the server: ");
	bzero(buffer, BUF);
	fgets(buffer, BUF, stdin);

	/* send message to the server */
	if ((n = write(sockfd, buffer, strlen(buffer))) < 0) {
		fprintf(stderr, "Error writing to socket\n");
		return 4;
	} else {
		printf("Wrote %d bytes\n", n);
	}

	/* now read server response */
	bzero(buffer, BUF);
	if ((n = read(sockfd, buffer, BUF-1)) < 0) {
		fprintf(stderr, "Error reading from socket\n");
		return 4;
	} else {
		printf("Read %d bytes\n", n);
	}

	close(sockfd);
	printf("Your message: %s", buffer);
	return 0;
}

