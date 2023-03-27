#include "data.h"

void data_init(data_t *data)
{
    data->data = NULL;
    data->curr_len = 0;
    data->max_len = 0;
}

int data_read(data_t *data)
{
    data_wipe(data);
    if (vector_init(data))
    {
        printf(ANSI_COLOR_RED "Не удалось выделить память под хранилище данных.\n" ANSI_COLOR_RESET);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }
    printf(ANSI_COLOR_MAGENTA "Введите имя файла:\n" ANSI_COLOR_RESET);
    char file_name[50];
    if (scanf("%s", file_name) <= 0)
    {
        printf(ANSI_COLOR_RED "Не удалось прочесть имя.\n" ANSI_COLOR_RESET);
        return INCORRECT_CONTENT;
    }
    FILE *f = fopen(file_name, "r");
    if (!f)
    {
        printf(ANSI_COLOR_RED "Не удалось открыть файл.\n" ANSI_COLOR_RESET);
        return INCORRECT_CONTENT;
    }
    char *buf = malloc(sizeof(char) * MAX_STR_LEN);
    while ((fscanf(f, "%s\n", buf) > 0))
    {
        if (vector_add(data, buf))
        {
            vector_free(data);
            printf(ANSI_COLOR_RED "Не удалось выделить память под хранилище данных.\n" ANSI_COLOR_RESET);
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        }
        buf = malloc(sizeof(char) * MAX_STR_LEN);
    }
    free(buf);
    if (data->curr_len == 0)
    {
        printf(ANSI_COLOR_RED "Пустой файл.\n" ANSI_COLOR_RESET);
        return INCORRECT_CONTENT;
    }
    fclose(f);
    return SUCCESS;
}

void data_wipe(data_t *data)
{
    if (data->data != NULL)
        for (size_t i = 0; i < data->curr_len; i++)
            free(data->data[i]);
    if (data->data != NULL)
        vector_free(data);
}

void print_data(data_t *data)
{
    for (size_t i = 0; i < data->curr_len; i++)
        printf("%s\n", (char *)data->data[i]);
}