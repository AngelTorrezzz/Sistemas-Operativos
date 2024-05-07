#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	//Comando de linux ls > arch.txt es equivalente a este codigo

	char *s = "letrero a archivo\n";
	char *m = "letrero a pantalla\n";
	/*
	Al ejecutarse un proceso siempre se abren 3 archivos por default, IN, OUT, ERR
	*/

	//STDOUT_FILENO apunta a la terminal, y STDOUT_FILENO es la salida principal de un proceso al ejecutarse (archivo)
	write( STDOUT_FILENO, m, strlen( m ));
	
	int fd = open( "arch.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	//fd apunta a arch.txt

	//con dup2 STDOUT_FILENO ahora apunta a fd (arch.txt)
	dup2( fd, STDOUT_FILENO ); 

	//liberamos fd, ya no nos hace falta
	close( fd );
	
	write( STDOUT_FILENO, s, strlen( s ) );
	
	//Ahora todas las funciones de salida seran mostradas en el archivo, debido al cambio que hicimos
	printf("bye bye\n");
	execlp("ls", "-lh", NULL);
	return 0;
}