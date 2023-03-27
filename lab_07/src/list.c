#include "list.h"

#include <string.h>
#include <stdio.h>

node_t *node_create(size_t data)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

void node_free(node_t **node)
{
    if (!node || !*node)
        return;
    else
    {
        free(*node);
        *node = NULL;
    }
}

void list_push(node_t **head, node_t *elem)
{
    if (*head == NULL)
        *head = elem;
    else
    {
        elem->next = *head;
        *head = elem;
    }
}

void list_wipe(node_t **head)
{
    while (*head)
    {
        node_t *tmp = (*head)->next;
        free(*head);
        *head = tmp;
    }
}

int list_check(node_t *head, size_t data)
{
    while (head)
    {
        if (head->data == data)
            return 1;
        head = head->next;
    }
    return 0;
}

int list_len(node_t *head)
{
    int len = 0;
    while (head)
    {
        len++;
        head = head->next;
    }
    return len;
}

void list_del(node_t **head_ref, size_t data)
{
    node_t *temp = *head_ref, *prev;
    if (temp != NULL && temp->data == data)
    {
        *head_ref = temp->next;
        node_free(&temp);
        return;
    }
    while (temp != NULL && temp->data != data)
    {

        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}
