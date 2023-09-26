#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

/* manejador: rutina de tratamiento de la señal SIGINT. */
void manejador(int sig) {
    printf("Señal número %d recibida \n", sig);
    fflush(stdout);
}

int main(void) {
    struct sigaction act;
    int i;

    act.sa_handler = SIG_DFL;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;

    for (i = 1; i < 32; i++) {
        if (i == 9 || i == 19) {
            i++;
        }
        if (sigaction(i, &act, NULL) < 0) {
            printf("Señal %d\n", i);
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
        printf("Señal %d recibida\n", i);
    }

    /*while(1) {
        printf("En espera de Ctrl+C (PID = %d)\n", getpid());
        sleep(9999);
    }*/
}
