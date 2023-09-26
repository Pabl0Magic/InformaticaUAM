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

int BubbleSortFlag(int* array, int ip, int iu)
{
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


