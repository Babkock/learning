/* TCP server with multiple connections
 * August 15, 2021 */
/* Use with client.c */
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
int handler(int sock);

int main(void) {
	int sockfd, newsockfd, portno, clilen;
	char buffer[BUF];
	struct sockaddr_in serv_addr, cli_addr;
	int n, pid;

	/* first call to socket() */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Error opening socket\n");
		return 1;
	}

	/* initialize socket structure */
	bzero((char *)&serv_addr, sizeof(serv_addr));
	portno = PORT;

	serv_addr = (struct sockaddr_in){ .sin_family = AF_INET, .sin_addr.s_addr = INADDR_ANY, .sin_port = htons(portno) };

	/* now bind the host address using bind() call */
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		fprintf(stderr, "Error binding\n");
		return 2;
	}

	/* now start listening for clients, here the process will sleep and
	 * wait for incoming connections */
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	while (1) {
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		if (newsockfd < 0) {
			fprintf(stderr, "Error on accept()\n");
			return 2;
		}
		/* create child process */
		if ((pid = fork()) < 0) {
			fprintf(stderr, "Error on fork()\n");
			return 3;
		}
		if (pid == 0) {
			/* this is the client process */
			close(sockfd);
			return handler(newsockfd);
		}
		else {
			close(newsockfd);
		}
	} /* while (1) */

	return 0;
}

int handler(int sock) {
	int n;
	char buffer[BUF];
	bzero(buffer, BUF);

	/* read 255 from sock and put it into buffer */
	if ((n = read(sock, buffer, BUF-1)) < 0) {
		fprintf(stderr, "Error reading from socket\n");
		return 1;
	}
	printf("Here is the message: %s\n", buffer);
	if ((n = write(sock, "I got your message", 18)) < 0) {
		fprintf(stderr, "Error writing to socket\n");
		return 1;
	}

	return 0;
}

