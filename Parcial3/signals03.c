#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t child_pid;



int main() {
    child_pid = fork();

    if (child_pid < 0) {
        perror("fork falló");
        exit(1);
    }

    if (child_pid == 0) {
        // Proceso hijo
        printf("Proceso hijo iniciado.\n");
        // Simular un trabajo largo (más de 10 segundos)
        sleep(15);
        //printf("Proceso hijo terminado.\n");
        exit(0);
    } else {
        // Proceso padre
        printf("Proceso padre iniciado.\n");

        sleep(2);
        kill(child_pid, SIGKILL);

        int status;
        waitpid(child_pid, &status, 0);//
        printf("Proceso padre terminado.\n");
    }

    return 0;
}