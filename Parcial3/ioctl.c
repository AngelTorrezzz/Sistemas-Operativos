#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

int main(){
	int fd, serial;
	fd = open("/dev/ttyS5", 1);
	ioctl(fd, TIOCMGET, &serial);
	if(serial &TIOCM_DTR)
		printf("Encendido\n");
	else
		printf("Apagado\n");

	return 0;
}