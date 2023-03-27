#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>
#include "list.h"
#include "data.h"

typedef node_t hash_t;

typedef struct
{
    hash_t **hash;
    size_t curr_size;
    size_t max_collisions;
    int hash_func;
} hash_table_t;

void hash_table_init(hash_table_t *hash_table);
void hash_wipe(hash_table_t hash_table);
void hash_del(hash_table_t *hash_table, void *data, size_t *oper);
void hash_print(hash_table_t hash_table);
void hash_insert(hash_table_t *hash_table, hash_t *hash);

hash_t *hash_create(void *data);
hash_t *hash_find(hash_table_t *hash_table, void *data, int (*comparator)(const char *, const char *), size_t *oper);

size_t hash_func_1(char *str);
size_t hash_func_2(char *str);

int hash_form(hash_table_t *hash_table, size_t hash_table_size, data_t data);

#endif //__HASH_H__