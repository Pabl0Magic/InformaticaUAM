#include <stdio.h>
#include <stdlib.h>
#include "afnd.h"
#include <string.h>

/**
 * @brief Esta estructura contendra los 
 * estados indistinguibles. El maximo de 
 * estados que estados de una clase es
 * el numero de estados.
 * 
 */
typedef struct {
    int *estados;
    int max_estados;
} ClaseEquivalencia;

/**
 * @brief Esta estructura almacenara las
 * clases de equivalencia que vayan surgiendo.
 * Tiene como maximo el numero de estados.
 * 
 */
typedef struct {
    ClaseEquivalencia* clase;
    int max_clases;
} Conjunto;

/**
 * @brief Estructura que guardara la informacion
 * de un estado, esto es, su nombre y su indice.
 * 
 */
typedef struct {
    char* nombre;
    int indice;
} Estado;


AFND * AFNDMinimiza(AFND * afd);