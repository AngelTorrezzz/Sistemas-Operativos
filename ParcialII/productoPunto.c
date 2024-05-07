#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>                                                             
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct arreglos {
    int mat1[100000],mat2[100000],mat3[100000],mat4[100000];
}Arreglos;

void * hilocode (void *);
void * hilocode2 (void *);
double Producto(int[], int[]);
void LlenarArreglos(Arreglos*);

int main(){
    pthread_t hilo_1, hilo_2; //Variables de tipo hilo
    clock_t inicio, fin;//Variables para medir el tiempo
    double tiempo, resultado;

    //Llenar arreglos
    Arreglos arreglos;
    LlenarArreglos(&arreglos);
    //for(int i=0; i<10; i++)
    //    printf("mat1[%d] = %.0f\n", i, arreglos.mat1[i]);

    //CON HILOS
    printf("CON HILOS.-\n");
    //A·B
    inicio = clock();
    pthread_create(&hilo_1, NULL, hilocode, (void *)&arreglos);
    pthread_join(hilo_1, NULL);
    //C·D
    pthread_create(&hilo_2, NULL, hilocode2, (void *)&arreglos);
    pthread_join(hilo_2, NULL);
    fin = clock();
    tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo: %f\n",tiempo);

    
    //SIN HILOS
    printf("\n\nSIN HILOS\n");
    //A·B
    inicio = clock();
    resultado = Producto(arreglos.mat1, arreglos.mat2);
    printf("Producto Punto A·B = %.0f\n", resultado);
    //C·D
    resultado = Producto(arreglos.mat3, arreglos.mat4);
    printf("Producto Punto C·D = %.0f\n", resultado);
    fin = clock();
    tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo: %f\n",tiempo);

    printf("\nFin de main\n");
    return 0;
}

void LlenarArreglos(Arreglos *arreglos){
    int tam = sizeof(arreglos->mat1) / sizeof(arreglos->mat1[0]); //Calcula el tamaño del arreglo
    //printf("Tamaño: %d\n", tam);
    
    //Inicializamos la semilla del generador de números aleatorios
    srand(time(NULL));
    for (int i = 0; i < tam; i++) {
        arreglos->mat1[i] = rand() % 10000; // Genera números aleatorios entre 0 y 9999
        arreglos->mat2[i] = rand() % 10000; // Genera números aleatorios entre 0 y 9999
        arreglos->mat3[i] = rand() % 10000; // Genera números aleatorios entre 0 y 9999
        arreglos->mat4[i] = rand() % 10000; // Genera números aleatorios entre 0 y 9999
        //printf("mat1[%d] = %.0f\n", i, arreglos.mat1[i]);
    }
}

void *hilocode(void *s){
    Arreglos *arreglos = (Arreglos *)s;//Recuperamos los argumentos q se enviaron en el hilo
    double resultado = 0;

    int tam = sizeof(arreglos->mat1) / sizeof(arreglos->mat1[0]); //Calcula el tamaño del arreglo

    resultado = Producto(arreglos->mat1, arreglos->mat2);
    //for (int i = 0; i < tam; i++)
    //    resultado = resultado + (arreglos->mat1[i] * arreglos->mat2[i]);

    printf("Producto Punto A·B = %.0f\n", resultado);
    pthread_exit(NULL);
}

void *hilocode2(void *s){
    double resultado;

    //Recuperamos los argumentos q se enviaron en el hilo
    Arreglos *arreglos = (Arreglos *)s;

    resultado = Producto(arreglos->mat3, arreglos->mat4);

    printf("Producto Punto C·D = %.0f\n", resultado);
    pthread_exit(NULL);
}

double Producto(int mat1[], int mat2[]){
    int tam = sizeof(mat1) / sizeof(mat1[0]); //Calcula el tamaño del arreglo
    double resultado = 0;

    for (int i = 0; i < tam; i++)
        resultado = resultado + (mat1[i] * mat2[i]);

    return resultado;
}