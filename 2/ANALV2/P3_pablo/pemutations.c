 /**
 *
 * Description: Implementation of functions for permutation generation
 *
 * File: permutations.c
 * Author: Jorge González, Pablo Almarza
 * Version: 1.0
 * Data: 20-09-2019
 *
 */


#include "permutations.h"
#include <stdlib.h>
#include <time.h>

/*Private function*/

void swap_perm (int *a, int *b) {

  int temp;
  
  temp = *a;
  *a = *b;
  *b = temp;
  
}
/***************************************************/
/* Function: random_num Date: 20/09/2019           */
/* Authors: Jorge González & Pablo Almarza         */
/*                                                 */
/* Rutine that generates random numbers	  		   */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: inferior limit                         */
/* int sup: superior limit       	               */
/* Output:                                         */
/* int: random number	                           */
/***************************************************/

int random_num(int inf, int sup)
{
  return (int) ((double)(sup-inf+1) * ((double)rand() / (double)RAND_MAX) + inf);
}

/***************************************************/
/* Function: genera_perm Date: 20/09/2019          */
/* Authors: Jorge González & Pablo Almarza         */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                               	       */
/* int n: Number of permutation elements           */
/* Output:                                         */
/* int *: punter to an integer array that 		   */
/* contains the permutation            			   */
/* or NULL if error		                           */
/***************************************************/
int* generate_perm(int N)
{
  int i, *perm;

  perm = (int*) malloc(N * sizeof(int));
  if(!perm) return NULL;

  for(i = 0; i < N; i++) perm[i] = i;

  for(i = 0; i < N; i++) swap_perm(&perm[i], &perm[random_num(i, N-1)]);

  return perm;
}

/***************************************************/
/* Function: genera_permutaciones Date: 20/09/2019 */
/* Authors: Jorge González & Pablo Almarza         */
/*                                                 */
/* Funcion that generates n_perms random		   */ 
/* permutations of N elements                 	   */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements of each permutation   */
/* Output:                                         */
/* int**: Array of integer pointers that point 	   */
/* to each of the permutations 		               */
/* NULL if error          		                   */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int i, j, *perm, **perms;

  perms = (int**) malloc(n_perms * sizeof(int*));

  for(i = 0; i < n_perms; i++) 
  {
    /* Safe way to manage errors to prevent memory leaks */
    perm = generate_perm(N);
    if(!perm)
    {
      /* Optimized to avoid doing N checks*/
      for(j = 0; j < i; j++)
      {
        free(perms[j]);
      }
      free(perms);
      return NULL;
    }
    perms[i] = perm;
  }

  return perms;
}
/*
  InsertSort:
    B(N): O(N) (Sorted array)
    W(N): O(N²) (Reverse-sorted array)
    A(N): O(N²)
  
  QuickSort:
    B(N): O(N*log N) (Everytime list of half size)
    W(N): O(N²) (Pivot is the smallest or the largest everytime of the recursion)
    A(N): O(N*log N)
      
  MergeSort:
    B(N): O(N*log N) 
    W(N): O(N*log N)
    A(N): O(N*log N)

  BSearch:
    B(N): O(1) = 1
    W(N): O(log N)
    A(N): O(log N)
  
  LSearch:
    B(N): O(1) = 1
    W(N): O(N)
    A(N): O(N) 
*/