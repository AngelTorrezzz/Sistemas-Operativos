#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *esperar_amigo(void *);

#define HILOS 4
#define SEMAFORO 4

sem_t semaforo;

int numHilo = 1;
int x = 0;
int cuentaHilo = 4;

int main(){
    int k;
    pthread_t hilo[ HILOS ];
    
    sem_init( &semaforo,
              0,//Semaforo entre hilos
              SEMAFORO//Valor inicial del contador
    );//Buen lugar para inicializar un semaforo

    for( k = 0; k < HILOS; k++){
        //TAMBIEN PUEDE SER CON UN ARREGLO INDEPENDIENTE DEL CICLO
        int *numHilo_copia = malloc(sizeof(int)); // Crear una copia de numHilo para cada hilo
        *numHilo_copia = numHilo; // Asignar el valor actual de numHilo a la copia
        //printf("%d\n", *numHilo_copia); // Imprimir el valor de la copia
        pthread_create( &hilo[ k ], NULL, esperar_amigo, (void *)numHilo_copia); // Pasar la copia al hilo
        numHilo++;
    }

    for( k = 0; k < HILOS; k++){
        pthread_join( hilo[ k ], NULL);
    }

    sem_destroy( &semaforo );//Liberar el semaforo

    printf("Fin hilo principal\n");
    return 0;
}

void *esperar_amigo(void *s){
    int *hilo = (int *)s;
    
    sem_wait( &semaforo );//Decrementa contador en 1
    printf("Soy El Amigo: %d\n", *hilo);
    cuentaHilo--;
    //printf("CuentaHilo: %d\n", cuentaHilo);
    if(cuentaHilo == 0){
        printf("Soy El Amigo: %d, soy el ultimo y liberare a mis amigos\n", *hilo);
        x = -1;
    }
    while(x==-1)
        x++;  
    sem_post( &semaforo );//Incrementa contador en 1

    pthread_exit(NULL);
}
