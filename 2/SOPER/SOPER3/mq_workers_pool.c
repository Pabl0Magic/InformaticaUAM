#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

#define SIZE 2000
#define FINALIZADO "finalizado"

int character_read;
int message_read;
int end;

void parent_handler (int sig) {
	if (sig == SIGUSR2) {
		end = 1;
	}
}

void child_handler (int sig) {
	if (sig == SIGTERM) {
		printf ("Mensajes procesados: %d\n Caracteres leidos: %d\n", message_read, character_read);
	}
}

typedef struct {
    int val;
    char cola[50];
} Mensaje;

int main(int argc, char **argv) {
    FILE *pf;
    int i, j;
    char *queuename;
    char character[SIZE];
    char *find;
    int n_workers;
    char c;
    pid_t *pid;
    int ret = EXIT_FAILURE;
    struct sigaction act;
    sigset_t set;
    sem_t sem;

    if (argc < 4) {
		fprintf(stderr,"usage: %s <workers_number> <queuename> <character_to_find> \n",argv[0]);
		return ret;
	}

    n_workers = atoi(argv[1]);
    if (n_workers < 1 || n_workers > 10) {
        fprintf(stderr,"Number must be between 1 and 10\n");
        return ret;
    }

    queuename = argv[2];
    find = argv[3];

    pid = (pid_t*) malloc(n_workers * sizeof(pid_t));

    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;
	act.sa_handler = parent_handler;
	if(sigaction(SIGUSR2, &act, NULL) < 0) {
	    perror("Error in sigaction");
	    return ret;
	}
    
    act.sa_handler = child_handler;
    if(sigaction(SIGTERM, &act, NULL) < 0) {
	    perror("Error in sigaction");
	    return ret;
	}

    mqd_t queue = mq_open(queuename, O_RDONLY);

    if(queue == (mqd_t)-1) {
        fprintf(stderr, "Error opening the queue\n");
        free(pid);
        return EXIT_FAILURE;
    }


    Mensaje msg;

    sem_init(&sem, 1, 1);

    sigset_t parent_set;
    sigfillset(&parent_set);
    sigdelset(&parent_set, SIGUSR2);
    sigdelset(&parent_set, SIGINT);

    for (i = 0; i < n_workers; i++) {	
		pid[i] = fork();
        if (pid[i] < 0) {
			perror("fork\n");
            free(pid);
			return ret;
		}
        if (pid[i] == 0) {
            break;
        }
        if (i == n_workers - 1) {
            break;
        }
	}


    /* Hijo */
    if (pid[i] == 0) {
        character_read = 0;
        message_read = 0;
        free(pid);

        for (i = 0; i < 10; i++) {
            sem_wait(&sem);
            memset(character, 0x00, sizeof(character));
            if (mq_receive(queue, character, SIZE, NULL) == -1) {
                fprintf(stderr, "Error receiving message\n");
                kill(getppid(), SIGUSR2);
                return EXIT_FAILURE;
            }

            if (strcmp(character, FINALIZADO) == 0) {
                mq_close(queue);
                break;
            }

            for(j = 0; j < strlen(character); j++) {
                if (character[j] == find[0]) {
                    character_read++;
                }    
            }
            message_read++;
            sem_post(&sem);
        }
        kill(getppid(), SIGUSR2);
        sigfillset(&set);
        sigdelset(&set, SIGTERM);

        sigsuspend(&set);
    }


    end = 0;
    while (end == 0) {
        sigsuspend(&parent_set);
    }

    printf("Mandando SIGTERM a hijos...\n");
    for (j = 0; j < n_workers; j++) {
        kill(pid[j], SIGTERM);
    }

    while (wait(NULL) > 0);
    free(pid);
    sem_destroy(&sem);
    mq_close(queue);
    mq_unlink(queuename);
    printf("Finalizado padre\n");

    return EXIT_SUCCESS;
}