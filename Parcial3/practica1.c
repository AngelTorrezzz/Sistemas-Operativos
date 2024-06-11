#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid;

void handle_alarm(int sig) {
    if (sig == SIGALRM) {
        printf("10 segundos han pasado. Enviando señal SIGKILL al proceso hijo.\n");
        kill(child_pid, SIGKILL);
        printf("Proceso hijo terminado.\n");
    }
}

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
        printf("Proceso hijo terminado.\n");
        exit(0);
    } else {
        // Proceso padre
        printf("Proceso padre iniciado.\n");
        struct sigaction sa;
        sa.sa_handler = handle_alarm;
        sa.sa_flags = 0;
        sigemptyset(&sa.sa_mask);

        if (sigaction(SIGALRM, &sa, NULL) == -1) {
            perror("sigaction falló");
            exit(1);
        }

        alarm(10);

        int status;
        waitpid(child_pid, &status, 0);//
        printf("Proceso padre terminado.\n");
    }

    return 0;
}