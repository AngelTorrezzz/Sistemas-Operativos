#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANO_PAGINA 4096
#define MEMORIA_TOTAL 32768
#define NUM_MARCOS (MEMORIA_TOTAL / TAMANO_PAGINA)

typedef struct {
    int pid;
    int numero_pagina;
    int *tabla_pagina;
} Proceso;

typedef struct {
    int id_proceso;
    int numero_pagina;
} Marco;

Marco marcos[NUM_MARCOS];
Proceso *procesos[100];
int contador_procesos = 0;
Proceso *procesos_en_espera[100];
int contador_espera = 0;
Proceso *procesos_completados[100];
int contador_completados = 0;

int suficienteMemoria(int numero_pagina) {
    int marcos_disponibles = 0;
    for (int i = 0; i < NUM_MARCOS; i++) {
        if (marcos[i].id_proceso == -1) {
            marcos_disponibles++;
        }
    }
    return marcos_disponibles >= numero_pagina;//retorna 1 si hay suficiente memoria
}

int encontrarMarcoLibre() {
    for (int i = 0; i < NUM_MARCOS; i++) {
        if (marcos[i].id_proceso == -1) {
            return i;
        }
    }
    return -1;
}

void asignarMemoria(Proceso *proceso) {
    for (int i = 0; i < proceso->numero_pagina; i++) {
        int marco = encontrarMarcoLibre();
        if (marco != -1) {
            marcos[marco].id_proceso = proceso->pid;
            marcos[marco].numero_pagina = i;
            proceso->tabla_pagina[i] = marco;
        }
    }
}

void memoriaLibre(Proceso *proceso) {
    for (int i = 0; i < proceso->numero_pagina; i++) {
        int marco = proceso->tabla_pagina[i];
        marcos[marco].id_proceso = -1;
        marcos[marco].numero_pagina = -1;
    }
}

void asignarProcesosEnEspera() {
    int i = 0;
    while (i < contador_espera) {
        if (suficienteMemoria(procesos_en_espera[i]->numero_pagina)) {
            asignarMemoria(procesos_en_espera[i]);
            procesos[contador_procesos++] = procesos_en_espera[i];
            for (int j = i; j < contador_espera - 1; j++) {
                procesos_en_espera[j] = procesos_en_espera[j + 1];
            }
            contador_espera--;
        } else {
            i++;
        }
    }
}

void agregarProceso(int pid, int numero_pagina) {
    Proceso *proceso = (Proceso *)malloc(sizeof(Proceso));
    proceso->pid = pid;
    proceso->numero_pagina = numero_pagina;
    proceso->tabla_pagina = (int *)malloc(numero_pagina * sizeof(int));
    if (suficienteMemoria(numero_pagina)) {
        asignarMemoria(proceso);
        procesos[contador_procesos++] = proceso;
    } else {
        procesos_en_espera[contador_espera++] = proceso;
    }
}

void terminarProceso(int pid) {
    for (int i = 0; i < contador_procesos; i++) {
        if (procesos[i]->pid == pid) {
            memoriaLibre(procesos[i]);
            procesos_completados[contador_completados++] = procesos[i];
            for (int j = i; j < contador_procesos - 1; j++) {
                procesos[j] = procesos[j + 1];
            }
            contador_procesos--;
            asignarProcesosEnEspera();
            break;
        }
    }
}

void mostrar() {
    printf("\nProcesos en Ejecucion:\n");
    for (int i = 0; i < contador_procesos; i++) {
        printf(" - ID: %d, Paginas: %d\n", procesos[i]->pid, procesos[i]->numero_pagina);
    }

    printf("\nEstado de la Memoria:\n");
    for (int i = 0; i < NUM_MARCOS; i++) {
        if (marcos[i].id_proceso == -1) {
            printf("Marco %d: Libre\n", i);
        } else {
            printf("Marco %d: Proceso %d, Pagina %d\n", i, marcos[i].id_proceso, marcos[i].numero_pagina);
        }
    }

    printf("\nProcesos Esperando Memoria:\n");
    for (int i = 0; i < contador_espera; i++) {
        printf(" - ID: %d, Paginas: %d\n", procesos_en_espera[i]->pid, procesos_en_espera[i]->numero_pagina);
    }

    printf("\nProcesos Completados:\n");
    for (int i = 0; i < contador_completados; i++) {
        printf(" - ID: %d, Paginas: %d\n", procesos_completados[i]->pid, procesos_completados[i]->numero_pagina);
    }
}

void MostrarMemoria(){
    printf("\nEstado de la Memoria:\n");
    for (int i = 0; i < NUM_MARCOS; i++) {
        if (marcos[i].id_proceso == -1) {
            printf("Marco %d: Libre\n", i);
        } else {
            printf("Marco %d: Proceso %d, Pagina %d\n", i, marcos[i].id_proceso, marcos[i].numero_pagina);
        }
    }
}

int main() {
    // Initialize marcos
    for (int i = 0; i < NUM_MARCOS; i++) {
        marcos[i].id_proceso = -1;
        marcos[i].numero_pagina = -1;
    }

    int option, pid, numero_pagina;
    while (1) {
        printf("\nMenu de Opciones:\n");
        printf("1. Agregar Proceso\n");
        printf("2. Terminar Proceso\n");
        printf("3. Mostrar Memoria\n");
        printf("4. Salir\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Ingrese ID: ");
                scanf("%d", &pid);
                printf("# de Paginas: ");
                scanf("%d", &numero_pagina);
                agregarProceso(pid, numero_pagina);
                mostrar();
                break;
            case 2:
                printf("ID del proceso a terminar: ");
                scanf("%d", &pid);
                terminarProceso(pid);
                mostrar();
                break;
            case 3:
                MostrarMemoria();
                break;
            case 4:
                printf("Saliendo...\n");
                return 0;
            default:
                printf("Opcion Invalida :( Intente otra vez.\n");
        }
    }

    return 0;
}
