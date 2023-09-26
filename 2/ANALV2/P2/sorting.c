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

#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"


void swap(int *a, int *b)
{

  int temp;

  temp = *a;
  *a = *b;
  *b = temp;
}

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

  if(table==NULL || ip<0 || ip>iu){
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

  if(table==NULL || ip < 0 || ip>iu){
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



/***************************************************/
/* Function: merge          Date: 8/11/2019        */
/* Merge or combine method to recursively call     */
/* to sort the table                               */
/***************************************************/
int merge(int *table, int ip, int iu, int imiddle)
{
  int i, j, k, count = 0, lowValue = imiddle - ip + 1, upValue = iu - imiddle, *lowerTab, *upperTab;
  
  lowerTab = (int*) malloc(lowValue * sizeof(int));
  
  if(!lowerTab) return ERR;
  
  upperTab = (int*) malloc(upValue * sizeof(int));
  
  if(!upperTab) 
  {
    free(lowerTab); 
    return ERR;
  }
  
  for (i = 0; i < lowValue; i++)
    lowerTab[i] = table[ip + i];
  
  for (j = 0; j < upValue; j++)
    upperTab[j] = table[imiddle + 1 + j];

  i = j = 0;
  k = ip;
  /*Perform the key comparison, raise the count by one, and merge the table */
  while (i < lowValue && j < upValue)
  {
    count++;
    if (lowerTab[i] <= upperTab[j])
    {
      table[k] = lowerTab[i];
      i++;
    }
    else
    {
      table[k] = upperTab[j];
      j++;
    }
    k++;
  }

  /* Copy the remaining elements of lowerTab[], if there are any */
  while (i < lowValue)
  {
    table[k] = lowerTab[i];
    i++;
    k++;
  }
  free(lowerTab);
  /* Copy the remaining elements of upperTab[], if there are any */
  while (j < upValue)
  {
    table[k] = upperTab[j];
    j++;
    k++;
  }
  free(upperTab);
  return count;
}

/***************************************************/
/* Function: mergesort      Date:  8/11/2019       */
/* Function to call to when you want to do the     */
/* MergeSort algorithm over an int array.          */
/***************************************************/
int mergesort(int *table, int ip, int iu)
{
  int m = ip + (iu - ip) / 2, ret = 0, obs = 0;

    if (!table || ip >= iu)
    {
      return ERR;
    }
  ret = mergesort(table, ip, m);
  obs = ret > 0 ? ret : 0;
  ret = mergesort(table, m + 1, iu);
  obs += ret > 0 ? ret : 0;
  return obs + merge(table, ip, iu, m);
}

/***************************************************/
/* Function: median         Date: 6/11/2019        */
/* Sets pos to the initial value of the array (ip) */
/***************************************************/
int median(int *table, int ip, int iu, int *pos) {

  if (!table || ip > iu || !pos) return ERR;

  *pos = ip;

  return 0;  
}

/***************************************************/
/* Function: split          Date: 13/11/2019       */
/* QuickSort core logic. Returns the count of BOs  */
/* and is the function to recursively call         */
/* replace the first function called with median,  */
/* median_avg or median_stat to use different pivot*/
/* choosing methods                                */
/***************************************************/
int split(int* table, int ip, int iu, int* pos) {
  
  int i, k, count;

  if (!table || ip > iu || ip < 0 || !pos) return ERR;

  count = median(table, ip, iu, pos);
  
  if((*pos) > iu || (*pos) < ip){
    return count;
  }

  k = table[*pos];
  swap(&table[ip], &table[*pos]);
  *pos = ip;

  for (i = ip + 1; i <= iu; i++) {
    count++;
    if (table[i] < k) {
      (*pos)++;
      swap(&table[i], &table[*pos]);
    }
  }

  swap(&table[ip], &table[*pos]);

  return count;
}

/***************************************************/
/* Function: QuickSort    Date: 13/11/2019         */
/* Sorts a generic int array given the first       */
/* position and the last one. Returns the count of */
/* BOs and uses the QuickSort algorithm            */
/***************************************************/
int quicksort(int* table, int ip, int iu){

  int pos;
  int count = 0;
  int auxCount;


  if(!table || ip > iu) {
    return ERR;
  }

  if (ip == iu) {
    return OK;
  }
  else {
    auxCount = split(table, ip, iu, &pos);
    if(auxCount == ERR) return ERR;
    count = auxCount;

    auxCount = quicksort(table, pos+1, iu);
    count += auxCount > 0 ? auxCount : 0;
    auxCount = quicksort(table, ip, pos-1);
    count += auxCount > 0 ? auxCount : 0;
  }

  return count;
}

int quicksort_ntr (int* table, int ip, int iu){
  int pos = 1, count = 1;

  if (table == NULL || ip < 0 || iu < ip) {
    return ERR;
  }

  while (ip < iu) {

    count += split(table, ip, iu, &pos);
    if (count == ERR)return ERR;

    if(pos - ip < iu - pos) {
      quicksort_ntr(table, ip, pos - 1);
      ip = pos + 1;
    } else {
      quicksort_ntr(table, ip, iu);
      iu = pos - 1;
    }
  }

  return count;

}