#include "io_lib.h"

#include <stdlib.h>

void print_menu(void)
{
    printf(ANSI_COLOR_YELLOW "\nМеню:\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_MAGENTA "== Работа с хранилищем данных ==\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "10. Выполнить чтение данных из файла.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "11. Выполнить поиск данных в файле.\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_MAGENTA "\n== Работа с двоичным деревом поиска ==\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "20. Сформировать дерево на основе прочитанных данных.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "21. Добавить элемент.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "22. Удалить элемент.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "23. Выполнить поиск элемента.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "24. Печать текущего состояния дерева в файл GraphViz.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "25. Печать объема памяти.\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_MAGENTA "\n== Работа со сбалансированным деревом поиска ==\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "30. Сформировать дерево на основе прочитанных данных.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "31. Добавить элемент.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "32. Удалить элемент.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "33. Выполнить поиск элемента.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "34. Печать текущего состояния дерева в файл GraphViz.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "35. Печать объема памяти.\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_MAGENTA "\n== Работа со хеш-таблицей ==\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "40. Сформировать хеш-таблицу на основе прочитанных данных.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "41. Устранить коллизии.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "42. Добавить элемент.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "43. Удалить элемент.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "44. Выполнить поиск элемента.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "45. Печать текущего состояния хеш-таблицы.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "46. Печать объема памяти.\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_GREEN "\n50. Сравнительный анализ структур.\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_GREEN "\n0. Завершить работу.\n");
}
void print_welcome(void)
{
    printf(ANSI_COLOR_MAGENTA "\nВас приветствует программа для работы с двоичными\n");
    printf("деревьями поиска, сбалансированными двоичными деревьями\n");
    printf("и хэш-таблицами для указанных данных.\n\n");
    printf("Время для операций указывается в тактах процессора.\n" ANSI_COLOR_RESET);
}

// int read_line(FILE *file, char **s)
// {
//     int ch;
//     int curr_size = 20;
//     *s = NULL;
//     char *tmp = realloc(*s, sizeof(char) * curr_size);
//     if (tmp == NULL)
//         return UNSUCCESSFUL_MEMORY_ALLOCATION;
//     *s = tmp;
//     int i = 0;
//     while ((ch = fgetc(file)) != '\n' && ch != EOF)
//     {
//         (*s)[i++] = ch;
//         if (i == curr_size - 1)
//         {
//             char *tmp = realloc(*s, sizeof(char) * curr_size * 2);
//             if (tmp == NULL)
//                 return UNSUCCESSFUL_MEMORY_ALLOCATION;
//             *s = tmp;
//             curr_size *= 2;
//         }
//     }
//     if (ch != '\n' && ch != EOF && i > 0)
//         return INCORRECT_CONTENT;
//     (*s)[i] = '\0';
//     return i;
// }
