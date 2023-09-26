#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define SIZE 2000
#define FINALIZADO "finalizado"

typedef struct {
    int val;
    char cola[SIZE];
} Mensaje;

int main(int argc, char **argv) {

    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_curmsgs = 0,
        .mq_msgsize = SIZE
    };

    FILE *pf;
    int i;
    char* filename;
    char* queuename;
    char character[SIZE];
    int ret = EXIT_FAILURE;

    if (argc < 3) {
		fprintf(stderr,"usage: %s <filename> <queuename> \n",argv[0]);
		return ret;
	}

    filename = argv[1];
    queuename = argv[2];

    pf = fopen(filename, "r");
    if(!pf) {
        perror("Error opening file");
        return ret;
    }

    mqd_t queue = mq_open(queuename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &attributes);

    if (queue == (mqd_t)-1) {
        fprintf(stderr, "Error opening the queue\n");
        return EXIT_FAILURE;
    }

    Mensaje msg;
    msg.val = 2000;

    while(fgets(character, SIZE, pf) != NULL) {
        printf("%s\n", character);
        if (mq_send(queue, character, SIZE, 1) == -1) {
            fprintf(stderr, "Error sending message 1\n");
            return ret;
        }
    }

    if (mq_send(queue, FINALIZADO, sizeof(FINALIZADO), 1) == -1) {
            fprintf(stderr, "Error sending message 2\n");
            return ret;
        }

    /* Wait for input to end the program */
    fprintf(stdout, "Press any key to finish\n");
    getchar();
    
    fclose(pf);
    mq_close(queue);
    mq_unlink(queuename);
    return EXIT_SUCCESS;   
    
}