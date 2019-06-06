
#ifndef UDP_H
#define UDP_H

#define DEFAULT_PORT 49161

/*
Start a UDP server running
*/
void startUDP(int port);

/*
Waits for a UDP packet to be received and then callls back with the 
packet contents with the callback function pointer method
*/
void receiveUDP(void (*packetReceived)(char *, int));

#endif