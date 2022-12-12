/* TCP server with multiple connections
 * August 15, 2021 */
/* Use with client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUF 256
#define PORT 5001
int handler(int sock, const char *msg);
void interrupt(int sig);

/* server response can be supplied on command line */
int main(int argc, char *argv[]) {
	int sockfd, newsockfd, portno, pid;
	char response[BUF];
	struct sockaddr_in serv_addr, cli_addr;
	unsigned int clilen;

	signal(SIGINT, interrupt);
	signal(SIGABRT, interrupt);

	/* first call to socket() */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Error opening socket\n");
		return 1;
	}

	if (argc < 2) {
		printf("Enter a response to connecting clients: ");
		fgets(response, BUF, stdin);
	}
	else {
		for (int i = 1; i < argc; i++) {
			sprintf(response, "%s%s%c", response, argv[i], (i != (argc-1)) ? ' ' : '\n');
		}
	}

	/* initialize socket structure */
	bzero((char *)&serv_addr, sizeof(serv_addr));
	portno = PORT;

	printf("Listening for clients\n");

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
			return handler(newsockfd, response);
		}
		else {
			close(newsockfd);
		}
	} /* while (1) */

	return 0;
}

int handler(int sock, const char *msg) {
	int n;
	char buffer[BUF];
	bzero(buffer, BUF);

	/* read 255 from sock and put it into buffer */
	if ((n = read(sock, buffer, BUF-1)) < 0) {
		fprintf(stderr, "Error reading from socket\n");
		return 1;
	}
	printf("Here is the message: %s", buffer);
	if ((n = write(sock, msg, strlen(msg))) < 0) {
		fprintf(stderr, "Error writing to socket\n");
		return 1;
	}

	return 0;
}

void interrupt(int sig) {
	printf("Done listening\n");
	exit(0);
}

