#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>    
#include <netdb.h>
#include "wrapsock.h"

#ifndef PORT
#define PORT 30000
#endif

#define BUF_SIZE 256

int main(int argc, char* argv[])
{ 
    int sockfd;
    char buf[BUF_SIZE];
    struct sockaddr_in server;
    fd_set allset, rset;
    int nready, maxfd, nread, err;
    int server_counter;
    char port[10];    
    struct addrinfo *info, hints;

    sprintf (port, "%d", PORT);
    
    memset (&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ( argc != 2 ) {    
        fprintf(stderr, "Usage: %s hostname\n", argv[0]);
        exit(1);
    }

    /* fill in peer address */
    if ((err = getaddrinfo(argv[1], port, &hints, &info))) {
        fprintf (stderr, "%s: %s\n", argv[0], gai_strerror(err));
        exit (1);
    }
    server = *(struct sockaddr_in *)(info->ai_addr);
    
    printf("PORT = %d\n", PORT);


    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    Connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    FD_ZERO(&allset);				/* empty the FD set */
    FD_SET(sockfd, &allset);		/* add the socket */
    FD_SET(STDIN_FILENO, &allset);	/* add standard input */

    /*sockfd is guaranteed to be bigger than STDIN_FILENO*/
    maxfd = sockfd;
                                    

    while(1) {
        rset = allset;
        // prompt user to type a number
        fprintf(stderr, "Enter a number: \n");
        
        // use select to multiplex between stdin and the socket.
        // timeout should be NULL
        
        // Add code here
        
        

    }

    Close(sockfd); 
    return(0);
}

/* Printf statements to insert into your code:
 printf("Counter is %d\n", server_counter);
 fprintf(stderr, "Server Terminated, closing connection\n");
 fprintf(stderr, "Read Error from server, closing connection\n");
 fprintf(stderr,"Error reading from stdin\n");
*/
