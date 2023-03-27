#include "io_lib.h"

#include <stdlib.h>

void print_menu(void)
{
    printf(ANSI_COLOR_YELLOW "\nМеню:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "1. Чтение данных из файла.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "2. Печать исходных данных в графическое представление.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "3. Поиск пути проходящего через каждую из дорог системы 1 раз.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "4. Сравнительный анализ структур.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "0. Завершить работу.\n"ANSI_COLOR_RESET);
}
void print_welcome(void)
{
    printf(ANSI_COLOR_MAGENTA "\nВас приветствует программа для работы с неориентированными\n");
    printf("графами. Для заданной системы двусторонних дорог выполняется\n");
    printf("поиск пути проходящего через каждую из дорог системы 1 раз.\n\n");
    printf("Время для операций указывается в тактах процессора.\n" ANSI_COLOR_RESET);
}