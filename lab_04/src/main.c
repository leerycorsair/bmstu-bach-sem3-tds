#define __USE_MINGW_ANSI_STDIO
#include "io_lib.h"
#include "err_codes.h"
#include "structs.h"
#include "mem_manager.h"

#include <math.h>

#define MAX_ITER 25
#define MAX_DATA_SIZE 1024

int main(void)
{
    setbuf(stdout, NULL);
    system("clear");
    print_welcome();
    int choice;
    list_stack_t list_stack_1 = {.curr_size = 0, .head = NULL};
    vector_stack_t vector_stack_1 = {.curr_size = 0, .pointer_start = NULL, .pointer_end = NULL, .elems_allocated = 0};
    list_stack_t list_stack_2 = {.curr_size = 0, .head = NULL};
    vector_stack_t vector_stack_2 = {.curr_size = 0, .pointer_start = NULL, .pointer_end = NULL, .elems_allocated = 0};
    list_stack_t list_stack_3 = {.curr_size = 0, .head = NULL};
    vector_stack_t vector_stack_3 = {.curr_size = 0, .pointer_start = NULL, .pointer_end = NULL, .elems_allocated = 0};
    node_t **free_mem_pointers = NULL;
    size_t free_mem_pointers_size = 0;
    int abc = 1;
    while (abc == 1)
    {
        print_menu();
        printf(ANSI_COLOR_MAGENTA "\nВыберите опцию меню: " ANSI_COLOR_RESET);
        if (scanf("%d", &choice) <= 0 || choice < 0 || choice > 9)
        {
            free(free_mem_pointers);
            memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
            printf(ANSI_COLOR_RED "\n\nНекорректный ввод.Программа завершена.\n\n" ANSI_COLOR_RESET);
            return INCORRECT_MENU_OPTION;
        }
        if (choice == 0)
        {
            free(free_mem_pointers);
            memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
            printf(ANSI_COLOR_GREEN "\n\nПрограмма успешно завершена.\n\n" ANSI_COLOR_RESET);
            return SUCCESS;
        }
        if (choice == 1)
        {
            free(free_mem_pointers);
            free_mem_pointers_size = 0;
            memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
            printf(ANSI_COLOR_MAGENTA "\nЧтение первого стека.\n" ANSI_COLOR_RESET);
            if (read_stack(&list_stack_1, &vector_stack_1))
            {
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                printf(ANSI_COLOR_GREEN "\n\nНекорректный ввод. Программа аварийно завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_INPUT;
            }
            printf(ANSI_COLOR_MAGENTA "\nЧтение второго стека.\n" ANSI_COLOR_RESET);
            if (read_stack(&list_stack_2, &vector_stack_2))
            {
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                printf(ANSI_COLOR_RED "\n\nНекорректный ввод. Программа аварийно завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_INPUT;
            }
            printf(ANSI_COLOR_GREEN "\nДанные успешно прочитаны.\n" ANSI_COLOR_RESET);
        }
        if (choice == 2)
        {
            int size;
            free(free_mem_pointers);
            free_mem_pointers_size = 0;
            memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
            printf(ANSI_COLOR_YELLOW "Введите количество элементов в 1 стеке:" ANSI_COLOR_RESET);
            if (scanf("%d", &size) <= 0 || size <= 0)
            {
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                printf(ANSI_COLOR_GREEN "\n\nНекорректный ввод. Программа аварийно завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_INPUT;
            }
            if (size > MAX_STACK_SIZE)
            {
                printf(ANSI_COLOR_RED "\nПревышен максимальный размер стека(%d)" ANSI_COLOR_RESET, MAX_STACK_SIZE);
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                return STACK_OVERFLOW;
            }
            if (gen_stack(&list_stack_1, &vector_stack_1, size))
            {
                printf(ANSI_COLOR_RESET "Не удалось выделить память." ANSI_COLOR_RESET);
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                return UNSUCCESSFUL_MEMORY_ALLOCATION;
            }

            printf(ANSI_COLOR_YELLOW "Введите количество элементов во 2 стеке:" ANSI_COLOR_RESET);
            if (scanf("%d", &size) <= 0 || size <= 0)
            {
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                printf(ANSI_COLOR_GREEN "\n\nНекорректный ввод. Программа аварийно завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_INPUT;
            }
            if (size > MAX_STACK_SIZE)
            {
                printf(ANSI_COLOR_RED "Превышен максимальный размер стека(%d)" ANSI_COLOR_RESET, MAX_STACK_SIZE);
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                return STACK_OVERFLOW;
            }
            if (gen_stack(&list_stack_2, &vector_stack_2, size))
            {
                printf(ANSI_COLOR_RESET "Не удалось выделить память." ANSI_COLOR_RESET);
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                return UNSUCCESSFUL_MEMORY_ALLOCATION;
            }
            printf(ANSI_COLOR_GREEN "\nДанные успешно сгенерированны.\n" ANSI_COLOR_RESET);
        }
        if (choice == 3)
        {
            int ch;
            printf(ANSI_COLOR_YELLOW "Опции:\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "1. 1 стек в виде вектора\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "2. 2 стек в виде вектора\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "3. Объединенный стек в виде вектора\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "4. 1 стек в виде списка\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "5. 2 стек в виде списка\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "6. Объединенный стек в виде списка\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "Выберите куда добавить элемент:\n" ANSI_COLOR_RESET);
            if (scanf("%d", &ch) == 0 || ch < 1 || ch > 6)
            {
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                printf(ANSI_COLOR_RED "\n\nНекорректный ввод.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_MENU_OPTION;
            }
            printf(ANSI_COLOR_YELLOW "Введите значение:" ANSI_COLOR_RESET);
            int value;
            if (scanf("%d", &value) == 0)
            {
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                printf(ANSI_COLOR_RED "\n\nНекорректный ввод.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_MENU_OPTION;
            }
            if (ch == 1 && vector_stack_push(&vector_stack_1, value) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                return PUSH_ERROR;
            if (ch == 2 && vector_stack_push(&vector_stack_2, value) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                return PUSH_ERROR;
            if (ch == 3 && vector_stack_push(&vector_stack_3, value) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                return PUSH_ERROR;
            if (ch == 4 && list_stack_push(&list_stack_1, value) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                return PUSH_ERROR;
            if (ch == 5 && list_stack_push(&list_stack_2, value) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                return PUSH_ERROR;
            if (ch == 6 && list_stack_push(&list_stack_3, value) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                return PUSH_ERROR;
            printf(ANSI_COLOR_GREEN "\nОперация завершена.\n" ANSI_COLOR_RESET);
        }
        if (choice == 4)
        {
            int ch;
            printf(ANSI_COLOR_YELLOW "Опции:\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "1. 1 стек в виде вектора\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "2. 2 стек в виде вектора\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "3. Объединенный стек в виде вектора\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "4. 1 стек в виде списка\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "5. 2 стек в виде списка\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "6. Объединенный стек в виде списка\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "Выберите откуда удалить элемент:\n" ANSI_COLOR_RESET);
            if (scanf("%d", &ch) == 0 || ch < 1 || ch > 6)
            {
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                printf(ANSI_COLOR_RED "\n\nНекорректный ввод.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_MENU_OPTION;
            }
            if (ch == 1 && vector_stack_pop(&vector_stack_1) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                return PUSH_ERROR;
            if (ch == 2 && vector_stack_pop(&vector_stack_2) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                return PUSH_ERROR;
            if (ch == 3 && vector_stack_pop(&vector_stack_3) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                return PUSH_ERROR;
            if (ch == 4)
            {
                if (list_stack_1.head != NULL)
                {
                    node_t **tmp_p;
                    if (free_mem_pointers_size == 0)
                        free_mem_pointers = NULL;
                    if ((tmp_p = realloc(free_mem_pointers, (free_mem_pointers_size + 1) * sizeof(node_t *))) == NULL)
                    {
                        printf(ANSI_COLOR_RESET "Не удалось выделить память." ANSI_COLOR_RESET);
                        free(free_mem_pointers);
                        memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                        return UNSUCCESSFUL_MEMORY_ALLOCATION;
                    }
                    free_mem_pointers = tmp_p;
                    free_mem_pointers_size++;
                    free_mem_pointers[free_mem_pointers_size - 1] = list_stack_1.head;
                }
                if (list_stack_pop(&list_stack_1) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                    return POP_ERROR;
            }
            if (ch == 5)
            {
                if (list_stack_2.head != NULL)
                {
                    node_t *tmp_p;
                    if ((tmp_p = realloc(free_mem_pointers, free_mem_pointers_size += 1)) == NULL)
                    {
                        printf(ANSI_COLOR_RESET "Не удалось выделить память." ANSI_COLOR_RESET);
                        free(free_mem_pointers);
                        memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                        return UNSUCCESSFUL_MEMORY_ALLOCATION;
                    }
                    free_mem_pointers_size++;
                    free_mem_pointers[free_mem_pointers_size - 1] = list_stack_2.head;
                }
                if (list_stack_pop(&list_stack_2) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                    return POP_ERROR;
            }
            if (ch == 6)
            {
                if (list_stack_3.head != NULL)
                {
                    node_t **tmp_p;
                    if ((tmp_p = realloc(free_mem_pointers, free_mem_pointers_size += 1)) == NULL)
                    {
                        printf(ANSI_COLOR_RESET "Не удалось выделить память." ANSI_COLOR_RESET);
                        free(free_mem_pointers);
                        memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                        return UNSUCCESSFUL_MEMORY_ALLOCATION;
                    }
                    free_mem_pointers_size++;
                    free_mem_pointers[free_mem_pointers_size - 1] = list_stack_3.head;
                }
                if (list_stack_pop(&list_stack_3) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                    return POP_ERROR;
            }
            printf(ANSI_COLOR_GREEN "\nОперация завершена.\n" ANSI_COLOR_RESET);
        }
        if (choice == 5)
        {
            clock_t time1, time2;
            int ec;
            del_vector_stack(&vector_stack_3);
            del_list_stack(&list_stack_3);
            if (vector_stack_1.curr_size + vector_stack_2.curr_size > MAX_STACK_SIZE)
            {
                printf(ANSI_COLOR_RED "\nПревышен максимальный размер стека." ANSI_COLOR_RESET);
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                return STACK_OVERFLOW;
            }
            time1 = clock();
            if ((ec = sort_vector_stacks(vector_stack_1, vector_stack_2, &vector_stack_3)) == SUCCESS)
            {
                time2 = clock();
                printf(ANSI_COLOR_GREEN "\nВремя на сортировку двух стеков в виде вектора, используя\n" ANSI_COLOR_RESET);
                printf(ANSI_COLOR_GREEN "дополнительный %ld" ANSI_COLOR_RESET, time2 - time1);
            }
            else if (ec == UNSUCCESSFUL_MEMORY_ALLOCATION)
            {
                printf(ANSI_COLOR_RED "Не удалось выделить память." ANSI_COLOR_RESET);
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                return UNSUCCESSFUL_MEMORY_ALLOCATION;
            }
            else if (ec == EMPTY_VECTORS)
                printf(ANSI_COLOR_RED "\nВектора пустые." ANSI_COLOR_RESET);

            time1 = clock();
            if ((ec = sort_list_stacks(list_stack_1, list_stack_2, &list_stack_3)) == SUCCESS)
            {
                time2 = clock();
                printf(ANSI_COLOR_GREEN "\nВремя на сортировку двух стеков в виде списков, используя\n" ANSI_COLOR_RESET);
                printf(ANSI_COLOR_GREEN "дополнительный %ld" ANSI_COLOR_RESET, time2 - time1);
            }
            else if (ec == UNSUCCESSFUL_MEMORY_ALLOCATION)
            {
                printf(ANSI_COLOR_RED "Не удалось выделить память." ANSI_COLOR_RESET);
                free(free_mem_pointers);
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                return UNSUCCESSFUL_MEMORY_ALLOCATION;
            }
            else if (ec == EMPTY_LISTS)
                printf(ANSI_COLOR_RED "\nСписки пустые.\n" ANSI_COLOR_RESET);
        }
        if (choice == 6)
        {
            printf(ANSI_COLOR_MAGENTA "\nСтек 1 на основе вектора\n" ANSI_COLOR_RESET);
            print_vector_stack(vector_stack_1);
            printf(ANSI_COLOR_MAGENTA "\nСтек 2 на основе вектора\n" ANSI_COLOR_RESET);
            print_vector_stack(vector_stack_2);
            printf(ANSI_COLOR_MAGENTA "\nОбъединенный стек на основе вектора\n" ANSI_COLOR_RESET);
            print_vector_stack(vector_stack_3);

            printf(ANSI_COLOR_MAGENTA "\n\nСтек 1 на основе списка\n" ANSI_COLOR_RESET);
            print_list_stack(list_stack_1);
            printf(ANSI_COLOR_MAGENTA "\nСтек 2 на основе списка\n" ANSI_COLOR_RESET);
            print_list_stack(list_stack_2);
            printf(ANSI_COLOR_MAGENTA "\nОбъединенный стек на основе списка\n" ANSI_COLOR_RESET);
            print_list_stack(list_stack_3);

            printf(ANSI_COLOR_GREEN "\n\nP.S. Данные выводятся в обратном порядке.\n" ANSI_COLOR_RESET);

            printf("\n");
        }
        if (choice == 7)
        {
            printf(ANSI_COLOR_MAGENTA "Адреса освобождаемых элементов списка\n" ANSI_COLOR_RESET);
            if (free_mem_pointers_size != 0)
                print_free_mem_pointers(free_mem_pointers, free_mem_pointers_size);
            else
                printf(ANSI_COLOR_YELLOW "Адреса отсутствуют." ANSI_COLOR_RESET);
        }
        if (choice == 8)
        {
            free(free_mem_pointers);
            printf("\n        __________________________________");
            printf("\n        |Размер|   Список   |   Вектор   |");
            printf("\n        |      |            |            |");
            printf("\n        __________________________________");
            for (int stack_size = MAX_STACK_SIZE / (4 * 8); stack_size <= MAX_STACK_SIZE / 4; stack_size += MAX_STACK_SIZE / (4 * 8))
            {
                clock_t time_vector = 0;
                clock_t time_list = 0;
                for (int i = 0; i < MAX_ITER; i++)
                {
                    memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                    if (gen_stack(&list_stack_1, &vector_stack_1, stack_size))
                    {
                        printf(ANSI_COLOR_RED "Не удалось выделить память." ANSI_COLOR_RESET);
                        free(free_mem_pointers);
                        memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                        return UNSUCCESSFUL_MEMORY_ALLOCATION;
                    }
                    if (gen_stack(&list_stack_2, &vector_stack_2, stack_size))
                    {
                        printf(ANSI_COLOR_RED "Не удалось выделить память." ANSI_COLOR_RESET);
                        free(free_mem_pointers);
                        memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                        return UNSUCCESSFUL_MEMORY_ALLOCATION;
                    }

                    uint64_t time1 = clock(), time2;
                    if (sort_list_stacks(list_stack_1, list_stack_2, &list_stack_3) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                    {
                        printf(ANSI_COLOR_RED "Не удалось выделить память." ANSI_COLOR_RESET);
                        free(free_mem_pointers);
                        memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                        return UNSUCCESSFUL_MEMORY_ALLOCATION;
                    }
                    time2 = clock();
                    time_list += time2 - time1;

                    time1 = clock();
                    if (sort_vector_stacks(vector_stack_1, vector_stack_2, &vector_stack_3) == UNSUCCESSFUL_MEMORY_ALLOCATION)
                    {
                        printf(ANSI_COLOR_RED "Не удалось выделить память." ANSI_COLOR_RESET);
                        free(free_mem_pointers);
                        memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
                        return UNSUCCESSFUL_MEMORY_ALLOCATION;
                    }
                    time2 = clock();
                    time_vector += time2 - time1;
                }
                printf("\n        |%6d|%9ld мс|%9ld мс|", stack_size, time_list / MAX_ITER, time_vector / MAX_ITER);
                printf("\n        __________________________________");
                memory_wipe(&list_stack_1, &list_stack_2, &list_stack_3, &vector_stack_1, &vector_stack_2, &vector_stack_3);
            }
        }
        if (choice == 9)
        {
            printf("\n        _____________________________________________________");
            printf("\n        |Размер| Размер данных | Объем памяти | Объем памяти |");
            printf("\n        |стека |    в ячейке   |    списка    |    вектора   |");
            for (int stack_size = MAX_STACK_SIZE / (4 * 8); stack_size <= MAX_STACK_SIZE / 4; stack_size += MAX_STACK_SIZE / (4 * 8))
                for (size_t data_size = 2; data_size < MAX_DATA_SIZE; data_size *= 2)
                {
                    printf("\n        _____________________________________________________");
                    printf("\n        |%6d|%10zu байт|%9zu байт|%9zu байт|", stack_size, data_size, stack_size * (data_size + sizeof(void *)), (long)pow(2, ceil(log2(stack_size))) * data_size + 2 * sizeof(void *));
                }
            printf("\n        _____________________________________________________");
        }
    }
    return SUCCESS;
}