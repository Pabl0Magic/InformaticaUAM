#ifndef MINIMIZA_H
#define MINIMIZA_H

#include "afnd.h"
#define INDISTINGUIBLE 0
#define DISTINGUIBLE 1
#define INACCESIBLE 0
#define ACCESIBLE 1
#define MAX_NOMBRE 200

typedef struct {  
    char nombre[MAX_NOMBRE];
    int *estados;
    int numEstados;
    int numClases;
    int tipo;
} Estado;


AFND *AFNDMinimiza(AFND * afnd);

#endif