#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    sigset_t set, oset;

    /* Máscara que bloqueará la señal SIGUSR1 y SIGUSR2. */
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);

    /* Bloqueo de las señales SIGUSR1 y SIGUSR2 en el proceso. */
    if (sigprocmask(SIG_BLOCK, &set, &oset) < 0) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("En espera de señales (PID = %d)\n", getpid());
    printf("SIGUSR1 y SIGUSR2 están bloqueadas\n");
    pause();
    /*sleep(10);
    if(sigprocmask(SIG_UNBLOCK, &set, &oset) < 0) {
        perror("sigprocmask UNBLOCK");
        exit(EXIT_FAILURE);
    }*/

    printf("Fin del programa\n");
    exit(EXIT_SUCCESS);
}
