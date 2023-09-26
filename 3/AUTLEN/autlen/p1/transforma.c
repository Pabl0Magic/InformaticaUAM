#include "transforma.h"
#include <string.h>
#define MAX 20

AFND * AFNDTransforma(AFND * afnd) {
    AFND *afd_final;
    int estado1, estado2, simbolo, qs, i, pos_ini, ep_indice;
    char *estado_partido, estado_inicial[MAX], *estado_aux, *estado_lambda;

    if(!afnd) {
        return NULL;
    }

    afd_final = AFNDNuevo("Final", AFNDNumEstados(afnd), AFNDNumSimbolos(afnd));
    if(!afd_final){
    	return NULL;
    }

    for(i = 0; i < AFNDNumSimbolos(afnd); i++){
    	AFNDInsertaSimbolo(afd_final, AFNDSimboloEn(afnd, i));
    }

    estado_partido = (char*)malloc(sizeof(char)*3);

    /* Calculo del estado inicial */
    pos_ini = AFNDIndiceEstadoInicial(afnd);
    strcpy(estado_inicial, AFNDNombreEstadoEn(afnd, pos_ini));

    printf("Creando estado inicial %s pos %d...\n", estado_inicial, pos_ini);
    for(i = 0; i < AFNDNumEstados(afnd); i++){ 
        if (AFNDLTransicionIJ(afnd, pos_ini, i) == 1) {
            strcat(estado_inicial, AFNDNombreEstadoEn(afnd, i));
            printf("Nuevo nombre: %s\n", estado_inicial);
        }
    }
    
    AFNDInsertaEstado(afd_final, estado_inicial, INICIAL);
    
    /*Para cada estado*/
    for(estado1 = 0; estado1 < AFNDNumEstados(afd_final); estado1++){
    	/*Estudias cada simbolo de ese estado*/
    	for(simbolo = 0; simbolo < AFNDNumSimbolos(afnd); simbolo++){
    		estado_aux = (char*)calloc(15,sizeof(char));
            estado_lambda = (char*)calloc(15,sizeof(char));

    		for(qs = 0; qs < strlen(AFNDNombreEstadoEn(afd_final, estado1)); qs += 2){
    			printf("Comprobamos estado %s simbolo %s\n", AFNDNombreEstadoEn(afd_final, estado1), AFNDSimboloEn(afnd, simbolo));

                
                *(estado_partido+0) = AFNDNombreEstadoEn(afd_final, estado1)[qs];  
                *(estado_partido+1) = AFNDNombreEstadoEn(afd_final, estado1)[qs+1];  
                *(estado_partido+2) = '\0';  
            
                ep_indice = (int)AFNDNombreEstadoEn(afd_final, estado1)[qs+1] - 48;
                printf("\tEstado %s...\n", estado_partido);
                
    			/*Estudias las transiciones con ese simbolo desde ese estado*/
	    		for(estado2 = 0; estado2 < AFNDNumEstados(afnd); estado2++){
	    			if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, ep_indice, simbolo, estado2) != 0){
                        /*Añadir los nombres de estado de forma alfabetica*/
                        if(strcmp(estado_aux, AFNDNombreEstadoEn(afnd, estado2)) != 0){
                            estado_aux = strcat(estado_aux, AFNDNombreEstadoEn(afnd, estado2));
                        }
                    }
	    		}
	    	}

            strcpy(estado_lambda, estado_aux);
            for(qs = 0; qs < strlen(estado_aux); qs += 2){
    			printf("Comprobamos trans lambda desde estado %s\n", estado_aux);
                
                *(estado_partido+0) = estado_aux[qs];  
                *(estado_partido+1) = estado_aux[qs+1];  
                *(estado_partido+2) = '\0'; 
            
                printf("\tEstado %s...\n", estado_partido);
                ep_indice = (int)estado_aux[qs+1] - 48;
    			/*Estudias las transiciones con ese simbolo desde ese estado*/
	    		for(estado2 = 0; estado2 < AFNDNumEstados(afnd); estado2++){
	    			if(AFNDLTransicionIJ(afnd, ep_indice, estado2) != 0){
                        /*Añadir los nombres de estado de forma alfabetica*/
                        if(strcmp(estado_lambda, AFNDNombreEstadoEn(afnd, estado2)) != 0)
                            estado_lambda = strcat(estado_lambda, AFNDNombreEstadoEn(afnd, estado2));
                    }
	    		}
	    	}

            if(strlen(estado_lambda) > 1){
                printf("Nueva transicion a %s desde %s con simbolo %s\n", estado_lambda, AFNDNombreEstadoEn(afd_final, estado1), AFNDSimboloEn(afnd, simbolo));
                for(i = 0; i < AFNDNumEstados(afd_final); i++){
                    if(AFNDNombreEstadoEn(afd_final, i) == NULL){
                        break;
                    }else if(strcmp(AFNDNombreEstadoEn(afd_final, i), estado_lambda)==0){
                        goto loop;
                    }
                }

                /*Loopear estados partidos para ver si alguno es FINAL*/
                for(qs = 0; qs < strlen(estado_lambda); qs += 2){
                    printf("Comprobamos si hay estados finales en %s\n", estado_lambda);

                    *(estado_partido+0) = estado_lambda[qs];  
                    *(estado_partido+1) = estado_lambda[qs+1];  
                    *(estado_partido+2) = '\0';

                    ep_indice = (int)estado_lambda[qs+1] - 48;
                    printf("\tEstado %s...\n", estado_partido);
                    /*Estudias las transiciones con ese simbolo desde ese estado*/
                    if(AFNDTipoEstadoEn(afnd, ep_indice) == FINAL){
                        if(pos_ini==estado1) {
                            AFNDInsertaEstado(afd_final, estado_lambda, INICIAL_Y_FINAL);
                            printf("\tCreamos estado INICIAL y FINAL %s...\n", estado_lambda);
                            goto loop;
                        }
                        AFNDInsertaEstado(afd_final, estado_lambda, FINAL);
                        printf("\tCreamos estado FINAL %s...\n", estado_lambda);
                        goto loop;
                    }
                }
                AFNDInsertaEstado(afd_final, estado_lambda, NORMAL);
                printf("\tCreamos estado NORMAL %s...\n", estado_lambda);
                    loop:
                AFNDInsertaTransicion(afd_final, AFNDNombreEstadoEn(afd_final, estado1), AFNDSimboloEn(afnd, simbolo), estado_lambda);
                printf("\tInsertamos transicion...\n");
            }
	    	free(estado_aux);
            free(estado_lambda);
    	}
    }
    free(estado_partido);
    return afd_final;
}
