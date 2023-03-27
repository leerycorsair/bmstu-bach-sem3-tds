#include "mem_manager.h"

#include <stdio.h>

/**
 * @brief Wipes full dynamic allocated memory.
 * 
 * @param list_stack_1 
 * @param list_stack_2 
 * @param list_stack_3 
 * @param vector_stack_1 
 * @param vector_stack_2 
 * @param vector_stack_3 
 */
void memory_wipe(list_stack_t *list_stack_1, list_stack_t *list_stack_2, list_stack_t *list_stack_3, vector_stack_t *vector_stack_1, vector_stack_t *vector_stack_2, vector_stack_t *vector_stack_3)
{
    del_vector_stack(vector_stack_1);
    del_vector_stack(vector_stack_2);
    del_vector_stack(vector_stack_3);

    del_list_stack(list_stack_1);
    del_list_stack(list_stack_2);
    del_list_stack(list_stack_3);
}

/**
 * @brief Deletes vector stack
 * 
 * @param vector_stack 
 */
void del_vector_stack(vector_stack_t *vector_stack)
{
    if (vector_stack->pointer_start != NULL)
    {
        free(vector_stack->pointer_start);
        vector_stack->pointer_start = NULL;
        vector_stack->pointer_end = NULL;
        vector_stack->curr_size = 0;
        vector_stack->elems_allocated = 0;
    }
}

/**
 * @brief Deletes list stack
 * 
 * @param list_stack 
 */
void del_list_stack(list_stack_t *list_stack)
{
    node_t *next;
    for (; list_stack->head; list_stack->head = next)
    {
        next = list_stack->head->next;
        del_node(list_stack->head);
    }
    list_stack->head = NULL;
    list_stack->curr_size = 0;
}

/**
 * @brief Deletes list node
 * 
 * @param node 
 */
void del_node(node_t *node)
{
    if (node != NULL)
        free(node);
    node = NULL;
}

/**
 * @brief Increases the length of vector stack in 2 times.
 * 
 * @param vector_stack 
 * @return int 
 */
int vector_stack_inc_len(vector_stack_t *vector_stack)
{
    if (vector_stack->elems_allocated == 0)
    {
        vector_stack->pointer_start = malloc(sizeof(int));
        if (vector_stack->pointer_start == NULL)
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        vector_stack->pointer_end = vector_stack->pointer_start;
        vector_stack->elems_allocated = 1;
    }
    else
    {
        int *tmp_p;
        tmp_p = realloc(vector_stack->pointer_start, vector_stack->curr_size * 2 * sizeof(int));
        if (tmp_p == NULL)
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        vector_stack->pointer_start = tmp_p;
        vector_stack->pointer_end = vector_stack->pointer_start + vector_stack->curr_size;
        vector_stack->elems_allocated *= 2;
    }
    return SUCCESS;
}

/**
 * @brief Creates of node of a list.
 * 
 * @return node_t* 
 */
node_t *node_create(int value)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (tmp == NULL)
        return NULL;
    tmp->value = value;
    return tmp;
}