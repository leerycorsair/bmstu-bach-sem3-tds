#include "io_lib.h"

/**
 * @brief Prints a program menu.
 * 
 */
void print_menu(void)
{
    printf(ANSI_COLOR_MAGENTA "\nМеню:\n\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN " 1.Ввести стеки.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN " 2.Сгенерировать стеки автоматически.\n\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN " 3.Добавить элемент в стек.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN " 4.Удалить элемент из стека.\n\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN " 5.Объединить и отсортировать стеки, используя дополнительный.\n\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN " 6.Печать текущего состояния стеков.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN " 7.Печать адресов освобождаемых элементов стека в виде списка.\n\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN " 8.Сравнение времени для обработки\n стеков в разных представлениях.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN " 9.Сравнение памяти для обработки\n стеков в разных представлениях.\n\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN " 0.Завершение программы.\n");
}

/**
 * @brief Prints a welcome message.
 * 
 */
void print_welcome(void)
{
    printf(ANSI_COLOR_MAGENTA "\nДанная программа предназначенна для сравнения преимуществ\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "работы со стеком, представленном в виде списка или вектора.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "\nВ данной программе размер стека ограничен %d элементами\n" ANSI_COLOR_RESET, MAX_STACK_SIZE);
    printf(ANSI_COLOR_YELLOW "\nРазработал: Леонов Владислав ИУ7-36Б\n" ANSI_COLOR_RESET);
}

/**
 * @brief Reads a stack from STDIN.
 * 
 * @param list_stack 
 * @param vector_stack 
 * @return int 
 */
int read_stack(list_stack_t *list_stack, vector_stack_t *vector_stack)
{
    printf(ANSI_COLOR_YELLOW "Введите количество элементов в стеке:" ANSI_COLOR_RESET);
    int size;
    if (scanf("%d", &size) <= 0 || size <= 0)
        return INCORRECT_INPUT;
    if (size > MAX_STACK_SIZE)
    {
        printf(ANSI_COLOR_RED"Превышен максимальный размер стека(%d)", MAX_STACK_SIZE);
        return STACK_OVERFLOW;
    }
    printf(ANSI_COLOR_YELLOW "Вводите элементы (целые числа), разделяя их пробелами:" ANSI_COLOR_RESET);
    for (int i = 0; i < size; i++)
    {
        int value;
        if (scanf("%d", &value) == 0)
            return INCORRECT_INPUT;
        vector_stack_push(vector_stack, value);
    }
    if (form_ls_by_vs(list_stack, *vector_stack))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;

    return SUCCESS;
}

/**
 * @brief Forms a list stack by a vector stack.
 * 
 * @param list_stack 
 * @param vector_stack 
 * @return int 
 */
int form_ls_by_vs(list_stack_t *list_stack, vector_stack_t vector_stack)
{
    for (int i = 0; i < vector_stack.curr_size; i++)
    {
        list_stack_push(list_stack, *vector_stack.pointer_start);
        vector_stack.pointer_start++;
    }
    return SUCCESS;
}

/**
 * @brief Prints the array of deleted elements memory addresses.
 * 
 * @param free_mem_pointers 
 * @param size 
 */
void print_free_mem_pointers(node_t **free_mem_pointers, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%15p ", (void*)free_mem_pointers[i]);
        if ((i + 1) % 5 == 0)
            printf("\n");
    }
}

/**
 * @brief Prints a vector stack in STDOUT.
 * 
 * @param vector_stack 
 */
void print_vector_stack(vector_stack_t vector_stack)
{
    if (vector_stack.curr_size != 0)
        while (vector_stack.pointer_end > vector_stack.pointer_start)
        {
            printf("%d ", *(vector_stack.pointer_end - 1));
            vector_stack.pointer_end--;
        }
    else
        printf(ANSI_COLOR_YELLOW "Стек, на основе вектора, пустой" ANSI_COLOR_RESET);
}

/**
 * @brief Prints a list stack in STDOUT.
 * 
 * @param list_stack 
 */
void print_list_stack(list_stack_t list_stack)
{
    if (list_stack.curr_size != 0)
        for (; list_stack.head; list_stack.head = list_stack.head->next)
            printf("Aдрес "ANSI_COLOR_MAGENTA"%p"ANSI_COLOR_RESET" значение"ANSI_COLOR_MAGENTA"%4d"ANSI_COLOR_RESET"\n", (void*) list_stack.head, list_stack.head->value);
    else
        printf(ANSI_COLOR_YELLOW "Стек, на основе списка, пустой" ANSI_COLOR_RESET);
}
