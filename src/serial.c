#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PERR -1

struct termios options_old;
struct termios options;

int fd;	

void openPort(char * port){
    fd = open(port, O_RDWR | O_NOCTTY );
	if (fd == PERR)
	{
		perror("openPort: Unable to open port");
	} 
	else
	{
		fcntl(fd, F_SETFL, 0);
		tcgetattr(fd, &options);
        tcgetattr(fd, &options_old);
		cfsetispeed(&options, B19200);
		options.c_cflag |= (CLOCAL | CREAD);
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8;
		cfmakeraw(&options);
		tcsetattr(fd, TCSANOW, &options);
	}
}

void closePort(void) {
    tcsetattr(fd, TCSANOW, &options_old);
    if(close(fd) == PERR)
	{	
		perror("closePort: Unable to close port");
	}
}

void sendData(char * buf, int n) {
    int bytes;
	
	bytes = write(fd, buf, n);
	if(bytes == PERR)
	{
		perror("writeData: Error while trying to write data - ");	
	}
	else if(bytes != n)
	{
		printf("only %u bytes written out of %u requested\n", bytes, n);	
	}
}