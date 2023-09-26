  /**
 *
 * Description: Header files for sorting
 *
 * File: sorting.h
 * Author: Javier Sanz-Cruzado, Rocío Cañamares 
 * Version: 1.0
 * Data: 20-09-2019
 *
 */

#ifndef SORTING_H
#define SORTING_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/* type definitions */
typedef int (* pfunc_sort)(int*, int, int);

/* Functions */

int InsertSort(int* tabla, int ip, int iu);
int InsertSortInv(int* tabla, int ip, int iu);
int mergesort(int* table, int ip, int iu);
int merge(int* table, int ip, int iu, int imiddle);
int quicksort(int* table, int ip, int iu);



#endif
