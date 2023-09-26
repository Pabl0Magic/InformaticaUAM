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

#define SHM_NAME "/shm_eje3"
#define MAX_MSG 2000

static void getMilClock(char *buf) {
    int millisec;
	char aux[100];
    struct tm* tm_info;
    struct timeval tv;

    gettimeofday(&tv, NULL);
	millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
    if (millisec>=1000) { // Allow for rounding up to nearest second
        millisec -=1000;
        tv.tv_sec++;
    }
    tm_info = localtime(&tv.tv_sec);
    strftime(aux, 10, "%H:%M:%S", tm_info);
	sprintf(buf, "%s.%03d", aux, millisec);
}

typedef struct {
	pid_t processid;       /* Logger process PID */
	long logid;            /* Id of current log line */
	char logtext[MAX_MSG]; /* Log text */
} ClientLog;

ClientLog *shm_struct;

void manejador (int sig) {
	if (sig == SIGUSR1) {
		printf ("Log %ld: Pid %d: %s\n",shm_struct->logid, shm_struct->processid, shm_struct->logtext);
	}
}

int getRandomNumber() {
	int up = 900;
	int low = 100;
	int res;

	res = (rand() % (up - low + 1)) + low;
	res = res/1000;

	return res;
}
int main(int argc, char *argv[]) {
	int n, m;
	int ret = EXIT_FAILURE;
	int i, j;
	int sleepTime;
	int pid;
	sigset_t set;
	struct sigaction act;

	if (argc < 3) {
		fprintf(stderr,"usage: %s <n_process> <n_logs> \n",argv[0]);
		return ret;
	}

	n = atoi(argv[1]);
	m = atoi(argv[2]);

	int fd_shm = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (fd_shm == -1) {
		perror("Error in creating shared memory");
		shm_unlink(SHM_NAME); /* If it is already created first will give error then it will be removed */
		return ret;
	}

	if (ftruncate(fd_shm, sizeof(ClientLog)) == -1) {
		perror("Error resizing shared memory");
		shm_unlink(SHM_NAME);
		return ret;
	}

	shm_struct = mmap(NULL, sizeof(*shm_struct), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
	shm_struct->logid = -1;
    close(fd_shm);

    if (shm_struct == MAP_FAILED) {
        perror("Error mapping the shared memory segment\n");
        shm_unlink(SHM_NAME);
        return EXIT_FAILURE;
    }
	/* Handler */
	act.sa_handler = manejador;
    sigemptyset(&(act.sa_mask));
	sigaddset(&act.sa_mask, SIGUSR1);
    act.sa_flags = 0;

	if(sigaction(SIGUSR1, &act, NULL) < 0) {
		perror("Error in sigaction");
		return ret;
	}

	for (i = 0; i< n; i++) {	
		pid = fork();
		if (pid < 0) {
			perror("fork\n");
			return ret;
		}
	}

	if (pid == 0) {
		for (j = 0; j < m; j++) {
		sleepTime = getRandomNumber();
		sleep(sleepTime);

		shm_struct->processid = getpid();
		shm_struct->logid = shm_struct->logid + 1;
		getMilClock(shm_struct->logtext);
	
		kill(getppid(), SIGUSR1);
		}
	} 

	sigfillset(&set);
	sigdelset(&set, SIGUSR1);

	/* In order to wait all the childs, we create a set to manage the signal SIGUSR1 */
	while (shm_struct->logid < n*m-1) {
		sigsuspend(&set);
	}

	munmap(shm_struct, sizeof(*shm_struct));
	shm_unlink(SHM_NAME);
	printf("Padre finalizado\n");
	return EXIT_SUCCESS;
}
