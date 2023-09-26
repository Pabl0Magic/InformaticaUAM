/**
 *
 * Descriptions: Declarations of the search functions and data
 *
 * File: search.h
 * Author: Pablo Almarza and Miguel Arnaiz
 * Date: 10-12-2020
 *
 */

#ifndef SEARCH_H_
#define SEARCH_H_

/* constantes */

#ifndef ERR
#define ERR -1
#define OK (!ERR)
#endif


#define NOT_FOUND -2
#define SORTED 1
#define NOT_SORTED 0


/* type definitions */
typedef struct dictionary {
  int size; /* size of the table */
  int n_data;  /* number of data in the table */ 
  char order;  /* sorted table (SORTED) or unsorted (NOT_SORTED) */ 
  int *table;  /* data table */
} DICT, *PDICT;

typedef int (* pfunc_search)(int*, int, int, int, int*);
typedef void (* pfunc_key_generator)(int*, int, int);

/* Dictionary ADT */
PDICT init_dictionary (int size, char order);
void free_dictionary(PDICT pdict);
int insert_dictionary(PDICT pdict, int key);
int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys);
int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method);




/* Search functions for the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos);
int lin_search(int *table,int F,int L,int key, int *ppos);
int lin_auto_search(int *table,int F,int L,int key, int *ppos);

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
void uniform_key_generator(int *keys, int n_keys, int max);
void potential_key_generator(int *keys, int n_keys, int max);



#endif

