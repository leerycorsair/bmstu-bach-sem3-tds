#include <stdio.h>

#include "io_lib.h"
#include "err_codes.h"
#include "data.h"
#include "tools.h"
#include "tree.h"
#include "file.h"
#include "hash.h"

void go_readdata(vector_t *data)
{
    data_read(data);
}

// void go_wipedata(vector_t *data)
// {
//     data_wipe(data);
//     data_init(data);
// }

void go_formtree(vector_t data, vertex_t **ubtree)
{
    if (data.data == NULL)
    {
        printf(ANSI_COLOR_RED "Данные отсутствуют.\n" ANSI_COLOR_RESET);
        return;
    }
    tree_wipe(ubtree);
    uint64_t time = tick();
    if (tree_form(ubtree, data))
    {
        printf(ANSI_COLOR_RED "Память не удалось выделить.\n" ANSI_COLOR_RESET);
        tree_wipe(ubtree);
    }
    else
    {
        time = tick() - time;
        printf(ANSI_COLOR_MAGENTA "Время для создания ДДП: %zu\n" ANSI_COLOR_RESET, time);
    }
}

void go_bformtree(vector_t data, vertex_t **btree)
{
    if (data.data == NULL)
    {
        printf(ANSI_COLOR_RED "Данные отсутствуют.\n" ANSI_COLOR_RESET);
        return;
    }
    tree_wipe(btree);
    uint64_t time = tick();
    if (tree_balanced_form(btree, data))
    {
        printf(ANSI_COLOR_RED "Память не удалось выделить.\n" ANSI_COLOR_RESET);
        tree_wipe(btree);
    }
    else
    {
        time = tick() - time;
        printf(ANSI_COLOR_MAGENTA "Время для создания сбалансированного ДДП: %zu\n" ANSI_COLOR_RESET, time);
    }
}

void go_treeinsert(vertex_t **ubtree, data_t *data)
{
    if (*ubtree == NULL || (*ubtree)->data == NULL)
    {
        printf(ANSI_COLOR_RED "Данные не инициализированны.\n" ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_MAGENTA "Введите строку для вставки:" ANSI_COLOR_RESET);
    char *str = malloc(sizeof(char) * MAX_STR_LEN);
    if (scanf("%s", str) <= 0)
        printf(ANSI_COLOR_RED "Некорректная строка.\n" ANSI_COLOR_RESET);
    else
    {
        vector_add(data, str);
        uint64_t time = tick();
        vertex_t *vertex = vertex_create(str);
        if (vertex == NULL)
            return;
        *ubtree = tree_insert(*ubtree, vertex, &strcmp);
        time = tick() - time;
        printf(ANSI_COLOR_MAGENTA "Время для вставки в ДДП: %zu\n" ANSI_COLOR_RESET, time);
    }
}
void go_hashinsert(hash_table_t *hash_table, data_t *data)
{
    if (hash_table->curr_size == 0)
    {
        printf(ANSI_COLOR_RED "Хэш-таблица не проинициализированна");
        return;
    }
    printf(ANSI_COLOR_MAGENTA "Введите строку для вставки:" ANSI_COLOR_RESET);
    char *str = malloc(sizeof(char) * MAX_STR_LEN);
    if (scanf("%s", str) <= 0)
        printf(ANSI_COLOR_RED "Некорректная строка.\n" ANSI_COLOR_RESET);
    else
    {
        vector_add(data, str);
        uint64_t time = tick();
        hash_t *hash = hash_create(str);
        if (hash == NULL)
            return;
        hash_insert(hash_table, hash);
        time = tick() - time;
        printf(ANSI_COLOR_MAGENTA "Время для вставки в хэш-таблицу: %zu\n" ANSI_COLOR_RESET, time);
    }
}

void go_btreeinsert(vertex_t **btree, data_t *data)
{
    if (*btree == NULL || (*btree)->data == NULL)
    {
        printf(ANSI_COLOR_RED "Данные не инициализированны.\n" ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_MAGENTA "Введите строку для вставки:" ANSI_COLOR_RESET);
    char *str = malloc(sizeof(char) * MAX_STR_LEN);
    if (scanf("%s", str) <= 0)
        printf(ANSI_COLOR_RED "Некорректная строка.\n" ANSI_COLOR_RESET);
    else
    {
        vector_add(data, str);
        uint64_t time = tick();
        vertex_t *vertex = vertex_create(str);
        if (vertex == NULL)
            return;
        *btree = tree_balanced_insert(*btree, vertex, &strcmp);
        time = tick() - time;
        printf(ANSI_COLOR_MAGENTA "Время для вставки в сбалансированное ДДП: %zu\n" ANSI_COLOR_RESET, time);
    }
}

void go_treedel(vertex_t **ubtree)
{
    if (*ubtree == NULL || (*ubtree)->data == NULL)
    {
        printf(ANSI_COLOR_RED "Данные отсутствуют.\n" ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_MAGENTA "Введите строку для удаления:" ANSI_COLOR_RESET);
    char *str = malloc(sizeof(char) * MAX_STR_LEN);
    if (scanf("%s", str) <= 0)
        printf(ANSI_COLOR_RED "Некорректная строка.\n" ANSI_COLOR_RESET);
    else
    {
        size_t compared = 0;
        uint64_t time = tick();
        if (tree_search(*ubtree, str, strcmp, &compared))
            *ubtree = tree_delete(*ubtree, str, &strcmp);
        time = tick() - time;
        printf(ANSI_COLOR_MAGENTA "Время для удаления из ДДП: %zu\n" ANSI_COLOR_RESET, time);
    }
    free(str);
}

void go_hashdel(hash_table_t *hash_table)
{
    if (hash_table->curr_size == 0 || hash_table->hash == NULL)
    {
        printf(ANSI_COLOR_RED "Данные отсутствуют.\n" ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_MAGENTA "Введите строку для удаления:" ANSI_COLOR_RESET);
    char *str = malloc(sizeof(char) * MAX_STR_LEN);
    if (scanf("%s", str) <= 0)
        printf(ANSI_COLOR_RED "Некорректная строка.\n" ANSI_COLOR_RESET);
    else
    {
        size_t oper = 0;
        uint64_t time = tick();
        hash_del(hash_table, str, &oper);
        time = tick() - time;
        printf(ANSI_COLOR_MAGENTA "Время для удаления из хэш-таблицы: %zu\n" ANSI_COLOR_RESET, time);
    }
    free(str);
}

void go_btreedel(vertex_t **btree)
{
    if (*btree == NULL || (*btree)->data == NULL)
    {
        printf(ANSI_COLOR_RED "Данные отсутствуют.\n" ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_MAGENTA "Введите строку для удаления:" ANSI_COLOR_RESET);
    char *str = malloc(sizeof(char) * MAX_STR_LEN);
    if (scanf("%s", str) <= 0)
        printf(ANSI_COLOR_RED "Некорректная строка.\n" ANSI_COLOR_RESET);
    else
    {
        size_t compared = 0;
        uint64_t time = tick();
        if (tree_search(*btree, str, strcmp, &compared))
            *btree = tree_balanced_delete(*btree, str, strcmp);
        time = tick() - time;
        printf(ANSI_COLOR_MAGENTA "Время для удаления из сбалансированного ДДП: %zu\n" ANSI_COLOR_RESET, time);
    }
    free(str);
}

void go_treesearch(vertex_t *ubtree)
{
    vertex_t *res = NULL;
    printf(ANSI_COLOR_MAGENTA "Введите строку для поиска:" ANSI_COLOR_RESET);
    char *str = malloc(sizeof(char) * MAX_STR_LEN);
    if (scanf("%s", str) <= 0)
        printf(ANSI_COLOR_RED "Некорректная строка.\n" ANSI_COLOR_RESET);
    else
    {
        size_t compared = 0;
        uint64_t time = tick();
        res = tree_search(ubtree, str, strcmp, &compared);
        time = tick() - time;
        if (res != NULL)
            printf(ANSI_COLOR_GREEN "Слово найдено за %zu сравнений.\n" ANSI_COLOR_RESET, compared);
        else
            printf(ANSI_COLOR_YELLOW "Слово не найдено, прошло %zu сравнений.\n" ANSI_COLOR_RESET, compared);
        printf(ANSI_COLOR_MAGENTA "Время для поиска в ДДП: %zu\n" ANSI_COLOR_RESET, time);
    }
    free(str);
}

void go_treeprint(vertex_t *ubtree)
{
    FILE *f = fopen("ubtree.gv", "w");
    fprintf(f, "digraph ubtree{\n");
    if (f)
        fclose(f);
    tree_post_apply(ubtree, &tree_fprint_graph, "ubtree.gv");
    f = fopen("ubtree.gv", "a");
    fprintf(f, "}");
    if (f)
        fclose(f);
    system("dot -Tpng ubtree.gv -o ubtree.png");
    system("rm ubtree.gv");
}

void go_btreesearch(vertex_t *btree)
{
    vertex_t *res = NULL;
    printf(ANSI_COLOR_MAGENTA "Введите строку для поиска:" ANSI_COLOR_RESET);
    char *str = malloc(sizeof(char) * MAX_STR_LEN);
    if (scanf("%s", str) <= 0)
        printf(ANSI_COLOR_RED "Некорректная строка.\n" ANSI_COLOR_RESET);
    else
    {
        size_t compared = 0;
        uint64_t time = tick();
        res = tree_search(btree, str, strcmp, &compared);
        time = tick() - time;
        if (res != NULL)
            printf(ANSI_COLOR_GREEN "Слово найдено за %zu сравнений.\n" ANSI_COLOR_RESET, compared);
        else
            printf(ANSI_COLOR_YELLOW "Слово не найдено, прошло %zu сравнений.\n" ANSI_COLOR_RESET, compared);
        printf(ANSI_COLOR_MAGENTA "Время для поиска в сбалансированном ДДП: %zu\n" ANSI_COLOR_RESET, time);
    }
    free(str);
}

void go_btreeprint(vertex_t *btree)
{
    FILE *f = fopen("btree.gv", "w");
    fprintf(f, "digraph btree{\n");
    if (f)
        fclose(f);
    tree_post_apply(btree, &tree_fprint_graph, "btree.gv");
    f = fopen("btree.gv", "a");
    fprintf(f, "}");
    if (f)
        fclose(f);
    system("dot -Tpng btree.gv -o btree.png");
    system("rm btree.gv");
}

void go_filesearch(void)
{
    printf(ANSI_COLOR_MAGENTA "Введите имя файла:\n" ANSI_COLOR_RESET);
    char file_name[50];
    if (scanf("%s", file_name) <= 0)
    {
        printf(ANSI_COLOR_RED "Не удалось прочесть имя.\n" ANSI_COLOR_RESET);
        return;
    }
    FILE *f = fopen(file_name, "r");
    if (!f)
    {
        printf(ANSI_COLOR_RED "Не удалось открыть файл.\n" ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_MAGENTA "Введите слово для поиска:\n" ANSI_COLOR_RESET);
    char search[MAX_STR_LEN];
    if (scanf("%s", search) <= 0)
    {
        fclose(f);
        printf(ANSI_COLOR_RED "Не удалось прочесть строку.\n" ANSI_COLOR_RESET);
        return;
    }
    uint64_t time = tick();
    int compared = search_file(search, f);
    time = tick() - time;
    if (compared)
        printf(ANSI_COLOR_GREEN "Слово найдено за %d сравнений.\n" ANSI_COLOR_RESET, compared);
    else
        printf(ANSI_COLOR_GREEN "Слово не найдено за %d сравнений.\n" ANSI_COLOR_RESET, compared);
    printf(ANSI_COLOR_MAGENTA "Время для поиска в файле: %zu\n" ANSI_COLOR_RESET, time);
    fclose(f);
}

void go_hashform(data_t *data, hash_table_t *hash_table)
{
    if (data->data == NULL)
    {
        printf(ANSI_COLOR_RED "Данные отсутствуют.\n" ANSI_COLOR_RESET);
        return;
    }
    hash_wipe(*hash_table);
    hash_table_init(hash_table);
    uint64_t time = tick();
    if (hash_form(hash_table, next_prime(data->curr_len), *data))
    {
        printf(ANSI_COLOR_RED "Память не удалось выделить.\n" ANSI_COLOR_RESET);
        hash_wipe(*hash_table);
    }
    else
    {
        time = tick() - time;
        printf(ANSI_COLOR_MAGENTA "Время для создания хэш-таблицы: %zu\n" ANSI_COLOR_RESET, time);
    }
}

void go_hashreform(data_t *data, hash_table_t *hash_table)
{
    if (data->data == NULL)
    {
        printf(ANSI_COLOR_RED "Данные отсутствуют.\n" ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_MAGENTA "Введите максимальное количество коллизий:" ANSI_COLOR_RESET);
    size_t c;
    if (!scanf("%zu", &c) || c == 0)
    {
        printf(ANSI_COLOR_RED "Вы сделали ошибку" ANSI_COLOR_RESET);
        return;
    }
    size_t size;
    uint64_t time = tick();
    while (hash_table->max_collisions > c)
    {
        size = hash_table->curr_size;
        hash_wipe(*hash_table);
        hash_table_init(hash_table);
        if (hash_form(hash_table, next_prime(size), *data))
        {
            printf(ANSI_COLOR_RED "Память не удалось выделить.\n" ANSI_COLOR_RESET);
            hash_wipe(*hash_table);
            return;
        }
        if (hash_table->max_collisions <= c)
            break;
        hash_wipe(*hash_table);
        hash_table_init(hash_table);
        hash_table->hash_func = 2;
        if (hash_form(hash_table, next_prime(size), *data))
        {
            printf(ANSI_COLOR_RED "Память не удалось выделить.\n" ANSI_COLOR_RESET);
            hash_wipe(*hash_table);
            return;
        }
    }
    time = tick() - time;
    printf(ANSI_COLOR_MAGENTA "Время для устранения коллизий хэш-таблицы: %zu\n" ANSI_COLOR_RESET, time);
}

void go_hashprint(hash_table_t hash_table)
{
    hash_print(hash_table);
}

void go_hashsearch(hash_table_t hash_table)
{
    if (hash_table.hash == NULL || hash_table.curr_size == 0)
    {
        printf(ANSI_COLOR_RED "Хэш-таблица не проинициализированна");
        return;
    }
    hash_t *res = NULL;
    printf(ANSI_COLOR_MAGENTA "Введите строку для поиска:" ANSI_COLOR_RESET);
    char *str = malloc(sizeof(char) * MAX_STR_LEN);
    if (scanf("%s", str) <= 0)
        printf(ANSI_COLOR_RED "Некорректная строка.\n" ANSI_COLOR_RESET);
    else
    {
        size_t compared = 0;
        uint64_t time = tick();
        res = hash_find(&hash_table, str, &strcmp, &compared);
        time = tick() - time;
        if (res != NULL)
            printf(ANSI_COLOR_GREEN "Слово найдено за %zu сравнений.\n" ANSI_COLOR_RESET, compared);
        else
            printf(ANSI_COLOR_YELLOW "Слово не найдено, прошло %zu сравнений.\n" ANSI_COLOR_RESET, compared);
        printf(ANSI_COLOR_MAGENTA "Время для поиска в хеш-таблице: %zu\n" ANSI_COLOR_RESET, time);
    }
    free(str);
}

void go_exit(data_t *data, vertex_t **btree, vertex_t **ubtree, hash_table_t *hash_table)
{
    data_wipe(data);
    tree_wipe(btree);
    tree_wipe(ubtree);
    hash_wipe(*hash_table);
}

void go_hashmem(hash_table_t hash_table)
{
    size_t mem = 0;
    for (size_t i = 0; i < hash_table.curr_size; i++)
        if (hash_table.hash[i])
            mem += list_len(hash_table.hash[i]) * sizeof(hash_t);
        else
            mem += sizeof(hash_t);
    printf("Объем памяти хеш-таблицы: %zu байт", mem);
}

void go_treemem(data_t data)
{
    size_t mem = data.curr_len * sizeof(vertex_t);
    printf("Объем памяти дерева в пике: %zu байт", mem);
}

#define MAX_ITER 10
void go_structs_cmp(data_t data, vertex_t **btree, vertex_t **ubtree, hash_table_t *hash_table)
{
    if (data.data == NULL)
    {
        printf(ANSI_COLOR_RED "Данные отсутствуют.\n" ANSI_COLOR_RESET);
        return;
    }
    tree_wipe(ubtree);
    uint64_t general_time_tree = 0;
    for (int i = 0; i < MAX_ITER; i++)
    {
        uint64_t time = tick();
        if (tree_form(ubtree, data))
        {
            printf(ANSI_COLOR_RED "Память не удалось выделить.\n" ANSI_COLOR_RESET);
            tree_wipe(ubtree);
        }
        else
        {
            time = tick() - time;
            general_time_tree += time;
            tree_wipe(ubtree);
        }
    }
    tree_wipe(btree);
    uint64_t general_time_btree = 0;
    for (int i = 0; i < MAX_ITER; i++)
    {
        uint64_t time = tick();
        if (tree_balanced_form(btree, data))
        {
            printf(ANSI_COLOR_RED "Память не удалось выделить.\n" ANSI_COLOR_RESET);
            tree_wipe(btree);
        }
        else
        {
            time = tick() - time;
            general_time_btree += time;
            tree_wipe(btree);
        }
    }
    hash_wipe(*hash_table);
    hash_table_init(hash_table);
    uint64_t general_time_hash = 0;
    for (int i = 0; i < MAX_ITER; i++)
    {
        uint64_t time = tick();
        if (hash_form(hash_table, next_prime(data.curr_len), data))
        {
            printf(ANSI_COLOR_RED "Память не удалось выделить.\n" ANSI_COLOR_RESET);
            hash_wipe(*hash_table);
        }
        else
        {
            time = tick() - time;
            general_time_hash += time;
            hash_wipe(*hash_table);
            hash_table_init(hash_table);
        }
    }
    tree_form(ubtree, data);
    tree_balanced_form(btree, data);
    hash_table_init(hash_table);
    hash_form(hash_table, data.curr_len, data);

    uint64_t search_tree_t = 0;
    size_t compared_tree = 0;
    for (size_t i = 0; i < data.curr_len; i++)
    {
        uint64_t time = tick();
        tree_search(*ubtree, data.data[i], strcmp, &compared_tree);
        time = tick() - time;
        search_tree_t += time;
    }

    uint64_t search_btree_t = 0;
    size_t compared_btree = 0;
    for (size_t i = 0; i < data.curr_len; i++)
    {
        uint64_t time = tick();
        tree_search(*btree, data.data[i], strcmp, &compared_btree);
        time = tick() - time;
        search_btree_t += time;
    }

    uint64_t search_hash_t = 0;
    size_t compared_hash = 0;
    for (size_t i = 0; i < data.curr_len; i++)
    {
        uint64_t time = tick();
        hash_find(hash_table, data.data[i], strcmp, &compared_hash);
        time = tick() - time;
        search_hash_t += time;
    }

    uint64_t del_tree_t = 0;
    for (size_t i = 0; i < data.curr_len; i++)
    {
        uint64_t time = tick();
        *ubtree = tree_delete(*ubtree, data.data[i], strcmp);
        time = tick() - time;
        del_tree_t += time;
    }

    uint64_t del_btree_t = 0;
    for (size_t i = 0; i < data.curr_len; i++)
    {
        uint64_t time = tick();
        *btree = tree_balanced_delete(*btree, data.data[i], strcmp);
        time = tick() - time;
        del_btree_t += time;
    }

    uint64_t del_hash_t = 0;
    for (size_t i = 0; i < data.curr_len; i++)
    {
        uint64_t time = tick();
        size_t del_hash = 0;
        hash_del(hash_table, data.data[i], &del_hash);
        time = tick() - time;
        del_hash_t += time;
    }

    tree_wipe(ubtree);
    tree_wipe(btree);
    hash_wipe(*hash_table);

    printf(ANSI_COLOR_YELLOW "------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "|             |     ДДП     |     АВЛ дерево     |     Хэш-таблица     |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "|   Создание  |%13zu|%20zu|%21zu|\n" ANSI_COLOR_RESET, general_time_tree / MAX_ITER, general_time_btree / MAX_ITER, general_time_hash / MAX_ITER);
    printf(ANSI_COLOR_YELLOW "------------------------------------------------------------------------\n" ANSI_COLOR_YELLOW);
    printf(ANSI_COLOR_YELLOW "|  Добавление |%13zu|%20zu|%21zu|\n" ANSI_COLOR_RESET, general_time_tree / MAX_ITER / data.curr_len, general_time_btree / MAX_ITER / data.curr_len, general_time_hash / MAX_ITER / data.curr_len);
    printf(ANSI_COLOR_YELLOW "------------------------------------------------------------------------\n" ANSI_COLOR_YELLOW);
    printf(ANSI_COLOR_YELLOW "|    Поиск    |%13zu|%20zu|%21zu|\n" ANSI_COLOR_RESET, search_tree_t / data.curr_len, search_btree_t / data.curr_len, search_hash_t / data.curr_len);
    printf(ANSI_COLOR_YELLOW "------------------------------------------------------------------------\n" ANSI_COLOR_YELLOW);
    printf(ANSI_COLOR_YELLOW "|   Удаление  |%13zu|%20zu|%21zu|\n" ANSI_COLOR_RESET, del_tree_t / data.curr_len, del_btree_t / data.curr_len, del_hash_t / data.curr_len);
    printf(ANSI_COLOR_YELLOW "------------------------------------------------------------------------\n" ANSI_COLOR_YELLOW);

    printf("Объем памяти ДДП - %zu байт\n", data.curr_len * sizeof(vertex_t));
    printf("Объем памяти АВЛ дерева - %zu байт\n", data.curr_len * sizeof(vertex_t));
    hash_table_init(hash_table);
    hash_form(hash_table, data.curr_len, data);
    go_hashmem(*hash_table);
    hash_wipe(*hash_table);
    hash_table_init(hash_table);
}

void option_perform(int *option, data_t *data, vertex_t **btree, vertex_t **ubtree, hash_table_t *hash_table)
{
    switch (*option)
    {
    case 0:
        go_exit(data, btree, ubtree, hash_table);
        break;
    case 10:
        go_readdata(data);
        break;
    // case 11:
    //     go_wipedata(data);
    //     break;
    case 11:
        go_filesearch();
        break;
    case 20:
        go_formtree(*data, ubtree);
        break;
    case 21:
        go_treeinsert(ubtree, data);
        break;
    case 22:
        go_treedel(ubtree);
        break;
    case 23:
        go_treesearch(*ubtree);
        break;
    case 24:
        go_treeprint(*ubtree);
        break;
    case 25:
        go_treemem(*data);
        break;
    case 35:
        go_treemem(*data);
        break;
    case 30:
        go_bformtree(*data, btree);
        break;
    case 31:
        go_btreeinsert(btree, data);
        break;
    case 32:
        go_btreedel(btree);
        break;
    case 33:
        go_btreesearch(*btree);
        break;
    case 34:
        go_btreeprint(*btree);
        break;
    case 40:
        go_hashform(data, hash_table);
        break;
    case 41:
        go_hashreform(data, hash_table);
        break;
    case 42:
        go_hashinsert(hash_table, data);
        break;
    case 43:
        go_hashdel(hash_table);
        break;
    case 44:
        go_hashsearch(*hash_table);
        break;
    case 45:
        go_hashprint(*hash_table);
        break;
    case 46:
        go_hashmem(*hash_table);
        break;
    case 50:
        go_structs_cmp(*data, ubtree, btree, hash_table);
        break;
    default:
        printf(ANSI_COLOR_RED "Некорректная опция меню.\n" ANSI_COLOR_RESET);
        break;
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    print_welcome();

    data_t data;
    data_init(&data);

    vertex_t *unbalanced_tree = NULL;
    vertex_t *balanced_tree = NULL;
    hash_table_t hash_table;
    hash_table_init(&hash_table);

    int option = -1;
    while (option)
    {
        option = -1;
        print_menu();
        printf(ANSI_COLOR_MAGENTA "Выберите опцию меню:" ANSI_COLOR_RESET);
        scanf("%d", &option);
        option_perform(&option, &data, &balanced_tree, &unbalanced_tree, &hash_table);
        empty_stream(stdin);
    }
    return SUCCESS;
}