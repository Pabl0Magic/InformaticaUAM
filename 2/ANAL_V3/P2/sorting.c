/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

/***************************************************/
/* Function: bo Date: 17/10/2020                   */
/* Authors: Pablo Almarza                          */
/*                                                 */
/* Function that is in charge of                   */
/* counting the basic operations                   */
/*                                                 */
/* Input:                                          */
/* char comparison: the return of the comparison   */
/* int *count: the array that has the number of bo */
/* Output:                                         */
/* int: if the condition meets, return is 1, else 0*/
/***************************************************/
int bo(char comparison, int * count)
{
  *count += 1;
  return comparison;
}

void swap(int *a, int *b) {

  int temp;
  
  temp = *a;
  *a = *b;
  *b = temp;
  
}

/***************************************************/
/* Function: BubbleSort    Date: 20-09-2021        */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
  int i, j, count = 0;
  if(!array || ip > iu) {
    return ERR;
  }

  for(i = iu; i >= ip + 1; i--) {
    for(j = ip; j <= i - 1; j++) {
      if(bo(array[j] > array[j+1], &count)) {
        swap(&array[j], &array[j+1]);
      }
    } 
  }
  
  return count;
}

int BubbleSortFlag(int* array, int ip, int iu) {
  int i, j, flag, count = 0;
  if(!array || ip > iu) {
    return ERR;
  }

  flag = 1;
  i = iu;

  while(flag == 1 && i >= ip + 1) {
    flag = 0;
    for (j = ip; j <= i - 1; j++) {
      count++;
      if(array[j] > array[j+1]) {
        swap(&array[j], &array[j+1]);
        flag = 1;
      }
    }
    i--;
  }

  return count;
}

int merge(int* tabla, int ip, int iu, int medio) {
  int i, j, k, count = 0, lowValue = medio - ip + 1, upValue = iu - medio;
  int *lowerTab, *upperTab;
  
  lowerTab = (int*) malloc(lowValue * sizeof(int));
  
  if(!lowerTab) return ERR;
  
  upperTab = (int*) malloc(upValue * sizeof(int));
  
  if(!upperTab) {
    free(lowerTab); 
    return ERR;
  }
  
  for (i = 0; i < lowValue; i++) {
    lowerTab[i] = tabla[ip + i];
  }

  for (j = 0; j < upValue; j++) {
    upperTab[j] = tabla[medio + 1 + j];
  }

  i = 0;
  j = 0;
  k = ip;

  /*Perform the key comparison, raise the count by one, and merge the table */
  while (i < lowValue && j < upValue) {
    count++;
    if (lowerTab[i] <= upperTab[j]) {
      tabla[k] = lowerTab[i];
      i++;
    } else {
      tabla[k] = upperTab[j];
      j++;
    }

    k++;
  }

  /* Copy the remaining elements of lowerTab[], if there are any */
  while (i < lowValue) {
    tabla[k] = lowerTab[i];
    i++;
    k++;
  }

  free(lowerTab);
  
  /* Copy the remaining elements of upperTab[], if there are any */
  while (j < upValue) {
    tabla[k] = upperTab[j];
    j++;
    k++;
  }

  free(upperTab);
  
  return count;
}

int MergeSort(int* tabla, int ip, int iu) {
  int medio = ip + (iu - ip) / 2, auxCount = 0, count = 0;

  if (!tabla || ip > iu) {
    return ERR;
  }

  if( ip == iu) {
    return OK;
  }

  auxCount = MergeSort(tabla, ip, medio);
  if (auxCount > 0) {
    count = auxCount;
  } else {
    count = 0;
  }

  auxCount = MergeSort(tabla, medio + 1, iu);
  if (auxCount > 0) {
    count += auxCount;
  } else {
    count += 0;
  }

  return count + merge(tabla, ip, iu, medio);
}



int median(int *tabla, int ip, int iu,int *pos) {
  if (!tabla || ip > iu || !pos) return ERR;

  *pos = ip;

  return 0;  
}

int split(int* tabla, int ip, int iu,int *pos) {
  int i, k, count;

  if (!tabla || ip > iu || ip < 0 || !pos) return ERR;

  count = median(tabla, ip, iu, pos);
  
  if((*pos) > iu || (*pos) < ip){
    return count;
  }

  k = tabla[*pos];
  swap(&tabla[ip], &tabla[*pos]);
  *pos = ip;

  for (i = ip + 1; i <= iu; i++) {
    count++;
    if (tabla[i] < k) {
      (*pos)++;
      swap(&tabla[i], &tabla[*pos]);
    }
  }

  swap(&tabla[ip], &tabla[*pos]);

  return count;
}

int QuickSort(int* tabla, int ip, int iu) {
  int pos;
  int count = 0;
  int auxCount;


  if(!tabla || ip > iu) return ERR;

  auxCount = split(tabla, ip, iu, &pos);
  if(auxCount == ERR) return ERR;
  count = auxCount;

  auxCount = QuickSort(tabla, pos+1, iu);
  if (auxCount > 0) {
    count += auxCount;
  } else {
    count += 0;
  }

  auxCount = QuickSort(tabla, ip, pos-1);
  if (auxCount > 0) {
    count += auxCount;
  } else {
    count += 0;
  }

  return count;
}

int QuickSort_ntr(int* table, int ip, int iu) {
  int pos = 1, count = 0;

  if (table == NULL || ip < 0 || iu < ip) {
    return ERR;
  }

  while (ip < iu) {

    count += split(table, ip, iu, &pos);
    if (count == ERR)return ERR;

    if(pos - ip < iu - pos) {
      QuickSort_ntr(table, ip, pos - 1);
      ip = pos + 1;
    } else {
      QuickSort_ntr(table, ip, iu);
      iu = pos - 1;
    }
  }

  return count;

}