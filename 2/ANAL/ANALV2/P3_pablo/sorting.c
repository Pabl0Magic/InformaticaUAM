/**
 *
 * Description: Implementation of sorting functions
 *
 * File: sorting.c
 * Author: Jorge González, Pablo Almarza
 * Version: 1.0
 * Data: 20-09-2019
 *
 */
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
/* Function: OB             Date: 13/11/2019       */
/* Function used to do the Basic Operation while   */
/* properly rising the count up. Returns a bool.   */
/***************************************************/
int bo(char comparison, int * count)
{
  *count += 1;
  return comparison;
}
/***************************************************/
/* Function: InsertSort    Date: 1/10/2019         */
/* The InsertSort algorithm to sort a generic      */
/* int array from the minimum number to the maximum*/
/***************************************************/
int InsertSort(int *list, int ip, int iu)
{
  int i, j, k, count = 0;

  if (!list || ip < 0)
  {
    return ERR;
  }

  for (i = ip + 1; i <= iu; i++)
  {
    k = list[i];
    j = i-1;

    while (j >= ip && bo(list[j] > k, &count)){
      list[j+1] = list[j];
      j--;
    } 
    list[j+1] = k;
  }

  return count;
}

/***************************************************/
/* Function: InsertSortInv    Date: 7/10/2019      */
/* The InsertSort algorithm to sort a generic      */
/* int array from the maximum number to the minimum*/
/***************************************************/
int InsertSortInv(int *list, int ip, int iu)
{
  int i, j, k, count = 0;

  if (!list || ip < 0)
  {
    return ERR;
  }

  for (i = ip + 1; i <= iu; i++)
  {
    k = list[i];
    j = i-1;

    while (j >= ip && bo(list[j] < k, &count)){
      list[j+1] = list[j];
      j--;
    } 
    list[j+1] = k;
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
  /* Perform the key comparison, raise the count by one, and merge the table */
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
/* Function: median_stat    Date: 6/11/2019        */
/* Set's pos to the average between the first,     */
/* the last and the element at the middle          */
/***************************************************/
int median_stat(int *table, int ip, int iu, int *pos) {
  
  int i;

  i = (ip+iu)/2;
  *pos = ip;

  if (!table || ip > iu ) {
    return ERR;
  }
  if (table[iu] > table[ip]) {
    if(table[i] > table[iu]) {
      /* i > iu > ip */
      *pos = iu;
      return 3;
    }
    /* table[i] < table[iu], table[iu] is max */
    else if(table[i] > table[ip]){
      /* iu > i > ip */
      *pos = i;
      return 3;
    }
    else {
      /* iu > ip > i */
      *pos = ip;
      return 3;
    }
  }
  else { /*table[iu] < table[ip] */
    if (table[i] > table[ip]){
        /* i > ip > ip */
        *pos = ip;
        return 3;
    }
    /* table[i] < table[ip], table[ip] is max */
    else if(table[i] > table[iu]) {
      /* ip > i > iu */
      *pos = i;
      return 3;
    }
    else {
      /* ip > iu > i */
      *pos = iu;
      return 3;
    }
  }
/* 
  if (table[ip] > table[iu] && table[ip] > table[i]) {
    if (table[iu] > table[i]) {
      *pos = iu;
      return count;
    } else {
      *pos = i;
      return count;
      }
  }

  if (table[iu] > table[ip] && table[iu > table[i]]) {
    if (table[ip] > table[i]) {
      *pos = ip;
      return count;
    = (ip+iu)/2;      *pos = i;
      return count;
    }
  }
  
  if (table[i] > table[ip] && table[i] > table[iu]) {
    if (table[ip] > table[iu]) {
      *pos = ip;
      return count;
    } else {
      return count;
    }
  }



  return ERR;*/
}

/***************************************************/
/* Function: median_avg     Date: 6/11/2019        */
/* Set's pos to the average between the first      */
/* and the last element                            */
/***************************************************/
int median_avg(int *table, int ip, int iu, int *pos) {
  
  int i=0;

  if (!table || ip > iu) {
    return ERR;
  }

  i = (ip+iu)/2;

  *pos = i;

  return 0;
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
/* Function: split_avg          Date: 13/11/2019       */
/* QuickSort core logic. Returns the count of BOs  */
/* and is the function to recursively call         */
/* replace the first function called with median,  */
/* median_avg or median_stat to use different pivot*/
/* choosing methods                                */
/***************************************************/
int split_stat(int* table, int ip, int iu, int* pos) {
  
  int i, k, count;

  if (!table || ip > iu || ip < 0 || !pos) return ERR;

  count = median_stat(table, ip, iu, pos);
  
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
/* Function: split_avg          Date: 13/11/2019       */
/* QuickSort core logic. Returns the count of BOs  */
/* and is the function to recursively call         */
/* replace the first function called with median,  */
/* median_avg or median_stat to use different pivot*/
/* choosing methods                                */
/***************************************************/
int split_avg(int* table, int ip, int iu, int* pos) {
  
  int i, k, count;

  if (!table || ip > iu || ip < 0 || !pos) return ERR;

  count = median_avg(table, ip, iu, pos);
  
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