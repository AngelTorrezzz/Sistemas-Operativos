#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// ID del proceso hijo
pid_t child_pid = 0;

// Manejador para SIGALRM
void handle_sigalrm(int sig) {
    if (child_pid != 0) {
        printf("Time's up! Sending SIGKILL to child process %d\n", child_pid);
        kill(child_pid, SIGKILL);  // Enviar SIGKILL al proceso hijo
    }
}

// Manejador para SIGCHLD
void handle_sigchld(int sig) {
    int status;
    pid_t pid;

    // Esperar a que cualquier proceso hijo termine
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (pid == child_pid) {
            printf("Child process %d terminated\n", pid);
            if (WIFEXITED(status)) {
                printf("Child exited with status %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Child killed by signal %d\n", WTERMSIG(status));
            }
        }
    }
}

int main() {
    // Configurar los manejadores para SIGALRM y SIGCHLD
    signal(SIGALRM, handle_sigalrm);
    signal(SIGCHLD, handle_sigchld);

    // Crear un proceso hijo
    child_pid = fork();

    if (child_pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // Este es el código del proceso hijo
        printf("Child process (PID: %d) running...\n", getpid());
        while (1) {
            // Simular un trabajo del proceso hijo
            sleep(1);
            printf("Child process still running...\n");
        }
    } else {
        // Este es el código del proceso padre
        printf("Parent process (PID: %d), child process (PID: %d)\n", getpid(), child_pid);

        // Establecer una alarma para 10 segundos
        alarm(5);

        // Esperar a que el proceso hijo termine
        pause();  // Esperar indefinidamente hasta recibir una señal
    }

    return 0;
}