
#define __USE_MINGW_ANSI_STDIO
#include <stdio.h>
#include "err_codes.h"
#include "show_t.h"
#include "repertuar_handling.h"

void print_menu()
{
    printf("%s", "\n\n============================================================================================\n\n");

    printf("%s", "      Меню:\n\n");
    printf("%s", "      1  - Выполнить чтение таблицы репертуара театров из файла\n");
    printf("%s", "      2  - Очистить таблицу репертуара\n\n");
    printf("%s", "      3  - Добавить запись в таблицу репертуара\n");
    printf("%s", "      4  - Удалить запись из таблицы репертуара\n\n");
    printf("%s", "      5  - Печать текущей таблицы репертуара, без использования таблицы ключей\n");
    printf("%s", "      6  - Печать текущей таблицы репертуара, с использованием таблицы ключей\n");
    printf("%s", "      7  - Печать текущей таблицы ключей (поле - название спектакля)\n\n");
    printf("%s", "      8  - Сортировка таблицы репертуара по названию\n");
    printf("%s", "      9  - Сортировка таблицы ключей (поле - название спектакля)\n");
    printf("%s", "      10 - Сравнение эффективности сортировки таблицы репертуара и таблицы ключей,\n");
    printf("%s", "           используя алгоритмы быстрой сортировки и сортировку пузырьком\n\n");
    printf("%s", "      11 - Вывести список всех музыкальных спектаклей для детей указанного возраста,\n");
    printf("%s", "           c продолжительностью меньше указанной\n\n");
    printf("%s", "      12 - Справка\n\n");
    printf("%s", "      13 - Об авторе\n\n");
    printf("%s", "      0  - Завершить работу программы\n");

    printf("%s", "\n\n============================================================================================\n\n");
}

void about_author()
{
    printf("\n        Данная программа выполнена Леоновым Владиславом в рамках\n        учебного курса 'Типы и структуры данных'");
}

void print_help()
{
    printf("\n        Cправка:\n");
    printf("\n        1. При чтении данных их файла предполагается, что\n        каждое поле таблицы начинается с новой строки и\n        ввод данных происходит аналогично производимому\n        непосредственно в программе.\n");
    printf("\n        2. Максимально допустимая длинна полей слов - 64 символа.\n");
    printf("\n        3. Максимально в таблице может быть не болле 100 строк.\n");
    printf("\n        4. Готовая таблица репертуара может быть загружена\n        из файла repertuar.txt");
}

int main()
{
    setbuf(stdout, NULL);
    int e_c = SUCCESS, menu_option;
    char file_name[MAX_STR_SIZE];
    FILE *f;
    show_t repertuar[MAX_REP_RECS];
    key_t key_rep[MAX_REP_RECS];
    size_t repertuar_size = 0;
    while (e_c == SUCCESS)
    {

        print_menu();
        printf("\n        Выберите опцию меню: ");
        if (scanf("%d", &menu_option) <= 0)
        {
            printf("\n        Некорректный ввод. Программа аварийно завершена.\n\n");
            e_c = INCORRECT_MENU_OPTION;
            return e_c;
        }
        if (menu_option == 0)
        {
            save_curr_table(repertuar, repertuar_size);
            printf("\n        Программа успешно завершена.Текущая таблица сохранена в файле out.txt\n\n");
            return e_c;
        }
        else if (menu_option == 1)
        {
            printf("\n        Введите название файла:");
            if (scanf("%s", file_name) <= 0 || strlen(file_name) == 0 || (f = fopen(file_name, "r")) == NULL)
            {
                printf("\n        Некорректное название файла. Программа аварийно завершена.\n\n");
                e_c = INCORRECT_FILE_NAME;
                return e_c;
            }
            if ((e_c = fread_repertuar(f, repertuar, &repertuar_size, key_rep) != SUCCESS))
            {
                printf("\n        Некорректное содержимое файла. Программа аварийно завершена.\n\n");
                return e_c;
            }
        }
        else if (menu_option == 2)
        {
            printf("\n        Данные успешно очищены.");
            repertuar_size = 0;
        }
        else if (menu_option == 3)
        {
            if ((e_c = repertuar_add_rec(repertuar, &repertuar_size, key_rep) != SUCCESS))
            {
                printf("\n        Некорректный ввод. Программа аварийно завершена.\n\n");
                return e_c;
            }
        }
        else if (menu_option == 4)
        {
            if ((e_c = repertuar_del_rec(repertuar, &repertuar_size, key_rep) != SUCCESS))
            {
                printf("\n        Некорректный ввод. Программа аварийно завершена.\n\n");
                return e_c;
            }
        }
        else if (menu_option == 5)
        {
            print_rep_no_key(repertuar, repertuar_size);
        }
        else if (menu_option == 6)
        {
            print_rep_with_key(repertuar, repertuar_size, key_rep);
        }
        else if (menu_option == 7)
        {
            print_rep_key(key_rep, repertuar_size);
        }
        else if (menu_option == 8)
        {
            sort_rep(repertuar, repertuar_size, key_rep);
            printf("\n        Функция сортировки таблицы репертуара завершена.\n");
        }
        else if (menu_option == 9)
        {
            sort_key(key_rep, repertuar_size);
            printf("\n        Функция сортировки таблицы ключей завершена.\n");
        }
        else if (menu_option == 10)
        {
            cmp_sorts(repertuar, repertuar_size, key_rep);
        }
        else if (menu_option == 11)
        {
            if ((e_c = shows_for_kids(repertuar, repertuar_size) != SUCCESS))
            {
                printf("\n        Некорректный ввод. Программа аварийно завершена.\n\n");
                return e_c;
            }
        }
        else if (menu_option == 12)
        {
            print_help();
        }
        else if (menu_option == 13)
        {
            about_author();
        }
        else
        {
            printf("\n        Неизвестный пункт меню. Программа аварийно завершена.\n\n");
            return INCORRECT_MENU_OPTION;
        }
    }
}
