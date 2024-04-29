#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

void *mesa(void *);

#define CLIENTES 7
#define LUGARES_EN_LA_MESA 3

sem_t semaforo;

unsigned int x = 0;

int main(){
    int k;
    pthread_t hilo[ CLIENTES ];
    
    //Buen lugar para inicializar un semaforo
    sem_init( &semaforo,
              0,//0 Semaforo entre hilos. 1 Smaforo entre procesos
              LUGARES_EN_LA_MESA//Valor inicial del contador
    );

    for( k = 0; k < CLIENTES; k++){
        //TAMBIEN PUEDE SER CON UN ARREGLO INDEPENDIENTE DEL CICLO
        int *cliente = malloc(sizeof(int)); // Crear una copia de k para cada hilo
        *cliente = k; // Asignar el valor actual de k a la copia
        pthread_create( &hilo[ k ], NULL, mesa, (void *)cliente); // Pasar la copia al hilo
    }

    for( k = 0; k < CLIENTES; k++){
        pthread_join( hilo[ k ], NULL);
    }

    //Buen lugar para liberar el semaforo que se ocupo
    sem_destroy( &semaforo );

    printf("Fin hilo principal\n");
    return 0;
}

void *mesa(void *s){
    
    int cliente = *(int *)s;

    sem_wait( &semaforo );//Decrementa contador en 1
    printf("Cliente: %d\n",cliente);
    while(1)
        x++;    
    sem_post( &semaforo );//Incrementa contador en 1

    pthread_exit(NULL);
}
