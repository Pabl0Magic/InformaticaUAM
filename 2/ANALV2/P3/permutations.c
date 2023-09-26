/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Pablo Almarza & Miguel Arnaiz
 * Version: 1.0
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdlib.h>

/***************************************************/
/* Function: random_num Date: 17/10/2020           */
/* Authors: Pablo Almarza & Miguel Arnaiz          */
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
  if (sup < inf){return ERR;}
  return (int) ((double)(sup-inf+1) * ((double)rand() / (double)RAND_MAX) + inf);
}

/***************************************************/
/* Function: swap_perm Date: 17/10/2020            */
/* Authors: Pablo Almarza & Miguel Arnaiz          */
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
/* Function: generate_perm Date: 17/10/2020        */
/* Authors: Pablo Almarza & Miguel Arnaiz          */
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

  if (N <= 0) {
    return NULL;
  }

  perm = (int*) malloc(N * sizeof(perm[0]));
  if(perm == NULL) return NULL;

  for(i = 0; i < N; i++) perm[i] = i+1;

  for(i = 0; i < N; i++) swap_perm(&perm[i], &perm[random_num(i, N-1)]);

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date: 17/10/2020*/
/* Authors: Pablo Almarza & Miguel Arnaiz          */
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

  if (n_perms<=0 || N<=0) {
    return NULL;
  }

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
