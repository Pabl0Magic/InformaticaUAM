#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

#include "shm_producer_consumer.h"

typedef struct {
    int arr[SIZE];
} Queue;

int getRandomNumber() {
	int up = 9;
	int low = 0;
	int res;

	res = (rand() % (up - low + 1)) + low;

	return res;
}

int main(int argc, char **argv) {
    
    int n, m, val;
    int i, j = 0;
    int *aux;
    int auxRear = 0;
    int ret = EXIT_FAILURE;
    
    sem_t *sem_mutex;
    sem_t *sem_fill;
    sem_t *sem_empty;

    if (argc < 3) {
		fprintf(stderr,"usage: %s <n_numbers> <random/secuence> \n",argv[0]);
		return ret;
	}

	n = atoi(argv[1]);
	m = atoi(argv[2]);
    
    aux = (int*) malloc(sizeof(int) * n);
    if(!aux) {
        fprintf(stderr, "Can't create an array of size %d", n);
        return ret;
    }
    srand(time(NULL));

	int fd_shm = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (fd_shm == -1) {
		perror("Error in creating shared memory or the file exists.");
		shm_unlink(SHM_NAME); /* If it is already created first will give an error and the next time will do it correctly */
		return ret;
	}

	if (ftruncate(fd_shm, sizeof(Queue)) == -1) {
		perror("Error resizing shared memory");
		shm_unlink(SHM_NAME);
		return ret;
	}

	Queue *shm_struct = mmap(NULL, sizeof(*shm_struct), 
        PROT_READ | PROT_WRITE, 
        MAP_SHARED, 
        fd_shm, 
        0);
    close(fd_shm);

    if (shm_struct == MAP_FAILED) {
        perror("Error mapping the shared memory segment\n");
        shm_unlink(SHM_NAME);
        return EXIT_FAILURE;
    }

    CREATE_MUTEX: 
    if ((sem_mutex = sem_open(SEM_NAME_MUTEX, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
		if (errno == 17) {
            sem_unlink(SEM_NAME_MUTEX);
            goto CREATE_MUTEX;
        } else {
            perror("sem_open");
            munmap(shm_struct, sizeof(*shm_struct));
	        shm_unlink(SHM_NAME);
		    exit(EXIT_FAILURE);
        }
	}

    CREATE_FILL:
    if ((sem_fill = sem_open(SEM_NAME_FILL, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED) {
        if (errno == 17) {
            sem_unlink(SEM_NAME_FILL);
            goto CREATE_FILL;
        } else {
		    perror("sem_open");
            munmap(shm_struct, sizeof(*shm_struct));
	        shm_unlink(SHM_NAME);
		    exit(EXIT_FAILURE);
        }
	}

    
    CREATE_EMPTY:
    if ((sem_empty = sem_open(SEM_NAME_EMPTY, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, SIZE)) == SEM_FAILED) {
        if (errno == 17) {
            sem_unlink(SEM_NAME_EMPTY);
            goto CREATE_EMPTY;
        } else {
		    perror("sem_open");
            munmap(shm_struct, sizeof(*shm_struct));
	        shm_unlink(SHM_NAME);
		    exit(EXIT_FAILURE);
        }
	}
    

    if (m == 0) {
        for (i = 0; i < n; i++)  {
            aux[auxRear] = getRandomNumber();
            auxRear++;
        }

    } else {
        for (i = 0; i < n; i++) {
            if (j == 10) {
                j = 0;
            }
            aux[auxRear] = j;
            j++;
            auxRear++;
        }
    }

    for (i = 0, j = 0; i < auxRear; i++, j = i % SIZE) {
        sem_wait(sem_empty);
        sem_wait(sem_mutex);

        shm_struct->arr[j] = aux[i];

        sem_post(sem_mutex);
        sem_post(sem_fill);
    }
    shm_struct->arr[j] = -1;
    sem_t *wait_consumer = sem_open(SEM_CONSUMER_ENDED, 0);
    if (wait_consumer != SEM_FAILED) {
        sem_wait(wait_consumer);
    }
    sem_close(sem_mutex);
	sem_unlink(SEM_NAME_MUTEX);
    sem_close(sem_empty);
	sem_unlink(SEM_NAME_EMPTY);
    sem_close(sem_fill);
	sem_unlink(SEM_NAME_FILL);

    munmap(shm_struct, sizeof(*shm_struct));
	shm_unlink(SHM_NAME);

    return EXIT_SUCCESS;
}