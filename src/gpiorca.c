#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "serial.h"
#include "udp.h"

void processOptions(int ac, char **av);

void packetReceived(char * buf, int n);

int portNumber = DEFAULT_PORT;

char * serialPort = DEFAULT_SERIAL;

int main(int argc, char **argv) {
    printf("Starting GPIOrca!\n");
    processOptions(argc, argv);
    startUDP(portNumber);
    openPort(serialPort);
    while(1) {
        receiveUDP(&packetReceived);
    }
    return 0;
}

void packetReceived(char * buf, int n) {
    if(fwrite(buf, sizeof(char), n, stdout) != n) {
        perror("fwrite");
    }
    sendData(buf, n);
}

void processOptions(int ac, char **av) {
    struct option long_options[] = {
        {"port", required_argument, 0, 'p'},
        {0, 0, 0, 0}
    };

    while (optind < ac)
    {
        int option_index = 0;
        // auto c = getopt_long(ac, av, "hdplri:", long_options, &option_index);
        int c;
        if ((c = getopt_long(ac, av, "p:s:", long_options, &option_index)) != -1) {
            switch (c)
            { 
            case 'p':
                printf("port option set.\n");
                portNumber = atoi(optarg);
            break;
            case 's':
                printf("port option set.\n");
                serialPort = optarg;
                break;
            default:
                return;
            }
        } 
    }
}

