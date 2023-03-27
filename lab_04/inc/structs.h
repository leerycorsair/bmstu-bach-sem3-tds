#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#define MAX_STACK_SIZE 4096

typedef struct
{
    int *pointer_start;
    int *pointer_end;
    int curr_size;
    int elems_allocated;
} vector_stack_t;

typedef struct node_t node_t;

struct node_t
{
    int value;
    node_t *next;
};

typedef struct
{
    node_t *head;
    int curr_size;
} list_stack_t;

#endif