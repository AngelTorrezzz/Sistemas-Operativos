#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int tuberia[ 2 ];
    
    int h1, h2;

    //pipe nos devuelve un descriptor de lectura y otro de escritura.
    //tuberia[0] es de lectura
    //tuberia[1] es de escritura
    pipe( tuberia );
    
    //generamos un proceso. Es el hijo1
    h1 = fork();

    if( h1 == 0 ){
        // este extremo de la tuberia no se utiliza
        // liberamos el descriptor de archivo correspondiente
        close( tuberia[ STDIN_FILENO ] );//STDIN_FILENO = 0

        //dirigimos la salida estandar hacia la tuberia
        dup2(tuberia[ STDOUT_FILENO ], STDOUT_FILENO);//STDOUT_FILENO = 1

        //este descriptor ya no hace falta. Lo liberamos
        close( tuberia[ STDOUT_FILENO ] );

        //ejecutamos el comando ls con la salida direccionada 
        // a la tuberia
        execlp("ls", "ls", NULL );

        // este mensaje no deberia aparecer.
        printf("ls no se ejecuto\n");

        //Una vez que los descriptores ya fueron ocupados para crear la tuberia pueden liberarse
    }
    
    //liberamos el descriptor de salida, ya que no se requiere.
    close( tuberia[ STDOUT_FILENO ] );
    
    //generamos otro proceso. Es el hijo2
    h2 = fork();
    if( h2 == 0 ){

        //hacemos que el flujo de entrada provenga de la tuberia
        dup2( tuberia[ STDIN_FILENO ], STDIN_FILENO );

        // este descriptor ya no es necesario
        close( tuberia[ STDIN_FILENO ] );

        // ejecutamos el comando wc. Su flujo de
        // entrada proviene de la tuberia
        execlp("wc", "wc", NULL);

        // este letreo no debería aparecer.
        printf("wc no se ejectuo\n");
    }

    // el proceso padre espera a que los
    // procesos hijos terminen su ejecución

    //Son necesarios los dos waits, el sistema operativo sabe que existen 2 procesos hijos pendientes
    //pero no sabe exactamente cuales por eso los waits deben ser 2 porque son dos procesos hijos pendientes

    wait(NULL);//Si quitamos el wait el proceso padre puede morir antes de que terminen los procesos hijos
    wait(NULL);
    printf("bye\n");
    return 0;
}