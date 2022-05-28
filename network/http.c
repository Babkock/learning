/* Functioning HTTP server with directory listing
 * Serves HTML, Javascript, and images in current directory
 * May 28, 2022 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BUFSIZE 1024
#define BBUFSIZE 4096
#define MAX 16

extern char **environ;

typedef struct {
	const char *extension;
	const char *type;
} mime_type;

mime_type types[] = {
	{".css", "text/css"},
	{".html", "text/html"},
	{".js", "application/javascript"},
	{".json", "application/json"},
	{".jpg", "image/jpeg"},
	{".jpeg", "image/jpeg"},
	{".png", "image/png"},
	{".webp", "image/webp"},
	{".svg", "image/svg+xml"},
	{".pdf", "application/pdf"},
	{".", "text/plain"}
};

void format_size(char* buf, struct stat *stat) {
	bzero(buf, strlen(buf));
	if (S_ISDIR(stat->st_mode)) {
		sprintf(buf, "%s", "DIR");
	} else {
		off_t size = stat->st_size;
		if (size < 1024)
			sprintf(buf, "%lu", size);								        
		else if (size < 1024 * 1024)
			sprintf(buf, "%.1fK", (double)size / 1024);
		else if (size < 1024 * 1024 * 1024)
			sprintf(buf, "%.1fM", (double)size / 1024 / 1024);
		else
			sprintf(buf, "%.1fG", (double)size / 1024 / 1024 / 1024);
	}
}

void error(char *msg) {
	perror(msg);
	exit(1);
}

void cerror(FILE *stream, char *cause, char *errno, char *shortm, char *longm) {
	fprintf(stream, "HTTP/1.1 %s %s\n", errno, shortm);
	fprintf(stream, "Content-Type: text/html\n");
	fprintf(stream, "\n");
	fprintf(stream, "<html><style type=\"text/css\">* { color:white; }</style><title>Error</title>");
	fprintf(stream, "<body bgcolor=\"720000\">\n");
	fprintf(stream, "%s: %s\n", errno, shortm);
	fprintf(stream, "<p>%s: %s</p>\n", longm, cause);
	fprintf(stream, "<hr color=\"white\"/><em>Web Server</em>\n");
}

int main(int argc, char *argv[]) {
	int parentfd, childfd, portno;
	unsigned int clilen;
	char *hostaddrp; // dotted host IP address string
	int optval; // setsockopt()
	struct hostent *hostp;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	struct stat sbuf; // file status

	FILE *stream; // childfd
	char buf[BUFSIZE]; // message buffer
	char method[BUFSIZE]; // request method
	char uri[BUFSIZE]; // request URI
	char version[BUFSIZE]; // request method
	char filename[BUFSIZE]; // path derived from URI
	char filetype[BUFSIZE]; // path derived from URI
	char *p;
	int fd, ffd, dd, z;

	if (argc != 2) {
		fprintf(stderr, "USAGE: %s [port]\n", argv[0]);
		return 1;
	}
	portno = atoi(argv[1]);

	/* open socket descriptor */
	parentfd = socket(AF_INET, SOCK_STREAM, 0);
	if (parentfd < 0)
		error("Error opening socket\n");

	optval = 1;
	setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR,
		(const void *)&optval, sizeof(int));

	/* bind port to socket */
	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr = (struct sockaddr_in){
		.sin_family = AF_INET,
		.sin_addr.s_addr = htonl(INADDR_ANY),
		.sin_port = htons((unsigned short)portno)
	};

	if (bind(parentfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
		error("Error on binding to socket\n");

	/* become ready to accept requests */
	if (listen(parentfd, 5) < 0)
		error("Error on listen\n");

	char bbuf[BBUFSIZE], m_time[32], size[16];
	struct stat statbuf;
	struct dirent *dp;
	DIR *d;

	/* wait for connection request, parse HTTP,
	 * serve content, close connection */
	clilen = sizeof(clientaddr);
	while (1) {
		bzero(buf, BUFSIZE);
		bzero(bbuf, BBUFSIZE);
		/* wait */
		if ((childfd = accept(parentfd, (struct sockaddr *)&clientaddr, &clilen)) < 0)
			error("Error on accepting connection\n");

		/* determine who sent the message */
		hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
			sizeof(clientaddr.sin_addr.s_addr), AF_INET);

		if (!(hostaddrp = inet_ntoa(clientaddr.sin_addr)))
			error("Error on inet_ntoa()\n");

		/* open the child socket descriptor as a stream */
		if ((stream = fdopen(childfd, "r+")) == NULL)
			error("Error on opening child socket\n");

		/* get HTTP request line */
		fgets(buf, BUFSIZE, stream);
		printf("%s", buf);
		sscanf(buf, "%s %s %s\n", method, uri, version);

		/* only support GET method */
		if (strcasecmp(method, "GET")) {
			cerror(stream, method, "501", "Not Implemented", "We only support the GET method");
			fclose(stream);
			close(childfd);
			continue;
		}

		/* read HTTP headers */
		fgets(buf, BUFSIZE, stream);
		printf("%s", buf);
		while (strcmp(buf, "\r\n")) {
			fgets(buf, BUFSIZE, stream);
			printf("%s", buf);
		}

		/* parse the URI */
		strcpy(filename, ".");
		strcat(filename, uri);

		/* make sure the file exists */
		if (stat(filename, &sbuf) < 0) {
			cerror(stream, filename, "404", "Not Found", "File not found");
			fclose(stream);
			close(childfd);
			continue;
		}

		/* serve static content */
		if (S_ISREG(sbuf.st_mode)) {
			for (z = 0; z < sizeof(types); z++) {
				if (strstr(filename, types[z].extension)) {
					strcpy(filetype, types[z].type);
					break;
				}
			}

			/* print response header */
			fprintf(stream, "HTTP/1.1 200 OK\n");
			fprintf(stream, "Server: My Web Server\n");
			fprintf(stream, "Content-Length: %d\n", (int)sbuf.st_size);
			fprintf(stream, "Content-Type: %s\n", filetype);
			fprintf(stream, "\r\n");
			fflush(stream);

			/* use mmap to return response body */
			fd = open(filename, O_RDONLY);
			p = mmap(0, sbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
			fwrite(p, 1, sbuf.st_size, stream);
			munmap(p, sbuf.st_size);
			close(fd);
		} else if (S_ISDIR(sbuf.st_mode)) {
			strcpy(filetype, "text/html");
			sprintf(bbuf, "HTTP/1.1 200 OK\r\n%s%s%s%s%s%s%s",
					"Content-Type: text/html\r\n\r\n",
					"<html><head><style>",
					"body{font-family: monospace; font-size: 1.1em; background-color:#720000; color:white; }",
					"a:link, a:hover, a:visited { color:lime; text-decoration:none }",
					"a:active { color:white; } table, table tbody { width:80%; }",
					"td {padding: 2px 6px; background-color:#220000; border:1px solid black; color:#eeeeee; }",
					"</style></head><body><table><tbody>\n");	
			
			if ((ffd = open(filename, O_RDONLY, 0)) < 0) {
				error("Could not open directory\n");
			}
			if (write(childfd, bbuf, strlen(bbuf)) < 0) {
				error("Could not write to buffer\n");
			}
			d = fdopendir(ffd);

			while ((dp = readdir(d)) != NULL) {
				if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
					continue;
				if ((dd = openat(ffd, dp->d_name, O_RDONLY)) == -1) {
					perror(dp->d_name);
					continue;
				}
				fstat(dd, &statbuf);

				strftime(m_time, sizeof(m_time), "%Y-%m-%d %H:%M", localtime(&statbuf.st_mtime));
				format_size(size, &statbuf);
				
				if (S_ISREG(statbuf.st_mode) || S_ISDIR(statbuf.st_mode)) {
					char *f = S_ISDIR(statbuf.st_mode) ? "/" : "";
					sprintf(bbuf, "<tr><td><a href=\"%s%s\">%s%s</a></td><td>%s</td><td>%s</td></tr>\n",
						dp->d_name, f, dp->d_name, f, m_time, size);
					write(childfd, bbuf, strlen(bbuf));
					
					bzero(bbuf, strlen(bbuf));
				}
			}
			sprintf(bbuf, "</tbody></table></body></html>");
			write(childfd, bbuf, strlen(bbuf));

			close(ffd);
			closedir(d);
		}
		fclose(stream);
		close(childfd);
	}

	return 0;
}
