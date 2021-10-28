#include "common.h"

#define IP "66.85.133.188"
#define PORT 8080

#define MAXLINE 256

void error (void) {
    printf ("error!\n");
}


int main (int argc, char *argv[]) {

    if (argc < 3) {
//	error ();
	;	
    }

    struct sockaddr_in server_addr, client_addr;
    int fsockd, newfsockd, n;
    uint8_t buffer[MAXLINE+1];
    uint8_t recvline[MAXLINE+1];

    printf("IPv4:\t %s\n",IP);
    printf("PORT:\t %d\n",PORT);

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = PORT;

    fsockd = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(fsockd, (struct sockaddr *) &server_addr, sizeof(&server_addr)) > 0) {
	error ();
    }

    else {
	printf ("the socket is bound.\n");
    }

    // number of connections to take
    if (listen (fsockd, 5) > 0) {
	error ();
    }

    else {
	printf ("listening...\n");
    }

    int running = 1;
    int connfd, listenfd;

    printf("waiting for a connection on port %d\n",PORT);
    while (running) {

	struct sockaddr_in addr;
	socklen_t addr_len;

	fflush(stdout);
	connfd = accept (listenfd, (struct socket_addr *) NULL, NULL);

	memset (recvline, 0, MAXLINE);

	while ( (n = read(connfd, recvline, MAXLINE-1) ) > 0 ) {
	    fprintf(stdout, "\n%s\n\n%s", bin2hex(recvline, n), recvline);

	    if (recvline[n-1] == '\n') {
		break;
	    }

	    if (n < 0) {
		error ();
	    }

	    snprintf((char*)buffer, sizeof(buffer), "HTTP/1.0 200 OK\r\n\r\nHello");
	    write (connfd, (char*) buffer, strlen((char *)buffer));
	    close(connfd);
	}

    }

    newfsockd = accept (fsockd, (struct sockaddr *) &client_addr, sizeof(&client_addr));
    n = read (newfsockd, buffer, 255);

    printf("recieved: \n%s\n", buffer);

    n = write (fsockd, "i got your message. \n", 18);
    
    return 0;
}
