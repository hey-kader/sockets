#include "common.h"

int main (int argc, char *argv[]) {

    struct sockaddr_in server_addr, client_addr;
    int fsockd, newfsockd, n;
    char buffer[256];

    printf("IPv4:\t %s\n",IP);
    printf("PORT:\t %d\n",PORT);

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
    listen (fsockd, 5);

    newfsockd = accept (fsockd, (struct sockaddr *) &newfsockd, 0 );
    memset (buffer, 0, MAX);

    while (n = read (newfsockd, buffer, 255) > 0) {
	fprintf (stdout, "\n%s\n%s", bin2hex (buffer, n), buffer);
    }

    if (strlen(buffer) > 0) {
	printf("recieved: \n%s\n", buffer);
    }

    n = write (fsockd, "i got your message. \n", 18);
    
    return 0;
}
