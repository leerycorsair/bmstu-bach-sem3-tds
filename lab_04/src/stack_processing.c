#include "stack_processing.h"

/**
 * @brief Generates a stack of SIZE elems.
 * 
 * @param list_stack 
 * @param vector_stack 
 * @param size 
 * @return int 
 */
int gen_stack(list_stack_t *list_stack, vector_stack_t *vector_stack, int size)
{
    srand(rand());
    for (int i = 0; i < size; i++)
        if (vector_stack_push(vector_stack, rand() % 200 - 100))
            return PUSH_ERROR;
    if (form_ls_by_vs(list_stack, *vector_stack))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    return SUCCESS;
}

/**
 * @brief Pushes the VALUE in a vector stack.
 * 
 * @param vector_stack 
 * @param value 
 * @return int 
 */
int vector_stack_push(vector_stack_t *vector_stack, int value)
{
    if (vector_stack->curr_size == MAX_STACK_SIZE)
    {
        printf(ANSI_COLOR_RED "Стек полон" ANSI_COLOR_RESET);
        return SUCCESS;
    }
    if (vector_stack->curr_size == vector_stack->elems_allocated && vector_stack_inc_len(vector_stack))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    *(vector_stack->pointer_end) = value;
    vector_stack->pointer_end++;
    vector_stack->curr_size++;
    return SUCCESS;
}

/**
 * @brief Pops the last element in a vector stack.
 * 
 * @param vector_stack 
 * @return int 
 */
int vector_stack_pop(vector_stack_t *vector_stack)
{
    if (vector_stack->pointer_end == vector_stack->pointer_start)
    {
        printf(ANSI_COLOR_RED "Стек пустой" ANSI_COLOR_RESET);
        return SUCCESS;
    }
    vector_stack->pointer_end--;
    vector_stack->curr_size--;
    return SUCCESS;
}

/**
 * @brief Pushes the VALUE in a list stack. 
 * 
 * @param list_stack 
 * @param value 
 * @return int 
 */
int list_stack_push(list_stack_t *list_stack, int value)
{
    node_t *curr_node = node_create(value);
    if (curr_node == NULL)
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    if (list_stack->curr_size == MAX_STACK_SIZE)
    {
        printf(ANSI_COLOR_RED "Стек полон" ANSI_COLOR_RESET);
        return SUCCESS;
    }
    curr_node->next = list_stack->head;
    list_stack->head = curr_node;
    list_stack->curr_size++;
    return SUCCESS;
}

/**
 * @brief Pops the last element in a list stack.
 * 
 * @param list_stack 
 * @return int 
 */
int list_stack_pop(list_stack_t *list_stack)
{
    if (list_stack->curr_size == 0)
    {
        printf(ANSI_COLOR_RED "Стек пуст" ANSI_COLOR_RESET);
        return SUCCESS;
    }
    node_t *tmp = list_stack->head;
    node_t *ptr = list_stack->head->next;
    list_stack->head = ptr;
    del_node(tmp);
    list_stack->curr_size--;
    return SUCCESS;
}

// /**
//  * @brief Returns the current time in CPU ticks.
//  *
//  * @return uint64_t
//  */
// uint64_t tick(void)
// {
//     uint32_t high, low;
//     __asm__ __volatile__(
//         "rdtsc\n"
//         "movl %%edx, %0\n"
//         "movl %%eax, %1\n"
//         : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

//     uint64_t ticks = ((uint64_t)high << 32) | low;

//     return ticks;
// }

/**
 * @brief Merges 2 vector stacks and sorts it.
 * 
 * @param vector_stack_1 
 * @param vector_stack_2 
 * @param vector_stack_3 
 * @return int 
 */
int sort_vector_stacks(vector_stack_t vector_stack_1, vector_stack_t vector_stack_2, vector_stack_t *vector_stack_3)
{
    if (vector_stack_1.curr_size == 0 && vector_stack_2.curr_size == 0)
        return EMPTY_VECTORS;
    if (merge_vector_stacks(vector_stack_1, vector_stack_2, vector_stack_3) || sort_vector_stack(vector_stack_3))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    return SUCCESS;
}

/**
 * @brief Merges two vector stacks in the third one.
 * 
 * @param vector_stack_1 
 * @param vector_stack_2 
 * @param vector_stack_3 
 * @return int 
 */
int merge_vector_stacks(vector_stack_t vector_stack_1, vector_stack_t vector_stack_2, vector_stack_t *vector_stack_3)
{
    vector_stack_1.pointer_end--;
    while (vector_stack_1.pointer_end >= vector_stack_1.pointer_start)
    {
        if (vector_stack_push(vector_stack_3, *vector_stack_1.pointer_end))
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        vector_stack_1.pointer_end--;
    }
    vector_stack_2.pointer_end--;
    while (vector_stack_2.pointer_end >= vector_stack_2.pointer_start)
    {
        if (vector_stack_push(vector_stack_3, *vector_stack_2.pointer_end))
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        vector_stack_2.pointer_end--;
    }
    return SUCCESS;
}

/**
 * @brief Sorts a vector stack using PUSH&POP operations.
 * 
 * @param vector_stack 
 * @return int 
 */
int sort_vector_stack(vector_stack_t *vector_stack)
{
    int num;
    vector_stack_t tmp_stack = {.pointer_start = NULL, .pointer_end = NULL, .elems_allocated = 0, .curr_size = 0};
    while (vector_stack->curr_size != 0)
    {
        int value = *(vector_stack->pointer_end - 1);
        vector_stack_pop(vector_stack);
        while (tmp_stack.curr_size != 0 && *(tmp_stack.pointer_end - 1) < value)
            if (vector_stack_push(vector_stack, (num = *(tmp_stack.pointer_end - 1))) || vector_stack_pop(&tmp_stack) != SUCCESS)
            {
                del_vector_stack(&tmp_stack);
                return UNSUCCESSFUL_MEMORY_ALLOCATION;
            }
        if (vector_stack_push(&tmp_stack, value))
        {
            del_vector_stack(&tmp_stack);
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        }
    }
    while (tmp_stack.curr_size != 0)
        if (vector_stack_push(vector_stack, (num = *(tmp_stack.pointer_end - 1))) || vector_stack_pop(&tmp_stack) != SUCCESS)
        {
            del_vector_stack(&tmp_stack);
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        }
    return SUCCESS;
}

/**
 * @brief Merges 2 list stacks and sorts it.
 * 
 * @param list_stack_1 
 * @param list_stack_2 
 * @param list_stack_3 
 * @return int 
 */
int sort_list_stacks(list_stack_t list_stack_1, list_stack_t list_stack_2, list_stack_t *list_stack_3)
{
    if (list_stack_1.curr_size == 0 && list_stack_2.curr_size == 0)
        return EMPTY_LISTS;
    if (merge_list_stacks(list_stack_1, list_stack_2, list_stack_3) || sort_list_stack(list_stack_3))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    return SUCCESS;
}

/**
 * @brief Merges two list stacks in the third one.
 * 
 * @param list_stack_1 
 * @param list_stack_2 
 * @param list_stack_3 
 * @return int 
 */
int merge_list_stacks(list_stack_t list_stack_1, list_stack_t list_stack_2, list_stack_t *list_stack_3)
{
    while (list_stack_1.head != NULL)
    {
        if (list_stack_push(list_stack_3, list_stack_1.head->value))
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        list_stack_1.head = list_stack_1.head->next;
    }
    while (list_stack_2.head != NULL)
    {
        if (list_stack_push(list_stack_3, list_stack_2.head->value))
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        list_stack_2.head = list_stack_2.head->next;
    }
    return SUCCESS;
}

/**
 * @brief Sorts a list stack using PUSH&POP operations.
 * 
 * @param list_stack 
 * @return int 
 */
int sort_list_stack(list_stack_t *list_stack)
{
    int num;
    list_stack_t tmp_stack = {.head = NULL, .curr_size = 0};
    while (list_stack->curr_size != 0)
    {
        int value = list_stack->head->value;
        list_stack_pop(list_stack);
        while (tmp_stack.curr_size != 0 && tmp_stack.head->value < value)
            if (list_stack_push(list_stack, (num = tmp_stack.head->value)) || list_stack_pop(&tmp_stack) != SUCCESS)
            {
                del_list_stack(&tmp_stack);
                return UNSUCCESSFUL_MEMORY_ALLOCATION;
            }
        if (list_stack_push(&tmp_stack, value))
        {
            del_list_stack(&tmp_stack);
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        }
    }
    while (tmp_stack.curr_size != 0)
        if (list_stack_push(list_stack, (num = tmp_stack.head->value)) || list_stack_pop(&tmp_stack) != SUCCESS)
        {
            del_list_stack(&tmp_stack);
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        }
    del_list_stack(&tmp_stack);
    return SUCCESS;
}