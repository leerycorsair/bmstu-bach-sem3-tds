#include "tree.h"

void tree_init(vertex_t *root)
{
    root->data = NULL;
    root->left = NULL;
    root->height = 0;
    root->right = NULL;
}

void tree_wipe(vertex_t **root)
{
    if (root != NULL && *root != NULL)
    {
        tree_wipe(&(*root)->left);
        tree_wipe(&(*root)->right);
        vertex_del(root);
    }
}

vertex_t *tree_insert(vertex_t *root, vertex_t *vertex, int (*comparator)(const char *, const char *))
{
    int cmp;
    if (root == NULL)
        return vertex;
    cmp = comparator(vertex->data, root->data);
    if (cmp < 0)
        root->left = tree_insert(root->left, vertex, comparator);
    else if (cmp > 0)
        root->right = tree_insert(root->right, vertex, comparator);
    return root;
}

int tree_form(vertex_t **root, data_t data)
{
    for (size_t i = 0; i < data.curr_len; i++)
    {
        vertex_t *vertex = vertex_create(data.data[i]);
        if (vertex == NULL)
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        *root = tree_insert(*root, vertex, &strcmp);
    }
    return SUCCESS;
}

void tree_post_apply(vertex_t *root, void (*f)(vertex_t *, void *), void *arg)
{
    if (root == NULL)
        return;
    tree_post_apply(root->left, f, arg);
    tree_post_apply(root->right, f, arg);
    f(root, arg);
}

vertex_t *tree_search(vertex_t *root, void *key, int (*comparator)(const char *, const char *), size_t *compared)
{
    int cmp;
    if (root == NULL)
        return NULL;
    cmp = comparator(key, root->data);
    (*compared)++;
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return tree_search(root->left, key, comparator, compared);
    else
        return tree_search(root->right, key, comparator, compared);
}

void tree_fprint_graph(vertex_t *root, void *file_name)
{
    FILE *f = fopen((char *)file_name, "a");
    if (f == NULL)
    {
        printf(ANSI_COLOR_RED "Не удалось создать файл.\n" ANSI_COLOR_RESET);
        return;
    }
    if (root->left)
        fprintf(f, "%s -> %s;\n", (char *)root->data, (char *)root->left->data);
    if (root->right)
        fprintf(f, "%s -> %s;\n", (char *)root->data, (char *)root->right->data);
    fclose(f);
}

vertex_t *tree_delete(vertex_t *root, void *key, int (*comparator)(const char *, const char *))
{
    if (root->data == NULL)
        return NULL;
    if (comparator(key, root->data) < 0)
        root->left = tree_delete(root->left, key, comparator);
    else if (comparator(key, root->data) > 0)
        root->right = tree_delete(root->right, key, comparator);
    else
    {
        if (root->left == NULL)
        {
            vertex_t *tmp = root->right;
            vertex_del(&root);
            return tmp;
        }
        else if (root->right == NULL)
        {
            vertex_t *tmp = root->left;
            vertex_del(&root);
            return tmp;
        }
        vertex_t *tmp = tree_min_vertex(root->right);
        root->data = tmp->data;
        root->right = tree_delete(root->right, tmp->data, comparator);
    }
    return root;
}

vertex_t *tree_min_vertex(vertex_t *vertex)
{
    vertex_t *current = vertex;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

vertex_t *tree_balanced_insert(vertex_t *root, vertex_t *vertex, int (*comparator)(const char *, const char *))
{
    int cmp;
    if (root == NULL)
        return vertex;
    cmp = comparator(vertex->data, root->data);
    if (cmp < 0)
        root->left = tree_balanced_insert(root->left, vertex, comparator);
    else if (cmp > 0)
        root->right = tree_balanced_insert(root->right, vertex, comparator);
    return vertex_balance(root);
}

vertex_t *tree_findmin(vertex_t *root)
{
    return root->left ? tree_findmin(root->left) : root;
}

vertex_t *tree_removemin(vertex_t *root)
{
    if (root->left == 0)
        return root->right;
    root->left = tree_removemin(root->left);
    return vertex_balance(root);
}

vertex_t *tree_balanced_delete(vertex_t *root, void *key, int (*comparator)(const char *, const char *))
{
    if (root == NULL)
        return root;
    if (comparator(key, root->data) < 0)
        root->left = tree_balanced_delete(root->left, key, comparator);
    else if (comparator(key, root->data) > 0)
        root->right = tree_balanced_delete(root->right, key, comparator);
    else
    {
        vertex_t *left = root->left;
        vertex_t *right = root->right;
        vertex_del(&root);
        if (!right)
            return left;
        vertex_t *min = tree_findmin(right);
        min->right = tree_removemin(right);
        min->left = left;
        return vertex_balance(min);
    }
    return vertex_balance(root);
}

int tree_balanced_form(vertex_t **root, data_t data)
{
    for (size_t i = 0; i < data.curr_len; i++)
    {
        vertex_t *vertex = vertex_create(data.data[i]);
        if (vertex == NULL)
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        *root = tree_balanced_insert(*root, vertex, strcmp);
    }
    return SUCCESS;
}