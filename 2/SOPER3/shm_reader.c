/* READER */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_NAME "/shm_example"
#define INT_LIST_SIZE 10
#define MSG_MAX 100
#define MAXBUF 10

typedef struct{
    int integer_list[INT_LIST_SIZE];
    char message[MSG_MAX];
} ShmExampleStruct;

int main(void) {
    /* We open the shared memory */
    int fd_shm = shm_open(SHM_NAME,
        O_RDONLY, /* Obtain it and open for reading */
        0); /* Unused */

    if (fd_shm == -1) {
        fprintf(stderr, "Error opening the shared memory segment\n");
        return EXIT_FAILURE;
    }

    /* Map the memory segment */
    ShmExampleStruct *example_struct = mmap(NULL, sizeof(*example_struct),
        PROT_READ,
        MAP_SHARED,
        fd_shm,
        0);
    close(fd_shm);

    if (example_struct == MAP_FAILED) {
        fprintf(stderr, "Error mapping the shared memory segment\n");
        return EXIT_FAILURE;
    }

    printf("Pointer to shared memory segment: %p\n", (void*)example_struct);

    /* Read the memory */
    printf("%s\n" , example_struct->message);
    for (int i = 0; i < MAXBUF; i++) {
        printf("%d\n", example_struct->integer_list[i]);
    }

    /* Unmap the shared memory */
    munmap(example_struct, sizeof(*example_struct));

    return EXIT_SUCCESS;
}
