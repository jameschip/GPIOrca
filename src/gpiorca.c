#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "udp.h"
#include "parse.h"

/*
Processes the command line options and sets the apropriate values
*/
void processOptions(int ac, char **av);

/*
Method that will be used as a callback when a UDP packet has been received
*/
void packetReceived(char * buf, int n);

int portNumber = DEFAULT_PORT;

parse_r parse_result;

int main(int argc, char **argv) {
    printf("Starting GPIOrca!\n");
    processOptions(argc, argv);
    startUDP(portNumber);
    while(1) {
        receiveUDP(&packetReceived);
    }
    return 0;
}

void packetReceived(char * buf, int n) {
    if (parseBuffer(buf, n, &parse_result) != -1) {
        printf("match\n");
        fflush(stdout);
    } 
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
        if ((c = getopt_long(ac, av, "p:", long_options, &option_index)) != -1) {
            switch (c)
            { 
            case 'p':
                printf("port option set.\n");
                portNumber = atoi(optarg);
            break;
            default:
                return;
            }
        } 
    }
}

