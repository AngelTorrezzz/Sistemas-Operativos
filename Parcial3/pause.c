#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("\nSeñal SIGINT recibida. Terminando el programa.\n");
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    // Registrar el manejador de señales para SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction falló");
        exit(1);
    }

    printf("Esperando señales...\n");
    // Suspender el proceso hasta que se reciba una señal
    pause();

    printf("Proceso reanudado.\n");
    return 0;
}
