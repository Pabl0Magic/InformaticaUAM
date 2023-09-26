#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minimiza.h"

int numClases = 0;
/**
 * Reserva memoria para un estado y lo returnea
 */
Estado* crearEstado(int numEstados) {
    Estado* estado = NULL;

    estado = (Estado *)malloc(1*sizeof(Estado));

    estado->estados = (int *)calloc(numEstados,sizeof(int));
    
    estado->numEstados = numEstados;
    estado->tipo = NORMAL;
    estado->numClases = 0;

    return estado;
}

/**
 * Libera la memoria de un estado
 */
void freeEstado(Estado* estado) {

    free(estado->estados);
    free(estado);

}

/**
 * Crea el nombre del estado concatenando los nombres de los estados que esta formado
 */
void nombreEstados(AFND *afnd, Estado *estado) {
    int i;
    char nombre[MAX_NOMBRE];

    strcpy(nombre, AFNDNombreEstadoEn(afnd, estado->estados[0]));
    for(i = 1; i < estado->numEstados; i++) {
        strcat(nombre, AFNDNombreEstadoEn(afnd, estado->estados[i]));
    }

    strcpy(estado->nombre, nombre);
}

/**
 * Especifica el tipo del eswtado pasado com argumento
 */
void tipoEstado(AFND *afnd, Estado *estado, int estadoInicial) {
    int i;

    /* estadoInicial == 0 => No hay estado inicial */
    if(estadoInicial==0){
        for(i=0; i<estado->numEstados; i++){

            if(estado->tipo==FINAL){
                if(AFNDTipoEstadoEn(afnd, estado->estados[i]) == INICIAL || AFNDTipoEstadoEn(afnd, estado->estados[i]) == INICIAL_Y_FINAL){
                    estado->tipo = INICIAL_Y_FINAL;
                    return;
                }
            }else if(estado->tipo==INICIAL){
                if(AFNDTipoEstadoEn(afnd, estado->estados[i]) == FINAL || AFNDTipoEstadoEn(afnd, estado->estados[i]) == INICIAL_Y_FINAL){
                    estado->tipo = INICIAL_Y_FINAL;
                    return;
                }
            }else if(estado->tipo==NORMAL){
                if(AFNDTipoEstadoEn(afnd, estado->estados[i]) == INICIAL){
                    estado->tipo = INICIAL;
                }else if(AFNDTipoEstadoEn(afnd, estado->estados[i]) == FINAL){
                    estado->tipo = FINAL;
                } else if(AFNDTipoEstadoEn(afnd, estado->estados[i]) == INICIAL_Y_FINAL){
                    estado->tipo = INICIAL_Y_FINAL;
                    return;
                }
            }
            
        }
    } else {
        for(i=0; i<estado->numEstados; i++){
            if(estado->tipo==NORMAL){
                if(AFNDTipoEstadoEn(afnd, estado->estados[i]) == FINAL || AFNDTipoEstadoEn(afnd, estado->estados[i]) == INICIAL_Y_FINAL){
                    estado->tipo = FINAL;
                    return;
                }
            }
        }
    }
}

/**
 * Crea un array que indica que estados son accesibles o no y devuelve dicho array 
 */
int* buscarEstadosInaccesibles(AFND *afnd) {
    int *estadosAccesibles = NULL;
    int i, j, k, transiciona, numEstados,  numSimbolos, estadoInicial;

    estadoInicial = AFNDIndiceEstadoInicial(afnd);

    estadosAccesibles = (int *)calloc(AFNDNumEstados(afnd),sizeof(int));

    for(i = 0; i < AFNDNumEstados(afnd); i++) {
        estadosAccesibles[i] = INACCESIBLE;
    }

    estadosAccesibles[estadoInicial] = ACCESIBLE;

    for(i = 0; i < AFNDNumEstados(afnd); i++) {
        for(j = 0; j < AFNDNumSimbolos(afnd) && estadosAccesibles[i] != ACCESIBLE; j++) {
            for(k = 0; k < AFNDNumEstados(afnd) && estadosAccesibles[i] != ACCESIBLE; k++) {
                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, j, k) == 1) {
                    estadosAccesibles[i] = ACCESIBLE;
                }
            }
        }
    }

    return estadosAccesibles;
}

/**
 * Crea y returnea un AFND en el que inserta solo los estados accesibles ademas de los simbolos y transiciones
 */
AFND* borrarEstadosInaccesibles(AFND *afnd, int *estadoAccesible) {
    AFND *aux = NULL;
    int i, j, k, numEstados = 0;

    for(i = 0; i < AFNDNumEstados(afnd);i++) {
        if(estadoAccesible[i] == ACCESIBLE) {
            numEstados++;
        }
    }

    if(numEstados == AFNDNumEstados(afnd)) {
        return afnd;
    }

    aux = AFNDNuevo("afndAccesibles", numEstados,  AFNDNumSimbolos(afnd));

    for(i = 0; i < AFNDNumEstados(afnd); i++) {
        if(estadoAccesible[i] == ACCESIBLE) {
            AFNDInsertaEstado(aux, AFNDNombreEstadoEn(afnd, i), AFNDTipoEstadoEn(afnd, i));
        }
    }
    for(i = 0; i < AFNDNumSimbolos(afnd); i++) {
        AFNDInsertaSimbolo(aux, AFNDSimboloEn(afnd, i));
    }

    for(i = 0; i < AFNDNumEstados(afnd); i++){
        if(estadoAccesible[i] == ACCESIBLE){
            for(j = 0; j < AFNDNumSimbolos(afnd); j++){
                for(k = 0; k < AFNDNumEstados(afnd); k++){
                    if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, j, k)){
                        AFNDInsertaTransicion(aux, AFNDNombreEstadoEn(afnd, i), AFNDSimboloEn(afnd, j), AFNDNombreEstadoEn(afnd, k));
                    }
                }
            }
        }       
    }

    return aux;
}

/**
 * Crea y returnea una matriz con todos los valores inicializados a indistinguible
 */
int** matrizIndistinguibles(AFND* afnd){
    int** res = NULL, i, j;

    res = (int**)malloc(AFNDNumEstados(afnd)*sizeof(int*));

    for (i=0; i < AFNDNumEstados(afnd); i++){
        res[i] = (int*)malloc(AFNDNumEstados(afnd)*sizeof(int));
    }

    for (i=0; i<AFNDNumEstados(afnd); i++){
        for (j=0; j<AFNDNumEstados(afnd); j++){
            res[i][j]=INDISTINGUIBLE;
        }
    }

    return res;
}

/**
 * En la matriz de distinguibles, setea a indistinguibles los estados finales de los normales
 */
void encontrardistinguiblesFinales(AFND* a, int** matriz){
    int i, j, tipo, tipo2;
    int **matriz_aux = NULL;

    for (i=0; i < AFNDNumEstados(a); i++){
        tipo = AFNDTipoEstadoEn(a, i);
        if(tipo == FINAL || tipo == INICIAL_Y_FINAL){
            for (j=0; j < AFNDNumEstados(a); j++){
                tipo2 = AFNDTipoEstadoEn(a, j);
                if (tipo2 != FINAL && tipo2 != INICIAL_Y_FINAL){
                    matriz[i][j] = DISTINGUIBLE;
                    matriz[j][i] = DISTINGUIBLE;
                }
            }
        }
    }
}

/**
 * Encuentra el resto de estados distinguibles y lo setea en la amtriz de indistinguibles
 */
void encontrarDistinguibles(AFND* a, int** matriz){
    int i, j, flag = 1, simb, dest1, dest2;
    int** matriz_aux = NULL;

    
    while (flag == 1){
        
        for (flag = 0,i  =0; i < AFNDNumEstados(a); i++){
            for (j = 0; j < AFNDNumEstados(a); j++){
                if (matriz[i][j] == INDISTINGUIBLE){
                    for (simb = 0; simb < AFNDNumSimbolos(a); simb++){
                        for (dest1 = 0; dest1 < AFNDNumEstados(a); dest1++){
                            if(AFNDTransicionIndicesEstadoiSimboloEstadof(a, i, simb, dest1) == 1)
                                break;
                        }
                        for (dest2 = 0; dest2 < AFNDNumEstados(a); dest2++){
                            if(AFNDTransicionIndicesEstadoiSimboloEstadof(a, j, simb, dest2) == 1)
                                break;
                        }
                        if (matriz[dest1][dest2] == DISTINGUIBLE){
                            matriz[i][j] = DISTINGUIBLE;
                            matriz[j][i] = DISTINGUIBLE;
                            flag = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}

/**
 * Agrupamos los estados en base a si pertenecen a una misma clase o no
 * 
 */
int* crearClasesEquivalencia(AFND* afnd, int **matriz) {
    int i, j, flag = 0, *clase = NULL;
    
    clase = (int*)malloc(AFNDNumEstados(afnd)*sizeof(int));

    for(i = 0 ; i < AFNDNumEstados(afnd); i++){
        clase[i] = -1;
    }

    for(i = 0; i < AFNDNumEstados(afnd); i++) {
        for(flag=0, j = 0; j < AFNDNumEstados(afnd); j++) {
            if(matriz[i][j] == INDISTINGUIBLE) {
                flag = 1;
                if(clase[i] == -1) {
                    clase[i] = numClases;
                    numClases++;
                } else if(clase[j] == -1) {
                    clase[j] = clase[i];
                }
            } 
        }
        /* Clase unitaria */
        if(flag == 0) {
            clase[i] = numClases;
            numClases++;
        } 
    }

    return clase;
}

/**
 * 
 */
Estado **crearArray(AFND *afnd, int* clase) {
    Estado **estado = NULL;
    int i, j, k, numEstados = 0, estadoInicial = 0;

    estado = (Estado**)malloc(numClases*sizeof(Estado*));

    for(i = 0; i < numClases; i++) {
        for(numEstados = 0, j = 0; j < AFNDNumEstados(afnd); j++) {
            if(clase[j] == i) {
                numEstados++;
            }
        }

        estado[i] = crearEstado(numEstados);
    }
    numEstados = 0;

    for(i = 0; i < numClases; i++) {
        for(numEstados = 0, j = 0; j < AFNDNumEstados(afnd); j++) {
            if(clase[j] == i) {
                estado[i]->estados[numEstados] = j;
                numEstados++;
            }
        }

        estado[i]->numClases = numClases;
        nombreEstados(afnd, estado[i]);
        tipoEstado(afnd, estado[i], estadoInicial);
        if(estado[i]->tipo == INICIAL || estado[i]->tipo == INICIAL_Y_FINAL) {
            estadoInicial = 1;
        }
    }

    return estado;
    
}

/**
 * Crea el AFD minimizado y le inserta los elementos finales
 */
AFND *automataMinimizadoCompleto(AFND *afnd, Estado **estado){
    AFND *aux = NULL;
    int i, j, k, a, b;
    int indEstadoOrigen, flag = 0;

    aux = AFNDNuevo("afndMin", estado[0]->numClases, AFNDNumSimbolos(afnd));

    for(i = 0; i < AFNDNumSimbolos(afnd); i++){
        AFNDInsertaSimbolo(aux, AFNDSimboloEn(afnd, i));
    }

    for(i = 0; i < estado[0]->numClases; i++){
        AFNDInsertaEstado(aux, estado[i]->nombre, estado[i]->tipo);
    }

    for(i = 0; i < estado[0]->numClases; i++){
        indEstadoOrigen = estado[i]->estados[0];
        
        for(j = 0; j < AFNDNumSimbolos(afnd); j++){
            for(flag = 0, k = 0; k < AFNDNumEstados(afnd); k++){
                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, indEstadoOrigen, j, k)==1){
                    for(a = 0; a < estado[0]->numClases; a++){
                        for(b = 0; b<estado[a]->numEstados; b++){
                            if(estado[a]->estados[b] == k){
                                AFNDInsertaTransicion(aux, AFNDNombreEstadoEn(aux, i), AFNDSimboloEn(aux, j), AFNDNombreEstadoEn(aux, a));
                                flag=1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return aux;

}

/**
 * 
 */
AFND* AFNDMinimiza(AFND* afnd){
    AFND* afd_aux = NULL, *minimizado = NULL;
    int *clasesEquivalencia = NULL, *estadosAccesibles = NULL;
    int** indist = NULL;
    Estado **array = NULL;
    int i, aux;

    estadosAccesibles = buscarEstadosInaccesibles(afnd);
    afd_aux = borrarEstadosInaccesibles(afnd, estadosAccesibles);    
    
    indist = matrizIndistinguibles(afd_aux);
    encontrardistinguiblesFinales(afd_aux, indist);
    encontrarDistinguibles(afd_aux, indist);

    clasesEquivalencia = crearClasesEquivalencia(afd_aux, indist);

    array = crearArray(afd_aux, clasesEquivalencia);
    minimizado = automataMinimizadoCompleto(afd_aux, array);


    /* Free matriz indistinguibles */
    for(i = 0; i < AFNDNumEstados(afnd); i++) {
        if(indist[i]) {
            free(indist[i]);
        }
    }
    if(indist) {
        free(indist);
    }

    /* Free claes equivalencia */
    free(clasesEquivalencia);

    /* Free estados inaccesibles */
    free(estadosAccesibles);

    /* Free array */
    if(array != NULL) {
        aux = array[0]->numClases;
        for(i = 0; i < aux; i++) {
            if(array[i]) {
                freeEstado(array[i]);
            }
        }
        free(array);
    }
    if(AFNDNumEstados(afnd)!=AFNDNumEstados(afd_aux)){
        AFNDElimina(afd_aux);
    }
    return minimizado;
}

