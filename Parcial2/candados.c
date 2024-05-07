#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void *h1(void *); // Prototipo de la funcion

int saldo = 500;      // Variable global
pthread_mutex_t lock; // Candado

int main()
{
    // Los hilos son procesos q se ejecutan infinitamente
    pthread_t hilos[2];// Se puede hacer un arreglo de hilos
    printf("Hilo main\n");// Se ejecuta en el hilo principal
    printf("SALDO = %d\n\n", saldo);
    int clientes[2] = {1, 2};
    int tamano = sizeof(clientes) / sizeof(clientes[0]);
    //printf("Tamano: %d\n", tamano);

    pthread_mutex_init(&lock, NULL); // Buen lugar para inicilizar candados (antes de ejecutar los hilos)
    for (int i = 0; i < tamano; i++)
        pthread_create(&hilos[i], NULL, h1, (void *)&clientes[i]); // hilo_1 ejectuta el mismo codigo

    for (int j = 0; j < tamano; j++)
        pthread_join(hilos[j], NULL); // Detiene a main, misma funcion que el wait()

    printf("\nSALDO = %d\n", saldo);
    printf("fin de main\n");
    return 0;
}

void *h1(void *s)
{
    int cliente = *(int *)s;
    printf("Cliente entrante: %d\n", cliente);

    pthread_mutex_lock(&lock); // Manda a dormir los otros hilos hasta que se termine de ejecutar el candado
    if (saldo >= 500)
    {
        //sleep(1); //Se puso para simular el ejemplo donde se retira dos veces
        saldo = saldo - 500;
        printf("El cliente %d hizo un retiro exitoso\n", cliente);
    }
    else
        printf("El cliente %d NO hizo un retiro exitoso \n", cliente);
    pthread_mutex_unlock(&lock); // Debe cerrarse SI O SI MAK

    pthread_exit(NULL);
}