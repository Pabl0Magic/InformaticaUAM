#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transforma.h"

/* Variables globales necesarias para crear el estado inicial */
ConjuntoEstados *estadosDeterminista = NULL, origen;
Estado *estudiados = NULL;

/*
 * Esta funcion que obtiene un array de cadenas con los nombres de los estados de un automata
 * 
 */
char **nombreEstados(AFND *afnd)
{
	int numEstados = 0	, i;
	char **nombre_estados = NULL;

	numEstados = AFNDNumEstados(afnd);
	nombre_estados = (char **)calloc(numEstados, sizeof(char *));

	for (i = 0; i < numEstados; i++)
	{
		nombre_estados[i] = (char *)calloc(MAX_NOMBRE, sizeof(char));
		strcpy(nombre_estados[i], AFNDNombreEstadoEn(afnd, i));
	}

	return nombre_estados;
}

/**
 * Esta funcion obtiene un array de estados a los que un estado transita 
 * dados el indice de un estado y el simbolo. Ademas, se puede obtener las transiciones
 * lambda si asi se quiere
 * 
 */
Estado *transiciones(AFND *afnd, int indEstadoOrigen, char *simbolo, int lambda)
{
	int i, n = 0, numEstados = 0, indSimbolo = 0, indEstadoDestino = 0;
	char **nombre_estados = NULL;
	Estado *transiciones = NULL;

	numEstados = AFNDNumEstados(afnd);
	nombre_estados = nombreEstados(afnd);

	if (lambda == 0)
	{
		indSimbolo = AFNDIndiceDeSimbolo(afnd, simbolo);
	}

	transiciones = (Estado *)calloc(numEstados, sizeof(Estado));

	for (i = 0; i < numEstados; i++)
	{
		indEstadoDestino = AFNDIndiceDeEstado(afnd, nombre_estados[i]);

		if (lambda == 0)
		{
			if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, indEstadoOrigen, indSimbolo, indEstadoDestino) == 1)
			{
				strcpy(transiciones[n].nombre, nombre_estados[i]);
				transiciones[n].indice = indEstadoDestino;
				n += 1;
			}
		}
		else
		{
			if (AFNDCierreLTransicionIJ(afnd, indEstadoOrigen, indEstadoDestino) == 1 && strcmp(AFNDNombreEstadoEn(afnd, indEstadoOrigen), AFNDNombreEstadoEn(afnd, indEstadoDestino)) != 0)
			{
				strcpy(transiciones[n].nombre, nombre_estados[i]);
				transiciones[n].indice = indEstadoDestino;
				n += 1;
			}
		}
	}

	for (i = 0; i < numEstados; i++)
	{
		free(nombre_estados[i]);
	}

	free(nombre_estados);

	if (n == 0) {
		free(transiciones);
		return NULL;
	}


	return transiciones;
}

/**
 * @brief Crear matriz de transiciones
 *
 */
Estado ***crearMatrizAFND(AFND *afnd, int filas, int columnas)
{
	int i=0, j=0;
	Estado *estado = NULL;
	Estado ***matrizAFND = NULL;

	matrizAFND = (Estado ***)calloc(filas, sizeof(Estado **));

	for (i = 0; i < filas; i++)
	{
		matrizAFND[i] = (Estado **)calloc(columnas, sizeof(Estado *));
	}

	for (i = 0; i < filas; i++)
	{
		for (j = 0; j < columnas - 1; j++)
		{
			estado = transiciones(afnd, i, AFNDSimboloEn(afnd, j), 0);
			matrizAFND[i][j] = estado;
		}

		estado = transiciones(afnd, i, AFNDSimboloEn(afnd, j), 1);
		matrizAFND[i][j] = estado;
	}

	return matrizAFND;
}

/**
 * @brief Esta funcion obtiene las transiciones del automata desde un estado y ve el tipo
 * 
 */
void transicionesPorCasilla(AFND *afnd, int x, int y, int filas, ConjuntoEstados *conjuntoEstados, Estado ***matrizAFND)
{
	int i;

	for (i = 0; i < filas; i++)
	{
		if (strlen(matrizAFND[x][y][i].nombre) > 0)
		{
			strcat(conjuntoEstados->nombre, matrizAFND[x][y][i].nombre);
			conjuntoEstados->indice[conjuntoEstados->numIndices] = matrizAFND[x][y][i].indice;
			conjuntoEstados->numIndices++;

			if (AFNDTipoEstadoEn(afnd, matrizAFND[x][y][i].indice) == FINAL)
			{
				conjuntoEstados->tipo = FINAL;
			}
		}
	}
}

/**
 * @brief Esta funcion obtiene las transiciones lambda de un estado y comprueba su tipo
 * 
 *
 */
void buscarTransicionesLambda(AFND *afnd, int i, int j, int k, int filas, int columnas, ConjuntoEstados *conjuntoEstados, Estado ***matrizAFND)
{
	int a, b, flag;

	for (a = 0; a < filas; a++)
	{
		if (strlen(matrizAFND[(matrizAFND[i][j][k].indice)][columnas - 1][a].nombre) > 0)
		{
			flag = 0;

			/*Comprobar si se ha transitado ya al estado mediante los indices*/
			for (b = 0; b < conjuntoEstados->numIndices; b++)
			{
				if (conjuntoEstados->indice[b] == matrizAFND[(matrizAFND[i][j][k].indice)][columnas - 1][a].indice)
				{
					flag = 1;
				}
			}

			if (flag != 1)
			{
				strcat(conjuntoEstados->nombre, matrizAFND[(matrizAFND[i][j][k].indice)][columnas - 1][a].nombre);
				conjuntoEstados->indice[origen.numIndices] = matrizAFND[(matrizAFND[i][j][k].indice)][columnas - 1][a].indice;
				conjuntoEstados->numIndices++;

				if (AFNDTipoEstadoEn(afnd, matrizAFND[(matrizAFND[i][j][k].indice)][columnas - 1][a].indice) == FINAL)
				{
					conjuntoEstados->tipo = FINAL;
				}
			}
		}
	}
}

/**
 * @brief Esta funcion obtiene las transiciones de un estado y comprueba su tipo
 * 
 */
void buscarTransiciones(AFND *afnd, int i, int j, int filas, int columnas, ConjuntoEstados *conjuntoEstados, Estado ***matrizAFND)
{
	int k, l, flag;

	for (k = 0; k < filas; k++)
	{
		if (strlen(matrizAFND[i][j][k].nombre) > 0)
		{
			flag = 0;

			/*Comprobar si se ha transitado ya al estado mediante los indices*/
			for (l = 0; l < conjuntoEstados->numIndices; l++)
			{
				if (conjuntoEstados->indice[l] == matrizAFND[i][j][k].indice)
				{
					flag = 1;
				}
			}

			if (flag == 0)
			{
				strcat(conjuntoEstados->nombre, matrizAFND[i][j][k].nombre);
				conjuntoEstados->indice[conjuntoEstados->numIndices] = matrizAFND[i][j][k].indice;
				conjuntoEstados->numIndices++;

				if (AFNDTipoEstadoEn(afnd, matrizAFND[i][j][k].indice) == FINAL)
				{
					conjuntoEstados->tipo = FINAL;
				}
			}

			/*Se buscan transiciones lambda*/
			if (matrizAFND[(matrizAFND[i][j][k].indice)][columnas - 1] != NULL)
			{
				buscarTransicionesLambda(afnd, i, j, k, filas, columnas, conjuntoEstados, matrizAFND);
			}
		}
	}
}

void transicionesLambdaOrigen(AFND *afnd, Estado ***matrizAFND, int filas, int columnas)
{
	int k;

	if (matrizAFND[0][columnas - 1] != NULL)
	{ /*columnas -1 porque lambda es la ultima columna */
		for (k = 0; k < filas; k++)
		{
			if (strlen(matrizAFND[0][columnas - 1][k].nombre) > 0)
			{
				strcat(origen.nombre, matrizAFND[0][columnas - 1][k].nombre);
				origen.indice[origen.numIndices] = matrizAFND[0][columnas - 1][k].indice;
				origen.numIndices++;
				strcat(estudiados[0].nombre, origen.nombre);

				if (AFNDTipoEstadoEn(afnd, matrizAFND[0][columnas - 1][k].indice) == FINAL)
				{
					origen.tipo = INICIAL_Y_FINAL;
				}

				estadosDeterminista[0] = origen;
			}
		}
	}
}

void crearEstadoInicial(AFND *afnd, Estado ***matrizAFND, int filas, int columnas)
{

	estadosDeterminista = (ConjuntoEstados *)calloc(1, sizeof(ConjuntoEstados));
	estudiados = (Estado *)calloc(1, sizeof(Estado));

	strcpy(estadosDeterminista[0].nombre, AFNDNombreEstadoEn(afnd, AFNDIndiceEstadoInicial(afnd)));
	strcpy(estudiados[0].nombre, AFNDNombreEstadoEn(afnd, AFNDIndiceEstadoInicial(afnd)));
	estadosDeterminista[0].tipo = INICIAL;

	origen.numIndices = 0;
	origen.tipo = INICIAL;

	/* Establecer estado origen */
	strcpy(origen.nombre, estadosDeterminista[0].nombre);
	origen.indice[origen.numIndices] = AFNDIndiceEstadoInicial(afnd);
	origen.numIndices++;

	transicionesLambdaOrigen(afnd, matrizAFND, filas, columnas);
}

AFND *AFNDTransforma(AFND *afnd)
{
	int i = 0, j = 0, k = 0, flag = 0, filas = 0, columnas_simb = 0, numEstados = 0, numEstudiados = 0, filasDeterminista = 1, loop =0;
	int simbolo = 0, fin = 0, a = 0, b = 0, c = 0, d = 0, e1 = 0;
	AFND *afd = NULL;
	ConjuntoEstados aux;
	Casilla casilla, **matrizTransiciones = NULL;
	Estado ***matrizAFND = NULL;

	filas = AFNDNumEstados(afnd);
	columnas_simb = AFNDNumSimbolos(afnd) + 1; /* +1 por la columna del simbolo lambda*/

	matrizAFND = crearMatrizAFND(afnd, filas, columnas_simb);

	matrizTransiciones = (Casilla **)calloc(1, sizeof(Casilla *));
	matrizTransiciones[0] = (Casilla *)calloc(columnas_simb, sizeof(Casilla));

	crearEstadoInicial(afnd, matrizAFND, filas, columnas_simb);

	numEstados++;
	estadosDeterminista = (ConjuntoEstados *)realloc(estadosDeterminista, (numEstados + 1) * sizeof(ConjuntoEstados));
	numEstudiados++;
	estudiados = (Estado *)realloc(estudiados, (numEstudiados + 1) * sizeof(Estado));

	/* Hacer la primera fila. Comprobar todas sus transiciones por simbolo */
	for (i = 0; i < columnas_simb - 1; i++)
	{
		strcpy(aux.nombre, "");
		aux.numIndices = 0;
		aux.tipo = NORMAL;

		for (j = 0; j < origen.numIndices; j++)
		{
			/* Si matriz != NULL => hay transicion */
			if (matrizAFND[origen.indice[j]][i] != NULL)
			{
				transicionesPorCasilla(afnd, origen.indice[j], i, AFNDNumEstados(afnd), &aux, matrizAFND);
			}
		}

		/* Añadir nuevo estado a la matriz de transiciones y al automata */
		casilla.siguiente = aux;
		casilla.estudiado = 0;
		matrizTransiciones[0][i] = casilla;

		for (k = 0; k < numEstados; k++)
		{
			if (strcmp(casilla.siguiente.nombre, estadosDeterminista[k].nombre) == 0)
			{
				flag = 1;
				break;
			}
		}

		if (flag != 1)
		{ /* Significa que el estado no existe */
			estadosDeterminista[numEstados] = aux;
			numEstados++;
			estadosDeterminista = (ConjuntoEstados *)realloc(estadosDeterminista, (numEstados + 1) * sizeof(ConjuntoEstados));
		}
		flag = 0;
	}

	/* Marcar estudiadas */
	for (i = 0; i < filasDeterminista; i++)
	{
		for (j = 0; j < columnas_simb - 1; j++)
		{
			if (strcmp(matrizTransiciones[i][j].siguiente.nombre, origen.nombre) == 0)
			{
				matrizTransiciones[i][j].estudiado = 1;
			}
		}
	}
	
	/* Iterar para ver todas las transiciones pr simbolo del resto de casillas */
	fin = 1;
	printf("%d\n", filasDeterminista);
	while (fin == 1)
	{
		fin = 0;
		for(i = 0; i < filasDeterminista; i++){
        	for(j = 0; j < columnas_simb - 1; j++){
				if(matrizTransiciones[i][j].estudiado == 0){
					fin = 1;
					filasDeterminista++;
					matrizTransiciones =realloc(matrizTransiciones, filasDeterminista*sizeof(Casilla*));
					matrizTransiciones[filasDeterminista-1] = (Casilla*)malloc(columnas_simb*sizeof(Casilla));
					origen = matrizTransiciones[i][j].siguiente; 
					strcpy(estudiados[numEstudiados].nombre, origen.nombre);
					numEstudiados++;
					estudiados = (Estado *)realloc(estudiados, (numEstudiados+1)*sizeof(Estado));

					for(simbolo = 0; simbolo < columnas_simb - 1; simbolo++) {
						strcpy(aux.nombre, "");
						aux.numIndices = 0;
						aux.tipo = NORMAL;
						
						/*Recorre cada estado del conjunto de estados*/
						for (e1 = 0; e1 < origen.numIndices; e1++) {
							if(matrizAFND[origen.indice[e1]][simbolo] != NULL){
								buscarTransiciones(afnd, origen.indice[e1], simbolo, filas, columnas_simb, &aux, matrizAFND);
							}
						}

						/*Si no hay transicion, la casilla se llamara vacio (conjunto vacio)*/
                    	if (strlen(aux.nombre) < 1){
                        strcpy(aux.nombre, "vacio");
						}
						
						/* Añadir nuevo estado(si no estaba ya) */
						casilla.siguiente = aux;

						if(strcmp(casilla.siguiente.nombre, "vacio") == 0) {
							casilla.estudiado = 1;
						} else {
							casilla.estudiado = 0;
						}

						matrizTransiciones[filasDeterminista - 1][simbolo] = casilla;
						
						for(a = 0; a < numEstados; a++) {
							if(strcmp(casilla.siguiente.nombre, estadosDeterminista[a].nombre) == 0 || strcmp(casilla.siguiente.nombre, "vacio") == 0) {
								flag = 1;
								break;
							}
						}

						if (flag != 1)
						{ /* Significa que el estado no existe */
							estadosDeterminista[numEstados] = aux;
							numEstados++;
							estadosDeterminista = (ConjuntoEstados *)realloc(estadosDeterminista, (numEstados + 1) * sizeof(ConjuntoEstados));
						}
						flag = 0;

						for (b = 0; b < filasDeterminista; b++)
						{
							for (c = 0; c < simbolo + 1; c++)
							{
								for (d = 0; d < numEstudiados; d++)
								{
									
									printf("%d----%s.....%s\n", filasDeterminista, matrizTransiciones[b][c].siguiente.nombre, origen.nombre);
									if (strcmp(matrizTransiciones[b][c].siguiente.nombre, estudiados[d].nombre) == 0)
									{
										matrizTransiciones[b][c].estudiado = 1;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	/* Rellenar y completar el nuevo automata */
	afd = AFNDNuevo("afd", numEstados, columnas_simb - 1);
	printf("%d____%d\n\n", numEstados, filasDeterminista);
	
	for (i = 0; i < columnas_simb - 1; i++) {
    	AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));
  	}
	
	for (i = 0; i < numEstados; i++) {
		AFNDInsertaEstado(afd, estadosDeterminista[i].nombre, estadosDeterminista[i].tipo);
	}

	for (i = 0; i < filasDeterminista; i++) {
  		for (j = 0; j < columnas_simb - 1; j++){
  			if (strcmp(matrizTransiciones[i][j].siguiente.nombre, "vacio") != 0){
  				AFNDInsertaTransicion(afd, estadosDeterminista[i].nombre, AFNDSimboloEn(afnd, j), matrizTransiciones[i][j].siguiente.nombre);
  			}
  		}
  	}

	/* Liberar toda la memoria */
	free(estadosDeterminista);
	free(estudiados);

	for (i = 0; i < filas; i++) {
    	for (j = 0; j < columnas_simb; j++) {
      		free(matrizAFND[i][j]);
    	}

		free(matrizAFND[i]);
	}

	free(matrizAFND);

	for (i = 0; i < filasDeterminista; i++) {
		free(matrizTransiciones[i]);
	}

	free(matrizTransiciones);

	return afd;
}
