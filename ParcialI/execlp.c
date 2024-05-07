#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int pid = fork();
    if( pid == 0 ){
        printf("HIJO: Iniciado\n");
        printf("HIJO: Ejecutando ls\n");
        execlp("ls", "ls", "-lh", NULL);
        printf("HIJO: Terminado.\n");
    }
    else{
        printf("PADRE: Inciado\n");
        printf("PADRE: Esperando...\n");
        wait( NULL );
        printf("PADRE: Terminado.\n");
        exit(0);
    }
    return 0;
}
