/**
 * @file ejercicio_hilos.c
 * @author Pablo Almarza (pablo.almarza@estudiante.uam.es)
 * @author Jorge Gonzalez (jorge.gonzalezgomez01@estudiante.uam.es)
 * @brief Se creara el numero de hilos que el usuario especfique y 
 * realizara el cubo de cada hilo, es decir, del hilo 1 el resultado 
 * sera 1, del hilo 2 el resultado sera 8, etc. Además, cada hilo tendrá 
 * un tiempo de espera, que sera guardado junto al resultado en la estructura param
 * @version 1.7
 * @date 2020-02-24
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

struct param {
    int time;
    int x;
};

/**
 * @brief Funcion que realiza la operacion de un numero al cubo 
 * y realiza la espera del numero aleatorio
 * 
 * @param arg estructura que guarda el tiempo de espera y el numero
 * @return void* el resultado del cubo
 */
void *cube_function(void * arg) {
    struct param* p = (struct param *)arg;
    int aux;
    int x;
    int *result;

    result = (int*) malloc(sizeof(int));
    if(!result) {
        printf("Error in memory allocation for the result.");
        exit(EXIT_FAILURE);
    }
    sleep(p->time); /* Esperar el tiempo del numero aleatorio */
    
    x = p->x;
    aux = x * x;
    *result = aux * x;

    return result;
}
/**
 * @brief Funcion que calcula un numero aleatorio entre 0 y 10
 * 
 * @param upper Limite superior del numero aleatorio
 * @param lower Limite inferior del numero aleatorio
 * @return int Un numero aleatorio entre el limite superior 
 * y el inferior
 */
int random_number(int upper, int lower) {
    int num;

    num = (rand() % (upper - lower +1) + lower);

    return num;
}

int main(int argc , char *argv []) {
    srand(time(NULL));

    int i, error, num_threads;
    pthread_t *thread;
    struct param* p;
    int upper = 10;
    int lower = 0;
    int *result;

    if(argc != 2) {
        printf("Debes de introducir el número de hilos\n");
        return EXIT_FAILURE;
    }
    num_threads = atoi(argv[1]);
    if (num_threads < 1) {
        printf("Debes introducir un número mayor que 0\n");
        return EXIT_FAILURE;
    }
    thread = (pthread_t*) malloc (num_threads * sizeof(pthread_t));
    p = (struct param*) malloc (num_threads * sizeof(struct param));
    if (!thread || !p) {
        printf("Error in memory allocation.");
        if(thread) free(thread);
        if(p) free(p);
        return EXIT_FAILURE;
    }

    for(i = 0; i < num_threads; i++) {
        p[i].x = i; /* Agregar el numero de hilo para hacer el cubo del mismo */
        p[i].time = random_number(upper, lower); /* Numero aleatorio entre 0 y 10 y guardado en la estructura*/
        
        /* Crear el hilo y comprobar que está bien */
        error = pthread_create(&thread[i], NULL, cube_function, &p[i]);
        if (error != 0) {
            fprintf(stderr , "pthread_create: %s\n", strerror(error));
            pthread_exit(&thread[i]);
        }
    }

    for(i = 0; i < num_threads; i++) {
        /* Join para esperar a que cada hilo termine. Se hace en todos los hilos */
        error = pthread_join(thread[i], (void**) &result);

        if (error != 0) {
            fprintf(stderr, "pthread_join: %s\n", strerror(error));
            pthread_exit(&thread[i]);
        }
        else printf("Hilo %d: %d\n", i, *result);
    }

    free(thread);
    free(p);
    printf("El programa %s finalizo correctamente\n", argv[0]);
    exit(EXIT_SUCCESS);
}
