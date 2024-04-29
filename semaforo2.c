#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

void *mesa(void *);

#define HILOS 3
#define SEMAFORO 1

sem_t semaforo;

int numHilo = 1;

int main(){
    int k;
    pthread_t hilo[ HILOS ];
    
    sem_init( &semaforo,
              0,//Semaforo entre hilos
              SEMAFORO//Valor inicial del contador
    );

    for( k = 0; k < HILOS; k++){
        //TAMBIEN PUEDE SER CON UN ARREGLO INDEPENDIENTE DEL CICLO
        int *numHilo_copia = malloc(sizeof(int)); // Crear una copia de numHilo para cada hilo
        *numHilo_copia = numHilo; // Asignar el valor actual de numHilo a la copia
        printf("%d\n", *numHilo_copia); // Imprimir el valor de la copia
        pthread_create( &hilo[ k ], NULL, mesa, (void *)numHilo_copia); // Pasar la copia al hilo
        numHilo++;
    }

    for( k = 0; k < HILOS; k++){
        pthread_join( hilo[ k ], NULL);
    }

    sem_destroy( &semaforo );

    printf("Fin hilo principal\n");
    return 0;
}

void *mesa(void *s){
    int *hilo = (int *)s;
    
    sem_wait( &semaforo );//Decrementa contador en 1
    printf("Soy el hilo: %d\n", *hilo);
    sem_post( &semaforo );//Incrementa contador en 1

    pthread_exit(NULL);
}
