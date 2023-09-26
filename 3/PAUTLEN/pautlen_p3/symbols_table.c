#include "symbols_table.h"


#define TOTAL_SIZE_GLOBAL 50
#define TOTAL_SIZE_LOCAL 50

HASH_TABLE *global_table = NULL;
HASH_TABLE *local_table = NULL;

Status declare(char *id,  INFO* desc_id) {
    if (local_table == NULL) {
       return declare_global(id, desc_id);
    } else {
       return declare_local(id, desc_id);
    }
}

Status declare_global(char *id, INFO* desc_id){

    if(!id) return ERROR;

    if (global_table == NULL) {
        global_table = create_hash_table(TOTAL_SIZE_GLOBAL);
        if(!global_table) {
            return ERROR;
        }
    }

    if(search_symbol(global_table, id) == NULL) {
        if(insert_symbol(global_table, id, desc_id->kind, desc_id->type, desc_id->category, desc_id->size, desc_id->aux1, desc_id->aux2) == ERROR) {
            return ERROR;
        }
    }else{
        return ERROR;
    }
    
    return OK;
}

Status declare_local(char *id, INFO* desc_id){
    if(!id || !desc_id) return ERROR;

    if (local_table == NULL) {
        local_table = create_hash_table(TOTAL_SIZE_LOCAL);
        if(!global_table) {
            return ERROR;
        }
    }

    if(search_symbol(local_table, id) == NULL) {
        if(insert_symbol(local_table, id, desc_id->kind, desc_id->type, desc_id->category, desc_id->size, desc_id->aux1, desc_id->aux2) == ERROR) {
            return ERROR;
        }
    }else{
        return ERROR;
    }
    
    return OK;
}

INFO* global_search(char *id){

    if(!global_table || !id) {
        return NULL;
    }

    return search_symbol(global_table, id);
    
}

INFO* local_search(char *id){
    if(!id) return ERROR;

    if(local_table != NULL){
        if(search_symbol(local_table, id) == NULL) {
            return global_search(id);
        } else {
            return search_symbol(local_table, id);
        }
    }else{
        return global_search(id);
    }
    
    return NULL;
}

Status declare_function(char *id, INFO *desc_id){

    if(!id || !desc_id) return ERROR;

    if(search_symbol(global_table, id) != NULL) {
       return ERROR;
    } else {
        insert_symbol(global_table, id, desc_id->kind, desc_id->type, desc_id->category, desc_id->size, desc_id->aux1, desc_id->aux2);  /*Set global table*/
        /* Table_local ini */
        if (!local_table) local_table = create_hash_table(TOTAL_SIZE_LOCAL);
        if (!local_table) {
            delete_symbol(global_table, id);
            return ERROR;
        }

        if(insert_symbol(local_table, id, desc_id->kind, desc_id->type, desc_id->category, desc_id->size, desc_id->aux1, desc_id->aux2) == ERROR) {
            delete_symbol(global_table, id);
            return ERROR;
        }
        return OK;
    }
}

void close() {

    if(!local_table) return;
    free_hash_table(local_table);
    local_table = NULL;
}

void free_tables() {
    free_hash_table(local_table);
    free_hash_table(global_table);
}