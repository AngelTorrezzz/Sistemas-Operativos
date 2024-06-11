#include <stdio.h>
#include <signal.h>

void capturar_control_c(int signal){
    printf("El usuario no me quiere\n");
}

int main(){
    //int k;
    char op;
    char señal[20];
    printf("%d\n", getpid());
    do{
        signal(SIGINT, capturar_control_c);
        printf("Introduce la señal que deseas mandar: \n");

        getchar();
        printf("¿Desea mandar otra señal? (s/n)\n");
        __fpurge(stdin);
        scanf("%c",&op);
        printf("%s\n",&op);
    }while (op == 's');
    return 0;
}