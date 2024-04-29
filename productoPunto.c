#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>                                                             
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct arreglos {
    double mat1[100000],mat2[100000],mat3[100000],mat4[100000];
}Arreglos;

void * hilocode (void *);
double Producto(double[], double[]);
void LlenarArreglos(Arreglos *);

int main(){
    pthread_t hilo_1, hilo_2; //Variables de tipo hilo
    clock_t inicio, fin;
    double tiempo, resultado;

    char uno[10], dos[10];
    strcpy(uno, "A·B");
    strcpy(dos, "C·D");

    //Llenar arreglos
    Arreglos arreglos;
    LlenarArreglos(&arreglos);

    //CON HILOS
    printf("CON HILOS.-\n");
    //A·B
    inicio = clock();
    pthread_create(&hilo_1, NULL, hilocode, (void *)&uno);
    pthread_join(hilo_1, NULL);
    fin = clock();
    tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo: %f\n",tiempo);
    //C·D
    inicio = clock();
    pthread_create(&hilo_2, NULL, hilocode, (void *)&dos);
    pthread_join(hilo_2, NULL);
    fin = clock();
    tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo: %f\n",tiempo);


    //SIN HILOS
    printf("\n\nSIN HILOS\n");
    printf("Producto Punto A·B\n");
    inicio = clock();
    resultado = Producto(mat1, mat2);
    fin = clock();
    tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo: %f\n",tiempo);

    printf("Producto Punto C·D\n");
    inicio = clock();
    resultado = Producto(mat1, mat2);
    fin = clock();
    tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo: %f\n",tiempo);
    printf("\nFin de main\n");
    return 0;
}

void LlenarArreglos(Arreglos arreglos*){
    int tam = sizeof(arreglos.mat1) / sizeof(arreglos.mat1[0]); //Calcula el tamaño del arreglo
    
    //Inicializamos la semilla del generador de números aleatorios
    srand(time(NULL));
    for (int i = 0; i < tam; i++) {
        mat1[i] = rand() % 10000; // Genera números aleatorios entre 0 y 9999
        mat2[i] = rand() % 10000; // Genera números aleatorios entre 0 y 9999
        mat3[i] = rand() % 10000; // Genera números aleatorios entre 0 y 9999
        mat4[i] = rand() % 10000; // Genera números aleatorios entre 0 y 9999
    }
}

void *hilocode(void *s){
    char nombre[10];
    double resultado;

    //Recuperamos los argumentos q se enviaron en el hilo
    strcpy(nombre, (char*)s);

    resultado = Producto(mat1, mat2);

    printf("Producto Punto %s = %.0f\n", nombre, resultado);
    pthread_exit(NULL);
}

double Producto(double mat1[], double mat2[]){
    int tam = sizeof(mat1) / sizeof(mat1[0]); //Calcula el tamaño del arreglo
    double resultado = 0;

    for (int i = 0; i < tam; i++)
        resultado = resultado + (mat1[i] * mat2[i]);
    return resultado;
}