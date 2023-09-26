#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_INI 5381
#define HASH_FACTOR 33



typedef enum {
    VARIABLE,
    PARAMETRO,
    FUNCION
} Kind;

typedef enum {
    BOOLEAN,
    INT
} Type;

typedef enum {
    ESCALAR,
    VECTOR
} Category;

typedef struct _INFO {
    char* key;
    Kind kind;
    Type type;
    Category category;
    int size;
    int aux1;   
    int aux2;
} INFO;

typedef struct _NODE {
    INFO *info;
    struct _NODE *next;
} NODE;

typedef struct _HASH_TABLE {
    int size;
    NODE **node;
} HASH_TABLE;

typedef enum {
    ERROR = 0,
    OK = 1
} Status;

/**
 * @brief Create a symbol info and generate all the information to 
 * include in the structure
 * 
 * @param key 
 * @param kind 
 * @param type 
 * @param category 
 * @param size 
 * @param aux1 
 * @param aux2 
 * @return INFO* 
 */
INFO* create_symbol_info(char* key, Kind kind, Type type, Category category, int size, int aux1, int aux2);

/**
 * @brief free the info structure
 * 
 * @param info 
 */
void free_info(INFO* info);

/**
 * @brief Create a node to be able to go through the hash table
 * 
 * @param info 
 * @return NODE 
 */
NODE *create_node(INFO* info);

/**
 * @brief Free the node structure
 * 
 * @param node 
 */
void free_node(NODE* node);

/**
 * @brief Create a hash table to start working
 * 
 * @param size 
 * @return HASH_TABLE 
 */
HASH_TABLE *create_hash_table(int size);

/**
 * @brief Free the hash table
 * 
 * @param table 
 */
void free_hash_table(HASH_TABLE* table);

/**
 * @brief Search in the hash table the key that
 * is passed by parameter
 * 
 * @param table 
 * @param key 
 * @return INFO* 
 */
INFO* search_symbol(HASH_TABLE* table, char* key);

/**
 * @brief Insert an element into the hash table
 * 
 * @param table 
 * @param key 
 * @param kind 
 * @param type 
 * @param category 
 * @param size 
 * @param aux1 
 * @param aux2 
 * @return Status 
 */
Status insert_symbol(HASH_TABLE* table, char* key, Kind kind, Type type, Category category, int size, int aux1, int aux2);

/**
 * @brief Delete a symbol of the hash table
 * 
 * @param table 
 * @param key 
 */
void delete_symbol(HASH_TABLE* table, char* key);

#endif