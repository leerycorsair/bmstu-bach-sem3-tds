#ifndef __MEM_MANAGER_H__
#define __MEM_MANAGER_H__

#include <stdlib.h>
#include "err_codes.h"
#include "structs.h"

void memory_wipe(list_stack_t *list_stack_1, list_stack_t *list_stack_2, list_stack_t *list_stack_3, vector_stack_t *vector_stack_1, vector_stack_t *vector_stack_2, vector_stack_t *vector_stack_3);
void del_vector_stack(vector_stack_t *vector_stack);
void del_list_stack(list_stack_t *list_stack);
void del_node(node_t *node);
int vector_stack_inc_len(vector_stack_t *vector_stack);
node_t *node_create(int value);

#endif