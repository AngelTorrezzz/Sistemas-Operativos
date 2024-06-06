#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void tratar_alarma(  ){
    static int c;
    printf("Alarma ativada = %d\n", c++);
    alarm(1);
}

int main( void ){
    //Investigar la estructura sigaction
    //QUE LO NO LO ACEPTE Y DESPUES QUE SI LO HAGA
    struct sigaction act;
    sigset_t mask;

    /*especifica el manejador*/

    act.sa_handler = tratar_alarma;     //funcion a ejecutar
        //sa_handler    = SIG_DFL para la accion por defecto
        //              = SIG_ING para ignorar la señal
        //              = Controlar que responderá a la señal
    act.sa_restorer = NULL; //obsoleto, no se debe utilizar
    act.sa_flags = 0;   //ninguna accion especifica

    /*inicia configuracion de bloqueo de la señal 2 SIGINT*/
    sigemptyset( &mask );
    //sigaddset( &mask, SIGINT );//Ya no responde al ctrl-c
    //sigaddset( &mask, SIGTSTP );//Ya no responde al ctrl-z
    //sigprocmask( SIG_SETMASK, &mask, NULL );
    /*termina configuracion de bloqueo*/
    
    sigaction( SIGALRM, &act, NULL );
    alarm(1);

    while(1){
        sleep(1);
        printf("Hola mundo\n");
    }
}