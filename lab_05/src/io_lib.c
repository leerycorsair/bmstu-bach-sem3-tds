#include "io_lib.h"

void print_menu(void)
{
    printf(ANSI_COLOR_YELLOW "\nМеню:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "1. Выполнить моделирование.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "2. Изменить параметры моделирование.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "3. Выполнить печать адресов памяти очереди.\n");
    printf(ANSI_COLOR_GREEN "4. Об авторе.\n");
    printf(ANSI_COLOR_GREEN "0. Завершить работу.\n");
}
void print_welcome(void)
{
    printf(ANSI_COLOR_MAGENTA "\nВас приветствует программа для моделирования обработки\n");
    printf("1000 заявок очереди, используя односвязный список и\n");
    printf("статический массив для ее построения.\n" ANSI_COLOR_RESET);
}

void print_author(void)
{
    printf(ANSI_COLOR_MAGENTA"\nФИО: Леонов Владислав Вячеславович\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA"Группа: ИУ7-36Б\n"ANSI_COLOR_RESET);
}
