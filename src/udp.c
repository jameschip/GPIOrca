#include <stdio.h>
#include <stdlib.h>     
#include <string.h>     
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <netdb.h>

#include "udp.h"

#define BUF_SIZE 100

int socketfd;
int clientLength;
struct sockaddr_in server; 
struct sockaddr_in client; 
struct hostent *hostp; 
char *buf;

void startUDP(int port) {
    
    buf = malloc(BUF_SIZE);

    if ( (socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("Failed to create socket"); 
        exit(EXIT_FAILURE); 
    } 

    int optval = 1;
	setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(port); 
    
    if ( bind(socketfd, (const struct sockaddr *)&server, sizeof(server)) < 0 ) 
    { 
        perror("Failed to bind server socket."); 
        exit(EXIT_FAILURE); 
    }

    clientLength = sizeof(client);

}

void receiveUDP(void (*packetReceived)(char *, int)) {
    int n = recvfrom(socketfd, buf, BUF_SIZE, 0, (struct sockaddr *)&client, &clientLength);
    if (n < 0)
        perror("ERROR in recvfrom");

    /* 
        * gethostbyaddr: determine who sent the datagram
        */
    hostp = gethostbyaddr((const char *)&client.sin_addr.s_addr, sizeof(client.sin_addr.s_addr), AF_INET);
    if (hostp == NULL) {
        perror("ERROR on gethostbyaddr\n");
        //exit(EXIT_FAILURE);
    }
    char *hostaddrp = inet_ntoa(client.sin_addr);
    if (hostaddrp == NULL) {
        perror("ERROR on inet_ntoa\n");
    }

    packetReceived(buf, n); // Callback with buffer

    
}