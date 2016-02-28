#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>    /* Internet domain header */
#include "wrapsock.h"

#ifndef PORT
#define PORT 30000
#endif
#define LISTENQ 10


int main(int argc, char **argv) {
    int  maxfd, listenfd, connfd;
    int nready, counter, ncounter;
    fd_set	rset, allset;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    int yes = 1;
    struct timeval timeout;
    fprintf(stderr, "Port = %d\n", PORT);

    listenfd = Socket(PF_INET, SOCK_STREAM, 0);

    memset(&servaddr, '\0', sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT);

    if((setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1) {
        perror("setsockopt");
    }

    Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    // We are accepting only 1 connection, so the 'accept' is not
    // in the 'select' loop
    
    clilen = sizeof(cliaddr);
    connfd = Accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        
    maxfd = connfd;

    FD_ZERO(&allset); //Init set
    FD_SET(connfd, &allset);
    counter = 10;

    for ( ; ; ) {
        rset = allset;		/* structure assignment */
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        nready = Select(maxfd+1, &rset, NULL, NULL, &timeout);

        if(nready == 0 && counter > 0) { //timeout occurred
            counter--;
            printf("%d\n", counter);
            // Write the counter to the client.
            ncounter = htons(counter);
            if(write(connfd, &ncounter, sizeof(int)) != sizeof(int)) {
                perror("write");
            }
            if(counter <= 0) {
                printf("Kaboom\n");
                exit(0);
            }
        }

        if (FD_ISSET(connfd, &rset)) {	
	    fprintf(stderr, "reading from client\n");
            if(read(connfd, &ncounter, sizeof(int)) != sizeof(int)) {
                fprintf(stderr, "Client closed or error\n");
                exit(1);
            } 
            counter = ntohs(ncounter);
        }
    }
}
