/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"
#include "sorting.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void swap_search(int *a, int *b)
{

  int temp;

  temp = *a;
  *a = *b;
  *b = temp;
}

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 0 to max-1 in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = 0.5+max/(max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order)
{
  PDICT pdict;
  if (size <= 0 || (order != NOT_SORTED && order != SORTED)) {
    return NULL;
  }

  pdict = (PDICT) malloc(sizeof(DICT));
  if (!pdict) return NULL;

  pdict->table = (int*) malloc (size * sizeof(int));
  if (!pdict->table) {
    free(pdict);
    return NULL;
  } 

  pdict->size = size;
  pdict->order = order;
  pdict->n_data = 0;
  return pdict;
}

void free_dictionary(PDICT pdict)
{
  if(pdict)
  {
    if(pdict->table) free(pdict->table);
    free(pdict);
  }
}

int insert_dictionary(PDICT pdict, int key)
{
  int i;
  #ifdef DEBUG
  int j;
  #endif
	if (!pdict) return ERR;
  
  pdict->table[pdict->n_data] = key;
  (pdict->n_data)++;

  if (pdict->order == SORTED) {
    i = InsertSort(pdict->table, 0, pdict->n_data - 1);
    
    #ifdef DEBUG
    printf("After insertion on an ordered dictionary: ");
    for (j=0; j < pdict->n_data; j++) {
      printf("%d ", pdict->table[j]);
    }
    printf("\n");
    #endif
    return i;
  }

  return 1;
}

int massive_insertion_dictionary (PDICT pdict, int *keys, int n_keys)
{	
  int i, count = 0;
  
  if (!pdict || !keys || n_keys <= 0) return ERR;
  
  for(i = 0; i < n_keys; i++) {
    #ifdef DEBUG
    printf("Inserting %d...\n", keys[i]);
    #endif
    count += insert_dictionary(pdict, keys[i]);
  }

  return count; 
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  if (!pdict) return ERR;
  
  if (method == bin_search && pdict->order == NOT_SORTED) {
    printf("You can't use the function \"bin_search\"\n");
    return ERR;
  }
  if(method == lin_auto_search && pdict->order == SORTED){
      pdict->order = NOT_SORTED;
  }
  return method(pdict->table, 0, pdict->n_data, key, ppos);
}

/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
  int count = 0;

  if (!table || F < 0 || F > L || !ppos) return ERR;
  #if DEBUG
  printf("start");
  #endif
  while (F < L) {
    *ppos = (F + L)/2;
    #if DEBUG
    printf("->%d(%d)", table[*ppos], *ppos);
    #endif
    count++;
    if (table[*ppos] == key) {
      return count;
    }
    else if (key < table[*ppos]) {
      L = *ppos - 1;
    }
    else {
      F = *ppos + 1;
    }
  }

  *ppos = NOT_FOUND;

  return NOT_FOUND;
}

int lin_search(int *table,int F,int L,int key, int *ppos)
{
  int i;

  if (!table || F < 0 || F > L || !ppos) return ERR;

  for (i = F; i < L; i++) {
    if (table[i] == key) {
      *ppos = i;
      return i - F + 1;
    }
  }

  *ppos = NOT_FOUND;
  
  return NOT_FOUND;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
	  int i;

  if (!table || F < 0 || F > L || !ppos) return ERR;

  for(i = F; i < L; i++){
    if (table[i] == key) {
      if (i == F) {
        *ppos = i;
        return 1;
      }
      swap_search(&table[i], &table[i - 1]);
      *ppos = i - 1;
      return i - F + 1;
    }
  }

  *ppos = NOT_FOUND;
  
  return NOT_FOUND;
}