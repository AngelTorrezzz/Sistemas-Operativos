#include <stdio.h>
#include <signal.h>

void capturar_control_c(int signal){
    printf("El usuario no me quiere\n");
}

int main(){
    //int k;
    int op;
    char señal[20];
    do{

        printf("¿Desea mandar otra señal?\n");
        printf("op == 1 SI  |   op != 1 SALIR\n\n");
        printf("op:");
        scanf("%d",op);
    }while (op == 1);
    return 0;
}