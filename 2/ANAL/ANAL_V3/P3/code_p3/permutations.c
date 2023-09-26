/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include "stdlib.h"


/***************************************************/
/* Function: swap_perm Date: 17/10/2020            */
/* Authors: Pablo Almarza          */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int a: first number                             */
/* int a: second number                            */
/* Output:                                         */
/***************************************************/
void swap_perm (int *a, int *b) {

  int temp;
  
  temp = *a;
  *a = *b;
  *b = temp;
  
}

/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  int r;
  int range = RAND_MAX / (sup - inf + 1);
  int limit = range * (sup - inf + 1);

    do
    {
        r = rand();
    } while (r >= limit);

    return inf + (r / range);
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int i, *perm;

  perm = (int*) malloc(N * sizeof(perm[0]));
  if(perm == NULL) return NULL;

  for(i = 0; i < N; i++) perm[i] = i+1;

  for(i = 0; i < N; i++) swap_perm(&perm[i], &perm[random_num(i, N-1)]);

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int i, j, *perm, **perms;

  perms = (int**) malloc(n_perms * sizeof(int*));
  if (perms == NULL) {
    return NULL;
  }

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