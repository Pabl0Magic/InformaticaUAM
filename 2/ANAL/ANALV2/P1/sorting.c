/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Pablo Almarza & Miguel Arnaiz
 * Version: 1.0
 * Fecha: 17-10-2020
 *
 */


#include "sorting.h"

/***************************************************/
/* Function: bo Date: 17/10/2020                   */
/* Authors: Pablo Almarza & Miguel Arnaiz          */
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

/***************************************************/
/* Function: InsertSort    Date: 17/10/2020        */
/* The InsertSort algorithm to sort a generic	     */
/* int array from the minimum number to the maximum*/
/***************************************************/
int InsertSort(int* table, int ip, int iu)
{
  int i, j, k, count = 0;

  if (!table || ip < 0)
  {
    return ERR;
  }

  for (i = ip + 1; i <= iu; i++)
  {
    k = table[i];
    j = i-1;

    while (j >= ip && bo(table[j] > k, &count)){
      table[j+1] = table[j];
      j--;
    } 
    table[j+1] = k;
  }

  return count;
}

/***************************************************/
/* Function: InsertSortInv    Date: 17/10/2020     */
/* The InsertSort algorithm to sort a generic      */
/* int array from the maximum number to the minimum*/
/***************************************************/
int InsertSortInv(int* table, int ip, int iu)
{
  int i, j, k, count = 0;

  if (!table || ip < 0)
  {
    return ERR;
  }

  for (i = ip + 1; i <= iu; i++)
  {
    k = table[i];
    j = i-1;

    while (j >= ip && bo(table[j] < k, &count)){
      table[j+1] = table[j];
      j--;
    } 
    table[j+1] = k;
  }

  return count;
}


