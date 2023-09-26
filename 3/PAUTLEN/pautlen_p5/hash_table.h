#ifndef HASH_TABLE_H
#define	HASH_TABLE_H


#include "alfa.h"

#define HASH_INI 5381
#define HASH_FACTOR 33


typedef struct {
  char key[MAX_LONG_ID+1];
  int category;
  int kind;
  int type;
  int size;
  int valor_entero;
  int num_local_var;
  int pos_local_var;
  int num_params;
  int pos_params;
} Info;

typedef Info **HASH_TABLE;

HASH_TABLE create_hash_table();
void free_hash_table(HASH_TABLE table);
int hash(HASH_TABLE table, char *key);

int getPos (HASH_TABLE t, char *x);
int search_symbol(HASH_TABLE t, char *key);

BOOL updateParam(HASH_TABLE t, char *key, int numero_param);

BOOL insert_symbol(HASH_TABLE t, char *key, int category, int kind, int type, int size, int num_local_var, int pos_local_var, int num_params, int pos_params);

int getCategory(HASH_TABLE t, char *key);
int getType(HASH_TABLE t, char *key);
int getKind(HASH_TABLE t, char *key);
int getSize(HASH_TABLE t, char *key);
int getNumParam(HASH_TABLE t, char *key);
int getIndexParam(HASH_TABLE t, char *key);
int getIndexVar(HASH_TABLE t, char *key);


#endif