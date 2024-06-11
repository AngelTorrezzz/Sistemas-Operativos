#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void capturar_control_c(int signal){
    printf("El usuario no me quiere\n");
    //exit(1);
}

int main(){
    //int k;
    signal(SIGINT, capturar_control_c);
    printf("%d\n", getpid());
    while(1){

    }
    //k++;
    return 0;
}