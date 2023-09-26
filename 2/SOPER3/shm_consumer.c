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
    int rear;
} Queue;

Queue *shm_struct;

int getRandomNumber() {
	int up = 9,
    low = 0;
	
	return (int)(((double)rand() / (double)RAND_MAX) * (double)up);
}

int main(int argc, char *argv[]) {
    
    int i, j;
    int val;
    int result[10], histogram[10];
    int ret = EXIT_FAILURE;
    
    sem_t *sem_mutex;
    sem_t *sem_fill;
    sem_t *sem_empty;
    sem_t *sem_consumer;

    for (i = 0; i < 10; i++) {
        histogram[i] = 0;
        result[i] = 0;
    }
    sem_unlink(SEM_CONSUMER_ENDED);

    int fd_shm = shm_open(SHM_NAME, 0, O_RDONLY);

    if (fd_shm == -1) {
        fprintf(stderr, "Error opening the shared memory segment. Make sure a Producer is running prior to launching %s.\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Map the memory segment */
    Queue* shm_struct = mmap(NULL, sizeof(Queue), PROT_READ, MAP_SHARED, fd_shm, 0);
    close(fd_shm);

    if (shm_struct == MAP_FAILED) {
        fprintf(stderr, "Error mapping the shared memory segment\n");
        return EXIT_FAILURE;
    }
    if ((sem_consumer = sem_open(SEM_CONSUMER_ENDED, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, SIZE)) == SEM_FAILED) {
        perror("sem_open");
        munmap(shm_struct, sizeof(*shm_struct));
	    shm_unlink(SHM_NAME);
		exit(EXIT_FAILURE);
    }
    if ((sem_mutex = sem_open(SEM_NAME_MUTEX, 0)) == SEM_FAILED) {
        perror("sem_open");
        munmap(shm_struct, sizeof(*shm_struct));
	    shm_unlink(SHM_NAME);
		exit(EXIT_FAILURE);
	}

    if ((sem_fill = sem_open(SEM_NAME_FILL, 0)) == SEM_FAILED) {
		perror("sem_open");
        munmap(shm_struct, sizeof(*shm_struct));
	    shm_unlink(SHM_NAME);
		exit(EXIT_FAILURE);
	}

    
    if ((sem_empty = sem_open(SEM_NAME_EMPTY, 0)) == SEM_FAILED) {
		perror("sem_open");
        munmap(shm_struct, sizeof(*shm_struct));
	    shm_unlink(SHM_NAME);
		exit(EXIT_FAILURE);
	}
    

    for (i = 0; shm_struct->arr[i] != -1; i = (i + 1) % SIZE) {
        sem_wait(sem_fill);   
        sem_wait(sem_mutex);

        if(shm_struct->arr[i] == -1) {
            break;
        }
        
        histogram[shm_struct->arr[i]]++;
        
        sem_post(sem_mutex);
        sem_post(sem_empty);
    }
    
    sem_post(sem_consumer);
    printf("Histogram:\n");
    for(i = 0; i < 10; i++) {
        printf("%d: %d\n", i, histogram[i]);
    }
    sem_unlink(SEM_CONSUMER_ENDED);

    return EXIT_SUCCESS;

}