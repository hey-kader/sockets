#include "common.h"
#define IP "66.85.133.188"
#define PORT 80

#define MAXLINE 256

void error (void) {
    printf ("error!\n");
}


int main (int argc, char *argv[]) {

    struct sockaddr_in server_addr, client_addr;
    int fsockd, newfsockd, n, clilen;
    char * buffer[MAXLINE+1];

    fsockd = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *)&server_addr, sizeof(&server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(fsockd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
	error ();
    }

    else {
	printf ("the socket is bound.\n");
    }

    listen (fsockd, 5);
    printf ("listening...\n");

    clilen = sizeof (client_addr);

    newfsockd = accept (fsockd, (struct sockaddr *) &client_addr, &clilen);

    n = read(newfsockd, buffer, MAXLINE-1);

    printf("here is the message:\t%s\n",buffer);
    write (newfsockd, (char*) buffer, strlen((char *)buffer));

    close(newfsockd);

    
    return 0;
}
