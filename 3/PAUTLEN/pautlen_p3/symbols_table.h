#ifndef SYMBOLS_TABLE_H
#define SYMBOLS_TABLE_H

#include "hash_table.h"

Status declare(char *id,  INFO* desc_id);
Status declare_global(char *id, INFO* desc_id);
Status declare_local(char *id, INFO* desc_id);
INFO* global_search(char *id);
INFO* local_search(char *id);
Status declare_function(char *id, INFO *desc_id);
void close();
void free_tables();
#endif