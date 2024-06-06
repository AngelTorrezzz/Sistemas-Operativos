#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

/*
Escriba un programa con un proceso padre y un proceso hijo. Cuando el proceso hijo tarde mas de 10 segundos
en terminar, el proceso padre enviara la señal 9 a su proceso hijo.

Explique el funcionamiento de la funcion pause. Muestre y explique un ejemplo del uso de esta función.
*/

void matarHijo( int signal )
{
    kill(getpid(), signal);
}

int main()
{
    pid_t pid;
    clock_t inicio, fin; // Variables para medir el tiempo
    double tiempo;
    struct sigaction act;
    sigset_t mask;

    act.sa_handler = matarHijo;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0; // ninguna accion especifica

    pid = fork();
    if (pid > 0)
    { // Proceso PADRE
        printf("PADRE: Iniciado pid: %d\n", getpid());
        inicio = clock();
        int bandera = 1;
        while ( bandera == 1)
        {
            fin = clock();
            tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
            // printf("%.1f\n", tiempo);
            if (tiempo >= 5)
            {
                //printf("Matar Hijo\n");
                if (kill(pid, SIGINT) == -1)
                {
                    perror("Error al enviar la señal al proceso hijo");
                    exit(EXIT_FAILURE);
                }
                printf("Señal enviada al proceso hijo.\n");
                bandera = 0;
                printf("Bander: %d\n", bandera);
            }
        }
        while(1){
            printf("Estoy en el proceso Padre");
            sleep(1);
        }
    }
    else
    { // Proceso HIJO
        printf("HIJO: Iniciado pid: %d\n", getpid());
        signal(SIGKILL, matarHijo);
        while(1){
            
        }
        //sigaction(SIGALRM, &act, NULL);
        //pause();
        //alarm(1);
    }
    return EXIT_SUCCESS;
}