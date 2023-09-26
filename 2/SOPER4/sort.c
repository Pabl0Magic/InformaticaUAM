#define _POSIX_C_SOURCE 200112L
#define MUTEX_NAME "mutex_tasks"

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <mqueue.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "sort.h"
#include "utils.h"

/* ********************************* */ 
/*  QUEDA POR HACER
 * 
 * Padre 
 * 
 * Checkear que cuando manda SIGUSR1 un trabajador se hayan hecho las tareas de ese nivel
    * Si ha terminado, que continue el siguiente nivel
    * Si no ha terminado, se suspende o envía tareas que aun no se hayan enviado   
 * Si se han completado todos los niveles o se recibe SIGINT, mandar a los trabajadores SIGTERM para que acaben
 * Crear las tuberias y semaforos (Puntos 6 y 7)
 * Crear proceso Ilustrador (?)
 * 
 * Trabajadores
 * 
 * Crear alarma que mande señal cada segundo
 * Cuando reciba SIGALARM, mandar por tuberia al ilustrador de la tarea que hace y se bloquea esperando la respuesta del ilustrador, tambien a traves de la tuberia(otra diferente)
 * Cuando reciba SIGTGERM, libera recursos y sale de forma ordenada
 * 
 * Ilustrador
 * 
 * No se como va esto del ilustrador todavia asi que no se que queda por hacer
 */

pid_t* pid;
int sigterm_received;  
int check;
int alarm_caught;
int tasks;
void kill_the_children() {
    int i;
    if(pid) {
        for(i = 0; i < tasks; i++) {
        /* pids set to 0 with calloc */
        if(pid[i] > 0) kill(pid[i], SIGTERM);
        }
    }
}
void parent_handler(int sig) {

    switch (sig) {
        case SIGINT:
            kill_the_children();
            if(pid) free(pid);
            shm_unlink(SHM_NAME);
            mq_unlink(MQ_NAME);
            break;
        case SIGALRM:
            alarm_caught = 1;
            break;
        case SIGUSR1:
            check++;
            break;
    }
}

void child_handler(int sig) {
    if(sig == SIGTERM) {
        shm_unlink(SHM_NAME);
        mq_unlink(MQ_NAME);
        if(pid) free(pid);
        exit(EXIT_SUCCESS);
    }
 }


Status bubble_sort(int *vector, int n_elements, int delay) {
    int i, j;
    int temp;

    if ((!(vector)) || (n_elements <= 0)) {
        return ERROR;
    }

    for (i = 0; i < n_elements - 1; i++) {
        for (j = 0; j < n_elements - i - 1; j++) {
            /* Delay. */
            fast_sleep(delay);
            if (vector[j] > vector[j+1]) {
                temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = temp;
            }
        }
    }

    return OK;
}

Status merge(int *vector, int middle, int n_elements, int delay) {
    int *aux = NULL;
    int i, j, k, l, m;

    if (!(aux = (int *)malloc(n_elements * sizeof(int)))) {
        return ERROR;
    }

    for (i = 0; i < n_elements; i++) {
        aux[i] = vector[i];
    }

    i = 0; j = middle;
    for (k = 0; k < n_elements; k++) {
        /* Delay. */
        fast_sleep(delay);
        if ((i < middle) && ((j >= n_elements) || (aux[i] < aux[j]))){
            vector[k] = aux[i];
            i++;
        }
        else {
            vector[k] = aux[j];
            j++;
        }

        /* This part is not needed, and it is computationally expensive, but
        it allows to visualize a partial mixture. */
        m = k + 1;
        for (l = i; l < middle; l++) {
            vector[m] = aux[l];
            m++;
        }
        for (l = j; l < n_elements; l++) {
            vector[m] = aux[l];
            m++;
        }
    }

    free((void *)aux);
    return OK;
}

int get_number_parts(int level, int n_levels) {
    /* The number of parts is 2^(n_levels - 1 - level). */
    return 1 << (n_levels - 1 - level);
}

Status init_sort(char *file_name, Sort *sort, int n_levels, int n_processes, int delay) {
    char string[MAX_STRING];
    FILE *file = NULL;
    int i, j, log_data;
    int block_size, modulus;

    if ((!(file_name)) || (!(sort))) {
        fprintf(stderr, "init_sort - Incorrect arguments\n");
        return ERROR;
    }

    /* At most MAX_LEVELS levels. */
    sort->n_levels = MAX(1, MIN(n_levels, MAX_LEVELS));
    /* At most MAX_PARTS processes can work together. */
    sort->n_processes = MAX(1, MIN(n_processes, MAX_PARTS));
    /* The main process PID is stored. */
    sort->ppid = getpid();
    /* Delay for the algorithm in ns (less than 1s). */
    sort->delay = MAX(1, MIN(999999999, delay));

    if (!(file = fopen(file_name, "r"))) {
        perror("init_sort - fopen");
        return ERROR;
    }

    /* The first line contains the size of the data, truncated to MAX_DATA. */
    if (!(fgets(string, MAX_STRING, file))) {
        fprintf(stderr, "init_sort - Error reading file\n");
        fclose(file);
        return ERROR;
    }
    sort->n_elements = atoi(string);
    if (sort->n_elements > MAX_DATA) {
        sort->n_elements = MAX_DATA;
    }

    /* The remaining lines contains one integer number each. */
    for (i = 0; i < sort->n_elements; i++) {
        if (!(fgets(string, MAX_STRING, file))) {
            fprintf(stderr, "init_sort - Error reading file\n");
            fclose(file);
            return ERROR;
        }
        sort->data[i] = atoi(string);
    }
    fclose(file);

    /* Each task should have at least one element. */
    log_data = compute_log(sort->n_elements);
    if (n_levels > log_data) {
        n_levels = log_data;
    }
    sort->n_levels = n_levels;

    /* The data is divided between the tasks, which are also initialized. */
    block_size = sort->n_elements / get_number_parts(0, sort->n_levels);
    modulus = sort->n_elements % get_number_parts(0, sort->n_levels);
    sort->tasks[0][0].completed = INCOMPLETE;
    sort->tasks[0][0].ini = 0;
    sort->tasks[0][0].end = block_size + (modulus > 0);
    sort->tasks[0][0].mid = NO_MID;
    for (j = 1; j < get_number_parts(0, sort->n_levels); j++) {
        sort->tasks[0][j].completed = INCOMPLETE;
        sort->tasks[0][j].ini = sort->tasks[0][j - 1].end;
        sort->tasks[0][j].end = sort->tasks[0][j].ini \
            + block_size + (modulus > j);
        sort->tasks[0][j].mid = NO_MID;
    }
    for (i = 1; i < n_levels; i++) {
        for (j = 0; j < get_number_parts(i, sort->n_levels); j++) {
            sort->tasks[i][j].completed = INCOMPLETE;
            sort->tasks[i][j].ini = sort->tasks[i - 1][2 * j].ini;
            sort->tasks[i][j].mid = sort->tasks[i - 1][2 * j].end;
            sort->tasks[i][j].end = sort->tasks[i - 1][2 * j + 1].end;
        }
    }

    return OK;
}

Bool check_task_ready(Sort *sort, int level, int part) {
    if (!(sort)) {
        return FALSE;
    }

    if ((level < 0) || (level >= sort->n_levels) \
        || (part < 0) || (part >= get_number_parts(level, sort->n_levels))) {
        return FALSE;
    }

    if (sort->tasks[level][part].completed != INCOMPLETE) {
        return FALSE;
    }

    /* The tasks of the first level are always ready. */
    if (level == 0) {
        return TRUE;
    }

    /* Other tasks depend on the hierarchy. */
    if ((sort->tasks[level - 1][2 * part].completed == COMPLETED) && \
        (sort->tasks[level - 1][2 * part + 1].completed == COMPLETED)) {
        return TRUE;
    }

    return FALSE;
}

Status solve_task(Sort *sort, int level, int part) {
    /* In the first level, bubble-sort. */
    if (sort->tasks[level][part].mid == NO_MID) {
        return bubble_sort(\
            sort->data + sort->tasks[level][part].ini, \
            sort->tasks[level][part].end - sort->tasks[level][part].ini, \
            sort->delay);
    }
    /* In other levels, merge. */
    else {
        return merge(\
            sort->data + sort->tasks[level][part].ini, \
            sort->tasks[level][part].mid - sort->tasks[level][part].ini, \
            sort->tasks[level][part].end - sort->tasks[level][part].ini, \
            sort->delay);
    }
}


Status sort_single_process(char *file_name, int n_levels, int n_processes, int delay) {
    int i, j;
    Sort sort;

    /* The data is loaded and the structure initialized. */
    if (init_sort(file_name, &sort, n_levels, n_processes, delay) == ERROR) {
        fprintf(stderr, "sort_single_process - init_sort\n");
        return ERROR;
    }

    plot_vector(sort.data, sort.n_elements);
    printf("\nStarting algorithm with %d levels and %d processes...\n", sort.n_levels, sort.n_processes);
    /* For each level, and each part, the corresponding task is solved. */
    for (i = 0; i < sort.n_levels; i++) {
        for (j = 0; j < get_number_parts(i, sort.n_levels); j++) {
            solve_task(&sort, i, j);
            plot_vector(sort.data, sort.n_elements);
            printf("\n%10s%10s%10s%10s%10s\n", "PID", "LEVEL", "PART", "INI", \
                "END");
            printf("%10d%10d%10d%10d%10d\n", getpid(), i, j, \
                sort.tasks[i][j].ini, sort.tasks[i][j].end);
        }
    }

    plot_vector(sort.data, sort.n_elements);
    printf("\nAlgorithm completed\n");

    return OK;
}

Status sort_multi_process(char* file, int n_levels, int n_processes, int delay) {

    struct mq_attr attributes;
    int i, j, t;
    Sort *project_struct;
    int fd_shm;
    mqd_t queue;
    Message message;
    struct sigaction act_parent, act_child;
    sem_t* mutex;

    act_parent.sa_handler = parent_handler;
    
    /* Inicializa los manejadores */
    act_parent.sa_handler = parent_handler;
    sigemptyset(&act_parent.sa_mask);
    sigaddset(&act_parent.sa_mask, SIGUSR1);
    sigaddset(&act_parent.sa_mask, SIGALRM);
    sigaddset(&act_parent.sa_mask, SIGINT);
    act_parent.sa_flags = 0;
    sigaction(SIGUSR1, &act_parent, NULL);
    sigaction(SIGALRM, &act_parent, NULL);
    sigaction(SIGINT, &act_parent, NULL);

    act_child.sa_handler = child_handler;
    sigemptyset(&act_child.sa_mask);
    sigaddset(&act_child.sa_mask, SIGUSR1);
    sigaddset(&act_child.sa_mask, SIGALRM);
    sigaddset(&act_child.sa_mask, SIGINT);
    sigaction(SIGINT, &act_child, NULL);
    sigaction(SIGALRM, &act_child, NULL);
    sigaction(SIGTERM, &act_child, NULL);

    /* Queue attributes */
    attributes.mq_flags = 0;
    attributes.mq_maxmsg = 10;
    attributes.mq_curmsgs = 0;
    attributes.mq_msgsize = MAX_STRING;

    pid = (pid_t*) calloc(n_levels, sizeof(pid_t));
    
    CREATE_SEMAPHOR:
    if ((mutex = sem_open(MUTEX_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
	    if (errno == 17) {
            sem_unlink(MUTEX_NAME);
            goto CREATE_SEMAPHOR;
        }
        else {
            perror("sem_open");
		    exit(EXIT_FAILURE);
        }
    }
    /* Memory share ini */
    fd_shm = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd_shm == -1) {
        perror("Error creating shared memory");
        shm_unlink(SHM_NAME);
        return ERROR;
    }

    if (ftruncate(fd_shm, sizeof(Sort)) == -1) {
        perror("Error resizing memory");
        shm_unlink(SHM_NAME);
        return ERROR;
    }

    project_struct = mmap(NULL, sizeof(*project_struct), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);

    project_struct->n_levels = n_levels;
    project_struct->n_processes = n_processes;
    project_struct->delay = delay;

    close(fd_shm);

    if(project_struct == MAP_FAILED) {
        perror("Error mapping the shared memory");
        shm_unlink(SHM_NAME);
        return ERROR;
    }

    /* Queue ini */
    queue = mq_open(MQ_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &attributes);
    if(queue == (mqd_t) - 1) {
        perror("Error opening queue");
        return ERROR;
    } 

    /* Sort ini */
    if (init_sort(file, project_struct, project_struct->n_levels, project_struct->n_processes, project_struct->delay) == ERROR) {
        fprintf(stderr, "sort_single_process - init_sort\n");
        return ERROR;
    }

    plot_vector(project_struct->data, project_struct->n_elements);
    printf("\nStarting algorithm with %d levels and %d processes...\n", project_struct->n_levels, project_struct->n_processes);

    /* Create workers */
    for(t = 0; t < project_struct->n_processes; t++) {
        pid[t] = fork();
        if(pid[t] < 0) {
            perror("Fork");
            kill_the_children();
            return ERROR;
        }
        else if (pid[t] == 0) {
            break;
        }
    }

    /* Child */
    if (pid[t] == 0) {
        act_child.sa_handler = child_handler;
        sigemptyset(&act_child.sa_mask);
        sigaddset(&act_child.sa_mask, SIGTERM);
        act_child.sa_flags = 0;
        sigaction(SIGTERM, &act_child, NULL);
        /* Receive from queue */
        while(mq_receive(queue, (char *)&message, sizeof(message), NULL) == -1) {
            /* Just in case the mq_receive does something funny */
            if(sigterm_received) {
                child_handler(SIGTERM);
            }
            /* Solve tasks */
            sem_wait(mutex);
            solve_task(project_struct, message.queue_level, message.queue_task);
            plot_vector(project_struct->data, project_struct->n_elements);
            printf("\n%10s%10s%10s%10s%10s\n", "PID", "LEVEL", "PART", "INI", \
                "END");
            printf("%10d%10d%10d%10d%10d\n", getpid(), message.queue_level, message.queue_task, \
                project_struct->tasks[message.queue_level][message.queue_task].ini, project_struct->tasks[message.queue_level][message.queue_task].end);
        
            /* Task completed */
            project_struct->tasks[message.queue_level][message.queue_task].completed = COMPLETED;
            sem_post(mutex);
            /* Advise parent with SIGUSR1 */
            kill(project_struct->ppid, SIGUSR1);
        }
        fprintf(stderr, "Error receiving message\n");
        kill(getppid(), SIGUSR1);
        if(pid) free(pid);
        mq_close(queue);
        shm_unlink(SHM_NAME);
        exit(EXIT_SUCCESS);
    }
    /* Parent */
    /* For each level, and each part, the corresponding task is solved. */
    for (i = 0; i < project_struct->n_levels; i++) {

        /* Task solving */
        for (j = 0; j < get_number_parts(i, project_struct->n_levels); j++) {

            /* Set message */
            message.queue_level = i;
            message.queue_task = j;
                
            /* Queue send */
            if (mq_send(queue, (char *) &message, sizeof(message), 1) == -1) {
                perror("Error sending message\n");
                free(pid);
                shm_unlink(SHM_NAME);
                return ERROR; 
            }
        }

        /* Wait for workers */
        while (check != t) {
            /* No need to use a mask here. If it's CTRL-C it'll be dealt with */
             pause();
        }
        check = 0;
        plot_vector(project_struct->data, project_struct->n_elements);
        
    }

    /* All work done */
    for (t = 0; t < project_struct->n_processes; t++) {
        kill(pid[t], SIGTERM);
    }
    
    free(pid);
    mq_close(queue);
    shm_unlink(SHM_NAME);
    printf("\nAlgorithm completed\n");
    
    return OK;    
}