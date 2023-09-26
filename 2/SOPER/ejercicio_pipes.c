/**
 * @file ejercicio_pipes.c
 * @author Pablo Almarza (pablo.almarza@estudiante.uam.es)
 * @author Jorge Gonzalez (jorge.gonzalezgomez01@estudiante.uam.es)
 * @brief A partir de un proceso padre, se crearan dos procesos hijos.
 * Todos ellos se comunicaran mediante tuberias, un hijo creara un numero
 * y se lo pasara al padre mediante una tuberia, mientras por otra tuberia 
 * el padre enviara dicho numero a su otro hijo
 * @version 1.2
 * @date 2020-02-24
 * 
 * 
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/**
 * @brief Funcion que calcula un numero aleatorio entre 0 y 10
 * 
 * @return int Un numero aleatorio
 */
int random_number() {
    int num;
    int upper = 10;
    int lower = 1;

    num = (rand() % (upper - lower +1) + lower);

    return num;
}

int main(void) {
    
    FILE *pf;
    int fd[2]; 
    int fd2[2];
    int num;
    char readbuffer[127];
    int readpipe = pipe(fd); /* Crear pipe para lectura */
    int writepipe = pipe(fd2); /* Crear pipe para escritura */

    /* Abrir el archivo como escritura */
    pf = fopen("numero_leido.txt", "w");
    srand(time(NULL));
    /* Error control */
    if(!pf) {
        perror("file");
        exit(EXIT_FAILURE);
    }
    /* Error control */
    if (readpipe == -1) {
        perror("readpipe");
        exit(EXIT_FAILURE);
    }

    /* Error control */
    if (writepipe == -1) {
        perror("writepipe");
        exit(EXIT_FAILURE);
    }

    /* Crear los hijos */
    pid_t readfromchild = fork();
    /* Ponemos writeinchild a -2 para no crear un hijo del hijo*/
    pid_t writeinchild = -2;
    /* Comprobamos que el proceso actual sea el padre antes de crear el fork */
    if(readfromchild != 0) writeinchild = fork();

    /* Error control */
    if (readfromchild == -1) {
        perror("fork readfromchild");
        exit(EXIT_FAILURE);
    }

    /* Error control */
    if (writeinchild == -1) {
        perror("fork writeinchild");
        exit(EXIT_FAILURE);
    }

    if(readfromchild == 0) {
        /* Cerrar el descriptor del hijo que crea el número */
        close(fd[0]);
        
        /* Escribir el número aleatorio generado y enviarlo por la tubería */
        num = random_number();
        char sendBuf[4];
        sprintf(sendBuf, "%d", num);
        ssize_t nbytes = write(fd[1], sendBuf, 4);
        if(nbytes == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        printf("He escrito el numero (%d) y lo he enviado al padre\n", num);

    } else if (writeinchild == 0) {
        /* Cerrar el descriptor del hijo que crea el número y cerrar la otra tuberia para que no espere para siempre */
        close(fd[0]);
        close(fd[1]);
        close(fd2[1]);

        /* Leer el número recibido del padre y escribirlo en el fichero */
        ssize_t nbytes = 0;
        do {
            nbytes = read(fd2[0], readbuffer, sizeof(readbuffer));
            if (nbytes == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
            }
            if (nbytes > 0) {
                printf("He recibido el numero del padre: %.*s\n", (int)nbytes, readbuffer);
                fprintf(pf, "%.*s", (int)nbytes, readbuffer);
            }
        } while(nbytes != 0);
        fclose(pf);
        exit(EXIT_SUCCESS);
    } else {
        /* Cerrar el descriptor del padre que lee el número creado */
        close(fd[1]);

        /* Leer el número recibido del hijo */
        ssize_t nbytes = 0;
        do {
            nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
            if (nbytes == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
            }
            if (nbytes > 0) {
                printf("He recibido el numero del hijo: %.*s\n", (int)nbytes, readbuffer);
                /* Escribir el número aleatorio generado y enviarlo por la tubería */
                ssize_t n_bytes = write(fd2[1], readbuffer, (int)nbytes);
                if(n_bytes == -1) {
                    perror("write");
                    exit(EXIT_FAILURE);
                }
                printf("He escrito el numero en el hijo: %.*s\n", (int)nbytes, readbuffer);
            }
        } while(nbytes != 0);

        /*Cerrar el descriptor del padre que escribe el numero creado y lo manda al hijo */
        close(fd2[0]);
    }

    wait(NULL);
    exit(EXIT_SUCCESS);
}