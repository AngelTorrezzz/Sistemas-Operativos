#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>                                                             
#include <unistd.h>
#include <string.h>

typedef struct persona {
    char nombre[50];
    int edad;
    float altura;
}Persona;

void *proceso_1(void *s){  
   printf("soy un proceso delgado mejor conocido como Hilo o Thread\n");
   pthread_exit(NULL);
}

 
void *proceso_2(void *parametro){  
   printf("Yo soy otro Hilo o Thread\n");
   Persona *persona1 = (Persona *)parametro; //Convierte el apuntador void al apuntador entero por medio del cast
   printf("PERSONA 1:\n");
   printf("Nombre: %s\n", persona1->nombre);
   printf("Edad: %d\n", persona1->edad);
   printf("Altura: %f\n", persona1->altura);
   pthread_exit(NULL);
}


int main()
{
    Persona persona1;

    strcpy(persona1.nombre, "pelon");
    persona1.edad = 15;
    persona1.altura = 1.50;

   //int k = 25;
   pthread_t hilo_1, hilo_2; //Variables de tipo hilo
   pthread_create(&hilo_1, NULL, proceso_1, NULL);
   pthread_create(&hilo_2, NULL, proceso_2, (void *)&persona1); //Convierte el argumento a apuntador de tipo void para que sean compatibles
   pthread_join(hilo_1, NULL);
   pthread_join(hilo_2, NULL);
   printf("fin de main\n");
   return 0;
}