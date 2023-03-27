#include "hash.h"

#include <math.h>

void hash_table_init(hash_table_t *hash_table)
{
    hash_table->hash = NULL;
    hash_table->curr_size = 0;
    hash_table->max_collisions = 0;
    hash_table->hash_func = 1;
}

hash_t *hash_create(void *data)
{
    return node_create(data);
}

size_t hash_func_2(char *str)
{
    size_t i = 1;
    size_t hash_sum = 0;
    while (*str++)
        hash_sum += *str * i++;
    return hash_sum;
}

size_t hash_func_1(char *str)
{
    size_t hash_sum = 0;
    while (*str++)
        hash_sum = ((hash_sum << 10) + hash_sum) + *str;
    return hash_sum;
}

int hash_form(hash_table_t *hash_table, size_t hash_table_size, data_t data)
{
    size_t (*hash_func)(char *);
    if (hash_table->hash_func == 1)
        hash_func = &hash_func_1;
    else
        hash_func = &hash_func_2;
    hash_table->hash = calloc(hash_table_size, sizeof(hash_t *));
    hash_table->curr_size = hash_table_size;
    size_t collisions = 0;
    for (size_t i = 0; i < data.curr_len; i++)
    {
        hash_t *hash = hash_create(data.data[i]);
        if (!hash)
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        if (!list_check(hash_table->hash[hash_func(data.data[i]) % hash_table->curr_size], hash))
        {
            list_push(&hash_table->hash[hash_func(data.data[i]) % hash_table->curr_size], hash);
            collisions = list_len(hash_table->hash[hash_func(data.data[i]) % hash_table->curr_size]);
        }
        else
            node_free(&hash);

        if (collisions > hash_table->max_collisions)
            hash_table->max_collisions = collisions;
    }
    return SUCCESS;
}

void hash_wipe(hash_table_t hash_table)
{
    for (size_t i = 0; i < hash_table.curr_size; i++)
        list_wipe(&hash_table.hash[i]);
    free(hash_table.hash);
}

void hash_insert(hash_table_t *hash_table, hash_t *hash)
{
    size_t (*hash_func)(char *);
    if (hash_table->hash_func == 1)
        hash_func = &hash_func_1;
    else
        hash_func = &hash_func_2;
    size_t collisions;
    if (!list_check(hash_table->hash[hash_func(hash->data) % hash_table->curr_size], hash))
    {
        list_push(&hash_table->hash[hash_func(hash->data) % hash_table->curr_size], hash);
        collisions = list_len(hash_table->hash[hash_func(hash->data) % hash_table->curr_size]);
    }
    else
        free(hash->data);

    if (collisions > hash_table->max_collisions)
        hash_table->max_collisions = collisions;
}

void hash_del(hash_table_t *hash_table, void *data, size_t *oper)
{
    size_t (*hash_func)(char *);
    if (hash_table->hash_func == 1)
        hash_func = &hash_func_1;
    else
        hash_func = &hash_func_2;
    hash_t *hash = hash_table->hash[hash_func(data) % hash_table->curr_size];
    list_del(&hash, data, oper);
    hash_table->hash[hash_func(data) % hash_table->curr_size] = hash;
}

hash_t *hash_find(hash_table_t *hash_table, void *data, int (*comparator)(const char *, const char *), size_t *oper)
{
    size_t (*hash_func)(char *);
    if (hash_table->hash_func == 1)
        hash_func = &hash_func_1;
    else
        hash_func = &hash_func_2;
    *oper = 0;
    return list_find(hash_table->hash[hash_func(data) % hash_table->curr_size], data, comparator, oper);
}

void hash_print(hash_table_t hash_table)
{
    int check = 0;
    printf("------------------------------------------------------------\n");
    for (size_t i = 0; i < hash_table.curr_size; i++)
    {
        if (hash_table.hash[i])
        {
            check = 1;
            printf("%zu ", i);
            list_print(hash_table.hash[i]);
            printf("\n------------------------------------------------------------\n");
        }
    }
    if (check == 0)
    {
        printf(ANSI_COLOR_RED "Таблица пустая.\n" ANSI_COLOR_RESET);
        printf("------------------------------------------------------------\n");
    }
}