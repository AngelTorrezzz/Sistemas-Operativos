#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int pid;
	printf("OMG\n");
	pid = fork();
	if(pid > 0)//Padre
		printf("Proceso 1 (PADRE)\n");
	else
		if(pid == 0)
			printf("Proceso 2 (HIJO)\n");
		else{
			printf("Error de fork\n");
			exit(-1);
		}
	printf("Hola Mundo\n");
	return 0;
}
