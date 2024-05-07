#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void *h1(void *);

int boleto = 0, boletos[5];
pthread_mutex_t lock;

int main()
{
    // Los hilos son procesos q se ejecutan infinitamente
    pthread_t hilos[10];
    printf("Hilo main\n\n");
    int clientes[10];

    for(int i=0; i<10; i++){
        boletos[i] = 0;//Inicializa los boletos en 0
        clientes[i] = i;
    }

    pthread_mutex_init( &lock, NULL); //Buen lugar para inicilizar candados (antes de ejecutar las hilos)
    for (int i = 0; i < 10 ; i++)
        pthread_create(&hilos[i], NULL, h1, (void *)&clientes[i]); // hilo_1 ejectuta el mismo codigo
    
    for (int j = 0; j < 10 ; j++)
        pthread_join(hilos[j], NULL);// Detiene a main, misma funcion que el wait()

    printf("fin de main\n");
    return 0;
}

void *h1(void *s)
{
    int i = *(int *)s;

    printf("Cliente: %d   ", i+1);

    pthread_mutex_lock( &lock );//Manda a dormir los otros hilos hasta que se termine de ejecutar el candado
    if (boletos[boleto] == 0 && boleto < 5){
        printf("Boleto: %d\n", boleto+1);
        boletos[boleto] = 1;
        boleto++;
    }else
        printf("Boletos VENDIDOS\n");
    pthread_mutex_unlock( &lock );

    pthread_exit(NULL);
}