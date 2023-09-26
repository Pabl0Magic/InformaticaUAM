#include "hash_table.h"

INFO* create_symbol_info(char* key, Kind kind, Type type, Category category, int size, int aux1, int aux2) {
    INFO* info;

    info = (INFO*)malloc (sizeof(INFO));
    if(!info) {
        return NULL;
    }

    info->key = strdup(key);
    if(!info->key) {
        free(info);
        return NULL;
    }

    info->kind = kind;
    info->type = type;
    info->category = category;
    info->size = size;
    info->aux1 = aux1;
    info->aux2 = aux2;

    return info;
}

void free_info(INFO* info) {
    if(info) {
        if(info->key) {
            free(info->key);
        }

        free(info);
    }
}

NODE *create_node(INFO* info) {
    NODE *node;

    if (!info) {
        printf("No info.\n");
        return NULL;
    }

    node = (NODE*)malloc(sizeof(NODE));
    if(!node) {
        return NULL;
    }

    node->info = info;
    node->next = NULL;

    return node;
}

void free_node(NODE* node) {
    if(node != NULL) {
        if(node->info) free_info(node->info);
        free(node);
    }
}

HASH_TABLE *create_hash_table(int size) {
    HASH_TABLE* table;

    if(size < 1) {
        printf("Size is less than 1");
        return NULL;
    }

    table = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));
    if(!table) {
        return NULL;
    }

    table->node = (NODE**)calloc(size, sizeof(NODE*));
    if(!table->node) {
        free(table);
        return NULL;
    }

    table->size = size; 

    return table;
}

void free_hash_table(HASH_TABLE* table) {
    int i;
    if (table != NULL){
        for(i = 0; i < table->size; i++) {
            free_node(table->node[i]);
        }
        free(table->node);
        free(table);
    }
}

int hash(HASH_TABLE* table, char* key) {
    unsigned long val = HASH_INI;
    unsigned char* aux;

    for(aux = (unsigned char *)key; *aux; aux++) {
        val = val*HASH_FACTOR + *aux;
    }

    return val % table->size;
}
 
INFO* search_symbol(HASH_TABLE* table, char* key) {
    int index;
    NODE* node = NULL;
    if (!table || !key) return NULL;
    index = hash(table, key);
    node = table->node[index];

    /* Search until there is a match or there are not more elements */
    while(node != NULL) {
        if(node->info == NULL) break;
        if (strcmp(node->info->key, key) == 0) return node->info;
        node = node->next;  
    }

    /* If it is NULL, then the element is not in the table, else it is and it is returned */
    if(!node || !node->info || strcmp(node->info->key, key) != 0) {
        return NULL;
    } else {
        return node->info;
    }

}

Status insert_symbol(HASH_TABLE* table, char* key, Kind kind, Type type, Category category, int size, int aux1, int aux2) {
    int index;
    INFO* info;
    NODE* node = NULL;

    if(!table) return ERROR;

    /*Element already inserted */
    if(search_symbol(table, key) != NULL) {
        return ERROR;
    }

    index = hash(table, key);
    
    info = create_symbol_info(key, kind, type, category, size, aux1, aux1);

    if (!info) {
        return ERROR;
    }

    node = create_node(info);
    if (!node) {
        free_info(info);
        return ERROR;
    }

    node->next = table->node[index];
    table->node[index] = node;

    return OK;
}

void delete_symbol(HASH_TABLE* table, char* key) {
    int val;
    NODE* next;
    NODE* last;
    NODE* aux;

    if(!table || !key) return;

    val = hash(table, key);
    next = table->node[val];

    while(next != NULL && next->info != NULL && strcmp(next->info->key, key) != 0) {
        last = next;
        next = next->next;
    }

    if(next != NULL && next->info != NULL && strcmp(next->info->key, key) == 0) {
        aux = next;
        free_info(next->info);
        free_node(next);

        /* First element of the table */
        if (aux == table->node[val]) {
            table->node[val] = aux->next;
        } /* Last element of the table */
        else if (aux->next == NULL) {
            last->next = NULL;
        } /* In the middle */
        else {
            last->next = aux->next;
        }

        /* If it does not get in, then the element is not in the table */
    }

}


