#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    //printf("%d\n",argc);
    //printf("%s\n",argv[2]);
    char *comando="";
    char *comandos;
    //printf("%s\n",comando);
    int pid = fork();
    if( pid == 0 ){
        while(strcmp(comando,"exit") != 0){
            printf("myshell$");
            scanf("%s",comando);
            for (char *buffer = strtok(comando, " "); buffer; buffer = strtok(NULL, " ")){
                execlp(comandos,NULL);
            }
        }
    }else{
        wait( NULL );
        exit(0);
    }
    return 0;
}
