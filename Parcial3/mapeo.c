#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int pid;
    int *var = malloc(sizeof(int));
	printf("OMG\n");
	pid = fork();
	if(pid > 0){//Padre
		printf("Proceso 1 (PADRE)\n");
        printf("%d\n", getpid()); // getpid() retorna el id del hilo main y gettid() retorna en id del subhilo
            while (1)
            {

            }
    }else//Hijo
		if(pid == 0){
			printf("Proceso 2 (HIJO)\n");
            printf("%d\n", getpid()); // getpid() retorna el id del hilo main y gettid() retorna en id del subhilo
            while (1)
            {
                int *var = malloc(sizeof(int)*10000000);
                printf("S\n");
                sleep(1);
                //free(var);
            }
		}else{
			printf("Error de fork\n");
			exit(-1);
		}
	printf("Hola Mundo\n");
	return 0;
}
