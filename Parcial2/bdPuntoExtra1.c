#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    unsigned int clave; // se utiliza para identificación de la tupla
    char nombre[21],
         telefono[11];
    double sueldo;
} Empleado;

int main(){
    Empleado empleado;
    
    int fd = open("db.personas", O_RDONLY );
    int tamanoArchivo = lseek( fd, 0, SEEK_END );// Obtiene el tamaño del archivo
    //parametros de lseek: descriptor de archivo, desplazamiento, origen de desplazamiento
    // SEEK_SET: inicio del archivo
    // SEEK_CUR: posición actual
    // SEEK_END: final del archivo

    //printf("tamano archivo = %d\n", tamanoArchivo );
    //printf("record size = %ld\n", sizeof( Empleado ) );
    int cantidadRegistros = tamanoArchivo / sizeof( Empleado );
    Empleado empleados[cantidadRegistros];
    //printf("cantidad de registros = %d\n", cantidadRegistros );

    for( int i = 0; i < cantidadRegistros; i++ ){
        lseek( fd, i*sizeof( Empleado), SEEK_SET );
        read( fd, (void *)&empleado, sizeof( Empleado ) );
        //printf("registro %d: %d\n", i, empleado.nombre );
        empleados[i] = empleado;
    }

    OrdenarEmpleados( empleados, cantidadRegistros );
    ImprimirEmpleados( empleados, cantidadRegistros );

    close(fd);
    return 0;
}

void OrdenarEmpleados( Empleado *empleados, int cantidadRegistros ){
    // Ordenamiento burbuja
    Empleado aux;
    for( int i = 0; i < cantidadRegistros; i++ ){
        for( int j = 0; j < cantidadRegistros - 1; j++ ){
            if( strcmp( empleados[j].nombre, empleados[j+1].nombre ) > 0 ){
                aux = empleados[j];
                empleados[j] = empleados[j+1];
                empleados[j+1] = aux;
            }
        }
    }
}

void ImprimirEmpleados( Empleado *empleados, int cantidadRegistros ){
    printf("EMPLEADOS ORDENADOS POR NOMBRE:\n\n");
    printf("clave         nombre      número      sueldo\n");
    for( int i = 0; i < cantidadRegistros; i++ ){
        printf("%d    %s        %s      %.2f\n", empleados[i].clave, empleados[i].nombre, empleados[i].telefono, empleados[i].sueldo);
    }
}