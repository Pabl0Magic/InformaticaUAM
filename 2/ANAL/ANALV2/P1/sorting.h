/**
 *
 * Descripcion: Header file for sorting functions 
 *
 * Fichero: sorting.h
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#ifndef ORDENACION_H
#define ORDENACION_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/* type definitions */
typedef int (* pfunc_ordena)(int*, int, int);

/* Functions */

/**************************************************/
/* Input:                                         */
/* int* table: table to sort                      */
/* int ip: minor limit                            */
/* int iu: upper limit                            */
/* Output:                                        */
/* int: number of KC (basic operation)            */
/**************************************************/
int InsertSort(int* table, int ip, int iu);
int InsertSortInv(int* table, int ip, int iu);


#endif
