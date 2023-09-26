#ifndef TRANSFORMA_H
#define TRANSFORMA_H

#include "afnd.h"

#define MAX_NOMBRE 50
#define MAX_INDICE 50

/**
 * @brief Estructura para almacenar el nombre y el indice de un 
 * estado simple (no compuesto por otros estados)
 * 
 */
typedef struct {
    char nombre[MAX_NOMBRE];
    int indice;
} Estado;

/**
 * @brief Estructura para almacenar un estado formado por varios
 * estados. Guarda tanto el nombre como el indice del estado, 
 * ademas de todos los indices de los que se compone el estado y 
 * el tipo de estado que es (final, inicial, inicial y final, normal)
 * 
 * Se guardan los indices para cuando haya que visitar este estado, 
 * visitar todos los estados que lo componen
 * 
 */
typedef struct {
    char nombre[MAX_NOMBRE];
    int indice[MAX_INDICE];
    int numIndices;
    int tipo;
} ConjuntoEstados;

/**
 * @brief Estructura en la que nos basaremos para estudiar los estados
 * en la matriz de transiciones. Almacena el estado al que se transita
 * desde la casilla en la que se esta y si la casilla ha sido ya estudiada
 * 1 = estudiado // 0 = no estudiado
 * 
 */
typedef struct {
    ConjuntoEstados siguiente;
    int estudiado;
} Casilla;

/**
 * @brief Esta funciona transforma un automata no determinista a uno finito determinista
 * 
 * @param afd El automata que se tiene que transformar
 * @return El automata determinista 
 */
AFND* AFNDTransforma(AFND*  afnd);

#endif