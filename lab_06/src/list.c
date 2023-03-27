#include "list.h"

#include <string.h>
#include <stdio.h>

node_t *node_create(void *data)
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

int list_check(node_t *head, node_t *elem)
{
    while (head)
    {
        if (strcmp(head->data, elem->data) == 0)
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

void list_del(node_t **head_ref, char *str, size_t *oper)
{
    *oper = 0;
    node_t *temp = *head_ref, *prev;
    if (temp != NULL && strcmp(temp->data, str) == 0)
    {
        *oper += 1;
        *head_ref = temp->next;
        node_free(&temp);
        return;
    }
    while (temp != NULL && strcmp(temp->data, str))
    {
        *oper += 1;
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
    if (*oper)
        return;
}

node_t *list_find(node_t *head, void *data, int (*comparator)(const char *, const char *), size_t *oper)
{
    if (head == NULL || data == NULL)
        return NULL;
    for (; head; head = head->next)
    {
        *oper += 1;
        if (!comparator(data, head->data))
            return head;
    }
    return NULL;
}

void list_print(node_t *head)
{
    while (head)
    {
        printf("%s ", (char *)head->data);
        head = head->next;
    }
}