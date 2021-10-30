/* TCP server
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

/* run this in one window, and client.c in another */
int main(void) {
	int sockfd, newsockfd, portno, clilen;
	char buffer[BUF];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	/* first call to socket() */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Error opening socket\n");
		return 1;
	}

	/* initialize socket structure */
	bzero((char *)&serv_addr, sizeof(serv_addr));
	portno = PORT;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/* now bind the host address */
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		fprintf(stderr, "Error on binding\n");
		return 2;
	}

	// now start listening for clients
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	// accept connection
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	if (newsockfd < 0) {
		fprintf(stderr, "Error on accept()\n");
		return 3;
	}

	/* start communicating */
	bzero(buffer, 256);
	if ((n = read(newsockfd, buffer, 255)) < 0) {
		fprintf(stderr, "Error reading from socket\n");
		return 4;
	}

	/* no newline because the message will be retrieved from fgets() */
	printf("Here is the message: %s", buffer);
	/* write a response to the client */
	
	if ((n = write(newsockfd, "I got your message", 18)) < 0) {
		fprintf(stderr, "Error writing to socket\n");
		return 5;
	}

	if ((n = close(sockfd)) < 0) {
		fprintf(stderr, "Error closing socket\n");
		return 6;
	}
	return 0;
}
