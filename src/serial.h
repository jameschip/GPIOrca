
#ifndef SERIAL_H
#define SERIAL_H

#define DEFAULT_SERIAL "/dev/ttyACM0"

void openPort(char * port);
void closePort(void);
void sendData(char * buf, int n);

#endif