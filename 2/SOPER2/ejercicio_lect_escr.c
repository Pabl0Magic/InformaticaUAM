#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define SEM_NAME "/reader"
#define SEM_NAME2 "/writer"
#define SEM_NAME3 "/confirm"

int signal_caught;

void child_term_handler(int sig) {
    if(sig == SIGTERM) {
        printf("Finalizado %d\n", getpid());
        exit(EXIT_SUCCESS);
    }
}

void parent_handler(int sig) {
    if(sig == SIGINT) {
        printf("Recibido\n");
        signal_caught = 1;
    }
}

int main(int argc, char** argv) {
    
    int i, j, n_read, SECS;
    sem_t *sem_reader = NULL, *sem_writer = NULL, *sem_confirm = NULL;
    pid_t *pid;
    
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <N_READ> <SECS>\n", argv[0]);
        return 1;
    }
    
    CREATE_SEMAPHOR:
    if ((sem_reader = sem_open(SEM_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) { 
	    if (errno == 17) {
            sem_unlink(SEM_NAME);
            goto CREATE_SEMAPHOR;
        }
        else {
            perror("sem_open");
		    exit(EXIT_FAILURE);
        }
    }	

    CREATE_SEMAPHOR2:
    if ((sem_writer = sem_open(SEM_NAME2, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) { 
		if (errno == 17) {
            sem_unlink(SEM_NAME2);
            goto CREATE_SEMAPHOR2;
        }
        else {
            perror("sem_open");
		    exit(EXIT_FAILURE);
        }
    }

    CREATE_SEMAPHOR3:
    if ((sem_confirm = sem_open(SEM_NAME3, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 100)) == SEM_FAILED) { 
		if (errno == 17) {
            sem_unlink(SEM_NAME3);
            goto CREATE_SEMAPHOR3;
        }
        else {
            perror("sem_open");
		    exit(EXIT_FAILURE);
        }
    }		
	

    n_read = atoi(argv[1]);
    SECS = atoi(argv[2]);
    pid = (pid_t*) malloc(n_read * sizeof(pid_t));

    struct sigaction act_term;
    act_term.sa_handler = parent_handler;
    sigemptyset(&act_term.sa_mask);
    sigaddset(&act_term.sa_mask, SIGINT);
    act_term.sa_flags = 0;
    sigaction(SIGINT, &act_term, NULL);

    for (i = 0; i < n_read; i++) {
        pid[i] = fork();
        if(pid[i] < 0) {
            perror("fork");
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
            int sem_val;
            while(1) {
                sem_wait(sem_reader); /*Down*/
                sem_post(sem_confirm); /* Reader ++ */
                sem_getvalue(sem_confirm, &sem_val);
                if (sem_val == 1) {
                    sem_wait(sem_writer); /*Down*/
                }
                sem_post(sem_reader); /*Up*/

                /*Read*/
                printf("R-INI %d\n", childPid);
                sleep(1);
                printf("R-FIN %d\n", childPid);

                sem_wait(sem_reader); /*Down*/
                sem_getvalue(sem_confirm, &sem_val);
                sem_wait(sem_confirm); /* Reader-- */
                sem_getvalue(sem_confirm, &sem_val);
                if (sem_val == 0) {
                    sem_post(sem_writer); /*Up*/
                }
                sem_post(sem_reader); /*Up*/ 
                sleep(SECS);
            }
        }
    }
     
    /*Write*/
    signal_caught = 0;
    while(!signal_caught) {
        sem_wait(sem_writer); /*Down*/
        printf("W-INI %d\n", getpid());
        sleep(1);
        printf("W-FIN %d\n", getpid());
        sleep(SECS);
        sem_post(sem_writer);
    }

    for (j = 0; j < n_read; j++) {
        kill(pid[j], SIGTERM);
    }

    sem_post(sem_writer); /*Up*/
    while (wait(NULL) > 0) ;
    free(pid);
    sem_unlink(SEM_NAME);
    sem_unlink(SEM_NAME2);
    sem_unlink(SEM_NAME3);
    printf("Finalizado padre\n");
    exit(EXIT_SUCCESS);
}