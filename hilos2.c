#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>                                                             
#include <unistd.h>
#include <sys/types.h>

void *h1( void * ); 
void *h2( void * ); 
void *h3( void * );
void *h4( void * );

unsigned int k = 100;

int main( ){
    //Los hilos son procesos q se ejecutan infinitamente
   pthread_t hilo_1, hilo_2, hilo_3, hilo_4;
   printf("Hilo main    Subhilos\n");
   pthread_create( &hilo_1, NULL, h1, NULL );//hilo_1 ejectuta el mismo codigo
   pthread_create( &hilo_2, NULL, h1, NULL );//hilo_2 ejectuta el mismo codigo
   pthread_create( &hilo_3, NULL, h1, NULL );//hilo_3 ejectuta el mismo codigo
   pthread_create( &hilo_4, NULL, h1, NULL );//hilo_4 ejectuta el mismo codigo
   pthread_join( hilo_1, NULL );//Detiene a main
   pthread_join( hilo_2, NULL );
   pthread_join( hilo_3, NULL );
   pthread_join( hilo_4, NULL );
   printf( "fin de main\n" );
   return 0;
}

void *h1( void *s ){
   printf("%d,        %d\n", getpid(), gettid( ) ); //getpid() retorna el id del hilo main y gettid() retorna en id del subhilo
   while( 1 )
       k++;

   pthread_exit( NULL );
}

 
void *h2( void *parametro ){
   printf("%d,        %d\n", getpid(), gettid( ) );
   while( 1 )
       k--;

   pthread_exit( NULL );
}

 
void *h3( void *parametro ){
   printf("%d,        %d\n", getpid(), gettid( ) );
   while( 1 ){
       //sleep( 1 );
       k--;
   }

   pthread_exit( NULL );
}


void *h4( void *parametro ){
   printf("%d,        %d\n", getpid(), gettid( ) );
   while( 1 )
       k--;

   pthread_exit( NULL );
}
