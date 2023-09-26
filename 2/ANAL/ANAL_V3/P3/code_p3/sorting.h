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
void swap(int *a, int *b);
int BubbleSort(int* array, int ip, int iu);
int BubbleSortFlag(int* array, int ip, int iu);
int MergeSort(int* tabla, int ip, int iu);
int QuickSort(int* tabla, int ip, int iu);
int QuickSort_ntr (int* table, int ip, int iu);

#endif