#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int pid;
	pid = fork();
	if(pid > 0){//Proceso PADRE
		printf("PADRE: Iniciado\n");
		wait(NULL);//Espera a que finalice el proceso hijo
		printf("PADRE: Durmiendo...\n");
		sleep(15);
		printf("PADRE: Despertado\n");
		printf("PADRE: Terminado\n");
		exit(1);
	}else{//Proceso HIJO
		printf("HIJO: Iniciado\n");
		printf("HIJO: Durmiendo...\n");
		sleep(15);
		printf("HIJO Despertado\n");
		exit(1);
		printf("HIJO: Terminado\n");
	}
	return EXIT_SUCCESS;
}