#include "hash_table.h"

HASH_TABLE create_hash_table(){
    int i;
    HASH_TABLE table=(HASH_TABLE)malloc(SIZE*sizeof(table[0]));

    if(!table)
        return table;
    for(i=0; i<SIZE; i++)
        table[i]=NULL;

    return table;
}

void free_hash_table(HASH_TABLE table){
    int i;
    
    for(i=0; i<SIZE; i++){
        if(table[i] != NULL)
          free(table[i]);
    }

    free(table);
    table=NULL;
}

int hash(HASH_TABLE table, char *key){
   unsigned long val = HASH_INI;
   unsigned char* aux;

   for(aux = (unsigned char *)key; *aux; aux++) {
      val = val*HASH_FACTOR + *aux;
   }

   return val % SIZE;
}

int getindex(HASH_TABLE table, char *key){
   int ini, i, aux;

   ini=hash(table, key);

   for (i=0; i<SIZE; i++) {
      aux=(ini+i)%SIZE;
      if (table[aux] == NULL)
         return aux;

      if (!strcmp(table[aux]->key, key))
         return aux;
   }

   return ini;
}

int search_symbol(HASH_TABLE table, char *key){
   int index=getindex(table, key);

   if (table[index]==NULL)
      return 0;

   else
      return(!strcmp(table[index]->key, key));
}

BOOL updateParam(HASH_TABLE table, char *key, int numero_param){
  int index;

  if (search_symbol(table, key)){
    index=getindex(table, key);
    table[index]->num_params=numero_param;

    return TRUE;
  }

  return FALSE;
}

BOOL insert_symbol(HASH_TABLE table, char *key, int category, int kind, int type, int size, int num_local_var, int pos_local_var, int num_params, int pos_params){
   int index;

   if (!search_symbol(table, key)) {
       index=getindex(table, key);
       if (table[index]==NULL ) {
          table[index]=(Info*)malloc(sizeof(table[index][0]));
          strcpy(table[index]->key,key);
          table[index]->category=category;
          table[index]->kind=kind;
          table[index]->type=type;
          table[index]->size=size;
          table[index]->num_local_var=num_local_var;
          table[index]->pos_local_var=pos_local_var;
          table[index]->num_params=num_params;
          table[index]->pos_params=pos_params;
          return TRUE;
       } else {
          return FALSE;
       }
   }

   return FALSE;
}

int getCategory(HASH_TABLE table, char *key){
   return  table[getindex(table, key)]->category;
}

int getType(HASH_TABLE table, char *key){
   return  table[getindex(table, key)]->type;
}

int getKind(HASH_TABLE table, char *key){
   return  table[getindex(table, key)]->kind;
}

int getSize(HASH_TABLE table, char *key){
   return  table[getindex(table, key)]->size;
}

int getNumParam(HASH_TABLE table, char *key){
   return  table[getindex(table, key)]->num_params;
}

int getIndexParam(HASH_TABLE table, char *key){
   return  table[getindex(table, key)]->pos_params;
}

int getIndexVar(HASH_TABLE table, char *key){
   return  table[getindex(table, key)]->pos_local_var;
}