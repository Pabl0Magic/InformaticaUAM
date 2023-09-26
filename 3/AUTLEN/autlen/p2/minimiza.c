#include "minimiza.h"

/* Matriz de transiciones (hecha desde 0
 * ya que P1 no esta correcta)
 */
Estado*** matriz_transiciones;
Estado* est;
int filas, columnas, tam;

/* Matriz de distinguibles */
int** matriz_indistinguibles;

/**
 * @brief Funcion que guarda un array con los nombres de
 * los estados.
 * 
 * @param afd El automata
 * @return char** Array con el nombre del estado concatenado
 */
char** nombreEstado(AFND *afd) {
    char **estado;
    int i;

    estado = (char**)malloc(sizeof(char*));

    for (i = 0; i < AFNDNumEstados(afd); i++) {
        estado[i] = (char*)malloc(sizeof(char));
        strcpy(estado[i], AFNDNombreEstadoEn(afd, i));
    }

    return estado;
}

/**
 * @brief Funcion que estudia todas las transiciones de un estado con un simbolo
 * y crea un array de estados a los que dicho estado transita
 * 
 * @param afd El automata
 * @param ind_estado El estado del que se quieren obtener las transiciones
 * @param simbolo El simbolo que se estudia
 * @param lambda Parametro lambda que, si vale 0 estudia las transiciones normales
 * y si vale 1, se estudian las lambda
 * @return Estado* 
 */
Estado* transiciona(AFND* afd, int ind_estado, char* simbolo, int lambda) {
    int i, j = 0;
    Estado *transiciones;
    char** estado;
    
    estado = nombreEstado(afd);
    transiciones = (Estado*)calloc(AFNDNumEstados(afd), sizeof(Estado));
    
    for (i = 0; i < AFNDNumEstados(afd); i++) {
        if(lambda = 0) {
            /* Comprobar que existe transicion, y de ser asi, copiar el nombre del estado (llevando la cuenta de las transiciones hechas) */
            if(AFNDTransicionIndicesEstadoiSimboloEstadof(afd, ind_estado, AFNDIndiceDeSimbolo(afd, simbolo), AFNDIndiceEstadoEn(afd, estado[i])) {
                strcpy(transiciones[j].nombre, estado[i]);
                transiciones[j].indice = AFNDIndiceEstadoEn(afd, estado[i]);
                j++;
            } else {
                /* Comprobar que hay transicion lambda y ver que no es el mismo estado (strcmp no debe devolver 0) */
                if(AFNDCierreLTransicionIJ(afd, ind_estado, AFNDIndiceEstadoEn(afd, estado[i])) == 1 && strcmp(AFNDNombreEstadoEn(afd, ind_estado), AFNDNombreEstadoEn(afd, AFNDIndiceEstadoEn(afd, estado[i]))) != 0 ) {
                strcpy(transiciones[j].nombre, estado[i]);
                transiciones[j].indice = AFNDIndiceEstadoEn(afd, estado[i]);
                j++;
                }
            }
        }
    }

    /* Liberar toda la memoria utilizada */

    for(i = 0; i < AFNDNumEstados(afd); i++) {
        free(estado[i]);
    }
    free(estado);

    if(j = 0) {
        free(transiciones);
        return NULL;
    }
    
    return transiciones;
}

/**
 * @brief Esta funcion crea una matriz de estados a partir del automata original
 * 
 * @param afd El automata
 */
void crearMatrizTransiciones(AFND* afd) {
    int i, j;
    matriz_transiciones = (Estado***)calloc(tam, sizeof(Estado**));

    for(i = 0; i < filas; i++) {
        matriz_transiciones[i] = (Estado**)calloc(columnas, sizeof(Estado*));
    } 
    
    for(i = 0; i < filas; i++) {
        for(j = 0; j < columnas; j++) {
            est = transiciona(afd, i, AFNDSimboloEn(afd, j), 0);
            matriz_transiciones[i][j] = est;
        }
    }
}

/**
 * @brief Crea la matriz de estados indistinguibles desde 0 
 * 
 */
void crearMatrizIndistinguible() {
    int i, j;
    matriz_indistinguibles = (int **)calloc(tam, sizeof(int*));
    
    for(i = 0; i < tam; i++) {
        matriz_indistinguibles[i] = (int*)calloc(tam, sizeof(int));
    }

    /* Se inicializa a 1 presuponiendo que todos son indistinguibles */
    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            matriz_indistinguibles[i][j] = 1;
        }
    }


}















/**
 * @brief Funcion que busca si un estado transiciona con un simbolo
 * a otro estado. En el caso de haber transicion, se devuelve el 
 * estado al que hace la transicion para encontrar y agrupar los
 * estados equivalentes 
 * 
 * @param afd El automata finito determinista
 * @param estado Estado actual desde donde se visitan todas sus transiciones
 * @param indiceSimbolo Simbolo con el que se transiciona
 * @return int El estado al que transiciona o -1 si no hay transicion
 */
/*
int transiciona(AFND* afd, int estado, int indiceSimbolo) {
    int i = 0;

    for(i = 0; i < AFNDNumEstados(afd); i++) {
        if(AFNDTransicionIndicesEstadoiSimboloEstadof(afd, estado, indiceSimbolo, i)) {
             Si hay transicion, devuelve el estado al que transiciona 
            return i;
        }
    }

    return -1;
}*/

int **crea_matriz_distinguibles(AFND* afd){
    int **matriz_distinguibles;
    int clase1, clase2, change = 0, i, j, k, t1, t2;

    matriz_distinguibles = (int**)malloc(sizeof(int*)*AFNDNumEstados(afd));
    for(i = 0; i < AFNDNumEstados(afd); i++) {
        matriz_distinguibles[i] = (int*)malloc(sizeof(int) *AFNDNumEstados(afd));
    }

    if(!matriz_distinguibles) {
        return NULL;
    }

    /* Crear matriz de estados distinguibles */
    for(i = 0; i < AFNDNumEstados(afd); i++) {
        for(j = 0; j < i; j++) {
            clase1 = AFNDTipoEstadoEn(afd, i);
            clase2 = AFNDTipoEstadoEn(afd, j);
            /* Equivalentes por tipo de Estado(en concreto, estado final)
             * Si uno es final y el otro no, se marca.
             * 
             */
            if(clase1 == FINAL || clase1 == INICIAL_Y_FINAL) {
                if(clase2 == FINAL || clase2 == INICIAL_Y_FINAL) {
                    matriz_distinguibles[i][j] = 0;
                    matriz_distinguibles[j][i] = 0; 
                } else {
                    matriz_distinguibles[i][j] = 1;
                    matriz_distinguibles[j][i] = 1;
                }
            } else {
                if(clase2 == FINAL || clase2 == INICIAL_Y_FINAL) {
                    matriz_distinguibles[i][j] = 1;
                    matriz_distinguibles[j][i] = 1;
                } else {
                    matriz_distinguibles[i][j] = 0;
                    matriz_distinguibles[j][i] = 0;
                }
            }
        }
    }
    /**
     * @brief Hay que comprobar por pares si los estados son efectivamente distintos.
     * Si, por ejemplo, q0q1 van con el mismo simbolo a q2q3 y estos dos son distintos,
     * entonces q0q1 tambien son distintos, luego hay que cambiar la matriz. Esto
     * se hara en bucle hasta que la matriz deje de tener cambios.
     * 
     */
    while(change == 1) {
        change = 0;
        for(i = 0; i < AFNDNumEstados(afd); i++) {
            for(j = 0; j < i; j++) {
                /* Si no esta marcado, hay que explorar*/
                if(matriz_distinguibles[i][j] == 0) {
                    for(k = 0; k < AFNDNumSimbolos(afd); k++) {
                        /* Explorar todas las transiciones de los estados con los diferentes simbolos */
                        t1 = transiciona(afd, i, k);
                        t2 = transiciona(afd, j, k);
                        
                        /* Si los estados son diferentes, mirar si entre ellos son distintos */
                        if(t1 != t2) {
                            if(matriz_distinguibles[t1][t2] == 1) {
                                /* Si esta marcado, cambiar la matriz */
                                matriz_distinguibles[i][j] = 1;
                                matriz_distinguibles[j][i] = 1;
                                change = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }       

    return matriz_distinguibles;
}

AFND* AFNDMinimiza(AFND* afd) {
    int **matriz_distinguibles;
    
    /* En esta primera parte creamos la matriz de trnasiciones desde 0, ya que la P1 esta incorrecta */
    
    filas = AFNDNumEstados(afd);
    columnas = AFNDNumSimbolos(afd);
    tam = AFNDNumEstados(afd);

    crearMatrizTransiciones(afd);
    
    matriz_distinguibles = crea_matriz_distinguibles(afd);

    /**
     * Falta:
     *      -Hacer funcion/es para identificar los estados inaccesibles
     *      -Hacer contador con los nuevos estados 
     *      -Renombrar los nuevos estados
     *      -Asignar las nuevas transiciones
     *      -Crear el nuevo automata(ya que no podemos utilizar AFNDTransforma porque no funciona)
     *      -Liberar toda la memoria(porque va a haber que reservar mas cosas)
     *      -Probablemente lo de matriz_distingubles sea una funcion 
     *      -
     */

}