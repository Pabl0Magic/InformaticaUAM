/* WRITER */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_NAME "/shm_example"
#define INT_LIST_SIZE 10
#define MSG_MAX 100
#define MESSAGE "Hello world shared memory!"
#define MAXBUF 10

typedef struct{
    int integer_list[INT_LIST_SIZE];
    char message[MSG_MAX];
} ShmExampleStruct;

int main(void) {
    /* We create the shared memory */
    int fd_shm = shm_open(SHM_NAME,
        O_RDWR | O_CREAT | O_EXCL, /* Create it and open for reading and writing */
        S_IRUSR | S_IWUSR); /* The current user can read and write */

    if (fd_shm == -1) {
        fprintf(stderr, "Error creating the shared memory segment\n");
        return EXIT_FAILURE;
    }

    /* Resize the memory segment */ 
    if (ftruncate(fd_shm, sizeof(ShmExampleStruct)) == -1) {
        fprintf(stderr, "Error resizing the shared memory segment\n");
        shm_unlink(SHM_NAME);
        return EXIT_FAILURE;
    }

    /* Map the memory segment */
    ShmExampleStruct *example_struct = mmap(NULL,
        sizeof(*example_struct), /* Memory mapping size */
        PROT_READ | PROT_WRITE, /* Read and write */
        MAP_SHARED, /* Share data changes */
        fd_shm, /* File or mem_file descriptor */
        0);
    close(fd_shm);

    if (example_struct == MAP_FAILED) {
        fprintf(stderr, "Error mapping the shared memory segment\n");
        shm_unlink(SHM_NAME);
        return EXIT_FAILURE;
    }

    printf("Pointer to shared memory segment: %p\n", (void*)example_struct);

    /* Initialize the memory */
    memcpy(example_struct->message, MESSAGE, sizeof(MESSAGE));
    int i;
    for (i = 0; i < MAXBUF; i++) {
        example_struct->integer_list[i] = i;
    }

    /* The daemon executes until press some character */
    getchar();

    /* Free the shared memory */
    munmap(example_struct, sizeof(*example_struct));
    shm_unlink(SHM_NAME);

    return EXIT_SUCCESS;
}
