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

// Definición general de macros necesarios para mayor legibilidad.
extern int errno;
#define SEM_NAME "/sem_babuino"
#define DATAFILE "data.txt"

// Variables globales necesarias para la captación de señales.
int alarm_caught, N, success_flag;
FILE *file;
// Array usado para los hijos
pid_t *pid;
// Semáforo usado como variable global para el manejador de SIGTERM en los hijos
sem_t *sem = NULL;

// Máscara usada para sigprocmask para evitar que se corte el manejador de la alarma
sigset_t act_anti_sigusr2;

// Función para acabar con los hijos
void kill_the_children() {
    int i;
    for (i = 0; i < N; i++) {
        kill(pid[i], SIGTERM);
    }
}

// Manejador del proceso padre
void parent_handler(int sig) { 
    sigset_t oldmask;
    int nproc;
    sigprocmask(SIG_BLOCK, &act_anti_sigusr2, &oldmask);
    sem_wait(sem);
    switch (sig) {
        case SIGALRM:
            // Si esta "flag" no ha sido activada antes que la flag "success_flag"
            // el programa recorrerá otro camino. De lo contrario, imprimirá que falta trabajo.
            alarm_caught = 1;
            kill_the_children();
            break;
        case SIGUSR2:
            if (file != NULL) {
                fclose(file);
                file = NULL;
            }
            file = fopen(DATAFILE, "r");
            fscanf(file, "%d", &nproc);
            printf("Recibido SIGUSR2 numero %d\n", nproc);
            if (nproc == N) {
                // Hemos recibido a todos los hijos. Mandamos SIGTERM a todos los hijos
                // y activamos la flag "success_flag"
                success_flag = 1;
                kill_the_children();
            }
            fclose(file);
            file = NULL;
            // Aceptamos otra señal
            break;
    }
    sem_post(sem);
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
}
// Manejador de los procesos hijos
void child_term_handler(int sig) {
    if(sig == SIGTERM)
    {
        sem_close(sem);
        if(file != NULL) {
            fclose(file);
            file = NULL;
        }
        // Liberamos su memoria allocada
        free(pid);
        printf("Finalizado %d\n", getpid());
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char** argv){
    int i, T;
    
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <N> <T>", argv[0]);
        return 1;
    }

    // Semáforo de E/S (I/O)
    CREATE_SEMAPHOR:
    if ((sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) { 
		// 17 significa que el semáforo ya existe
        if (errno == 17) {
            sem_unlink(SEM_NAME);
            goto CREATE_SEMAPHOR;
        }
        else {
            perror("sem_open");
		    exit(EXIT_FAILURE);
        }
	}
    
    // Inicialización y lectura de variables
    N = atoi(argv[1]);
    T = atoi(argv[2]);
    pid = (pid_t*) malloc(N * sizeof(pid_t));
    if (!pid) {
        perror("pid array");
        exit(EXIT_FAILURE);
    }
    
    /* Inicializa los manejadores */
    struct sigaction act_signals;
    act_signals.sa_handler = parent_handler;
    sigemptyset(&act_signals.sa_mask);
    sigaddset(&act_signals.sa_mask, SIGUSR2);
    sigaddset(&act_signals.sa_mask, SIGALRM);
    act_signals.sa_flags = 0;
    sigaction(SIGUSR2, &act_signals, NULL);
    sigaction(SIGALRM, &act_signals, NULL);

    /* Inicializa la variable para ignorar SIGUSR2 cuando se maneja la alarma*/
    sigemptyset(&act_anti_sigusr2);
    sigaddset(&act_anti_sigusr2, SIGUSR2);
    /* Escribe 0\n0 en el fichero y ciérralo */
    file = fopen(DATAFILE, "w");
    fprintf(file, "0\n0\n");
    fclose(file);


    for (i = 0; i < N; i++) {
        pid[i] = fork();
        if(pid[i] < 0) {
            perror("fork\n");
            return -1;
        }
        if (pid[i] == 0) {
            pid_t childPid = getpid();
            int n_proc;
            unsigned long results;
            struct sigaction child_act;

            // Añade el manejador de SIGTERM
            child_act.sa_handler = child_term_handler;
            sigemptyset(&child_act.sa_mask);
            sigaddset(&child_act.sa_mask, SIGTERM);
            child_act.sa_flags = 0;
            sigaction(SIGTERM, &child_act, NULL);
            
            register unsigned int result;
            int limit = childPid / 10;
            for (register int j = 1; j <= limit; j++) {
                result += j;
            }
            sem_wait(sem);
            /* REGIÓN CRÍTICA */
            // Abre el fichero como lectura y escritura
            file = fopen(DATAFILE, "r+");
            
            // Lee los contenidos del fichero (asumimos que se deben leer las dos primeras líneas)
            fscanf(file, "%d", &n_proc);
            fscanf(file, "%lu", &results);

            // Computa los números localmente
            n_proc++;
            results += result;
            
            // Vuelve al principio y escribe los resultados
            fseek(file, 0, SEEK_SET);
            fprintf(file, "%d\n%lu", n_proc, results);
            
            // Cierra el archivo
            fclose(file);
            file = NULL;

            // Hacemos UP al semáforo           
            sem_post(sem);

            // Manda la señal al padre de que ya ha terminado si no se ha enviado ninguna otra señal
            kill(getppid(), SIGUSR2);

            // Espera a la señal SIGTERM.
            // Si se finalizara el proceso sin pasar por el manejador, este proceso acabaría con código EXIT_FAILURE
            sigset_t child_set;
            sigfillset(&child_set);
            sigdelset(&child_set, SIGTERM);
            sigsuspend(&child_set);

            printf("Error en PID: %d\n", getpid());
            exit(EXIT_FAILURE);
        }
    }

    alarm(T);
    
    sigset_t parent_set;
    sigfillset(&parent_set);
    sigdelset(&parent_set, SIGALRM);
    sigdelset(&parent_set, SIGUSR2);

    alarm_caught = 0;
    success_flag = 0;
    while (alarm_caught == 0 && success_flag == 0) {
        sigsuspend(&parent_set);
    }
    
    // Cuando saltamos del sigsuspend, matamos a los hijos
    kill_the_children();
    if (!success_flag) {
        int proc_written;
        file = fopen(DATAFILE, "r");
        fscanf(file, "%d", &proc_written);
        fclose(file);
        if (proc_written != N) {
            printf("Falta trabajo\n");
            exit(EXIT_FAILURE);
        }
    }
    
    while (wait(NULL) > 0) ;
    int n_proc;
    unsigned long results;
    file = fopen(DATAFILE, "r");
    fscanf(file, "%d", &n_proc);
    fscanf(file, "%lu", &results);
    printf("Han acabado todos, resultado: %lu\n", results);
    sem_unlink(SEM_NAME);
    free(pid);
    exit(EXIT_SUCCESS);
}