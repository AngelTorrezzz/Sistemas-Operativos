#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void capturar_control_c(int signal){
    printf("El usuario no me quiere\n");
    //exit(1);
}

int main(){
    //signal(SIGINT, capturar_control_c);

    struct sigaction sa;
    sa.sa_handler = capturar_control_c;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    printf("%d\n", getpid());
    while(1){

    }

    return 0;
}