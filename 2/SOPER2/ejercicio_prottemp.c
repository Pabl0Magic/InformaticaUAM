#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern int errno;

int alarm_caught;

void parent_handler(int sig) { 
    int static counter = 0;

    switch (sig) {
        case SIGALRM:
            alarm_caught = 1;
            break;
        case SIGUSR2:
            counter++;
            printf("Recibido SIGUSR2 numero %d\n", counter);
            break;
    }
}

void child_term_handler(int sig) {
    if(sig == SIGTERM)
    {
        printf("Finalizado %d\n", getpid());
        exit(EXIT_SUCCESS);
    }
 }

int main(int argc, char** argv){
    int i, j, N, T;
    pid_t *pid;
    
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <N> <T>", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    T = atoi(argv[2]);
    pid = (pid_t*) malloc(N * sizeof(pid_t));

    
    struct sigaction act_sigusr2;
    act_sigusr2.sa_handler = parent_handler;
    sigemptyset(&act_sigusr2.sa_mask);
    sigaddset(&act_sigusr2.sa_mask, SIGUSR2);
    sigaddset(&act_sigusr2.sa_mask, SIGALRM);
    act_sigusr2.sa_flags = 0;
    sigaction(SIGUSR2, &act_sigusr2, NULL);
    sigaction(SIGALRM, &act_sigusr2, NULL);

    for (i = 0; i < N; i++) {
        pid[i] = fork();
        if(pid[i] < 0) {
            perror("fork\n");
            return -1;
        }

        if (pid[i] == 0) {
            pid_t childPid = getpid();

            struct sigaction child_act;
            child_act.sa_handler = child_term_handler;
            sigemptyset(&child_act.sa_mask);
            sigaddset(&child_act.sa_mask, SIGTERM);
            child_act.sa_flags = 0;
            sigaction(SIGTERM, &child_act, NULL);

            sigset_t child_set;
            sigfillset(&child_set);
            sigdelset(&child_set, SIGTERM);

            register unsigned int result;
            int limit = childPid / 10;
            for (register int j = 1; j <= limit; j++) {
                result += j;
            }
            printf("PID: %d. Resultado: %u\n", childPid, result);
            
            kill(getppid(), SIGUSR2);
            sigsuspend(&child_set);
            exit(EXIT_FAILURE);
        }
    }

    alarm(T);
    
    sigset_t parent_set;
    sigfillset(&parent_set);
    sigdelset(&parent_set, SIGALRM);
    sigdelset(&parent_set, SIGUSR2);

    alarm_caught = 0;
    while (alarm_caught == 0) {
        sigsuspend(&parent_set);
    }
    for (j = 0; j < N; j++) {
        kill(pid[j], SIGTERM);
    }

    while (wait(NULL) > 0) ;
    free(pid);
    printf("Finalizado padre\n");
    exit(EXIT_SUCCESS);
}