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
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

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
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order)
{
	PDICT pdict=NULL;
  if(size < 1 || (order != SORTED && order != NOT_SORTED)) {
    return NULL;
  }
  
  pdict = (PDICT)malloc(sizeof(DICT));
  if(!pdict) {
    return NULL;
  }
  
  pdict->table = NULL;
  
  pdict->table = (int*)malloc(sizeof(int)*size);
  if(!pdict->table) {
    free_dictionary(pdict);
    return NULL;
  }

  pdict->size = size;
  pdict->n_data = 0;
  pdict->order = order;
  
  return pdict;
}

void free_dictionary(PDICT pdict)
{
	if(!pdict) return;

  if(pdict->table!=NULL) {
    free(pdict->table);
  }
  free(pdict);
}

int insert_dictionary(PDICT pdict, int key)
{
	int A, j = 0, count = 0;

  if(!pdict || pdict->size == pdict->n_data) return ERR;

  pdict->table[pdict->n_data] = key;
  
  if(pdict->order==SORTED && pdict->n_data > 0){
    A = pdict->table[pdict->n_data];
    j = pdict->n_data - 1;

    while (j >= 0 && pdict->table[j] > A){
      pdict->table[j+1] = pdict->table[j];
      j--;
      count++;
    }

    if(j >= 0){
      count++;
    }
    pdict->table[j+1] = A;
  }

  pdict->n_data++;
  return count;
}

int massive_insertion_dictionary (PDICT pdict, int *keys, int n_keys)
{
	int count = 0, i, aux;

	if(!pdict || !keys || n_keys<1 || (pdict->size - pdict->n_data) < n_keys) return ERR;
  
  for(i = 0 ; i < n_keys ; i++){
    if((aux = insert_dictionary(pdict, keys[i])) == ERR) {
      return ERR;
    }
    count += aux;
  }
  return count;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  int i;
	if(!pdict || !method || !ppos || key < 0) return ERR;

  i = method(pdict->table, 0, pdict->n_data-1, key, ppos);

  if (*ppos == NOT_FOUND) {
    return NOT_FOUND;
  } else {
    return i;
  }
}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
	int M, count = 0;
  if(!table || F > L || F < 0) return ERR;


  while(F <= L){  
    M = (L+F)/2;
    count++;
    if(table[M] == key){
      *ppos = M;
      return count;
    }
    else if(table[M] > key){
      L = M-1;
    }
    else{
      F = M+1;
    }
  }
  *ppos = NOT_FOUND;
    
  return count;
}

int lin_search(int *table,int F,int L,int key, int *ppos)
{
	int count = 0, i;
  
  if(!table || F > L || F < 0 || !ppos) return ERR;
  
  for(i=F ; i <= L ; i++){
    count++;
    if(table[i] == key){
      *ppos=i;
      return count;
    }
  }

  *ppos = NOT_FOUND;
  return count;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
	int count = 0, i;

  if(!table || F > L || F < 0 || !ppos) {
    return ERR;
  }

  for(i = F ; i <= L ; i++){
    count++;
    if(table[i] == key){
      if(i != F){
        swap(&table[i], &table[i-1]);
        i--;
      }
      
      *ppos=i;
      return count;
    }
  }

  *ppos=NOT_FOUND;
  return count;
}


