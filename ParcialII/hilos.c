#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void *proceso_1(void *);
void *proceso_2(void *);

typedef struct persona
{
   char nombre[50];
   int edad;
   float altura;
} Persona;

int main()
{
   Persona persona1;

   strcpy(persona1.nombre, "Pelon");
   persona1.edad = 15;
   persona1.altura = 1.75;

   // int k = 25;
   pthread_t hilo_1, hilo_2; // Variables de tipo hilo
   pthread_create(&hilo_1, NULL, proceso_1, NULL);
   pthread_create(&hilo_2, NULL, proceso_2, (void *)&persona1); // Convierte el argumento a apuntador de tipo void para que sean compatibles
   pthread_join(hilo_1, NULL);
   pthread_join(hilo_2, NULL);
   printf("fin de main\n");
   return 0;
}

void *proceso_1(void *s)
{
   printf("Hilo 1\n");
   pthread_exit(NULL);
}

void *proceso_2(void *parametro)
{
   printf("Hilo 2\n");
   Persona *persona = (Persona *)parametro; // Convierte el apuntador void al apuntador entero por medio del cast
   printf("Nombre: %s\n", persona->nombre);
   printf("Edad: %d\n", persona->edad);
   printf("Altura: %.2f\n", persona->altura);
   pthread_exit(NULL);
}