#define __USE_MINGW_ANSI_STDIO
#include <stdio.h>

#include "my_real.h"
#include "real_nums_io.h"
#include "multiplication_real_nums.h"
#include "err_codes.h"

int main()
{
    setbuf(stdout, NULL);
    printf("Вас приветствует программа для умножения двух действительных чисел,\nколичество значащих цифр и порядка которых не более 30 и 5 цифр соответственно.\nПеред вводом чисел необходимо ознакомится со следующими правилами ввода:\n1. '+' можно не указывать.\n2. Для разделения целой и дробной части используется символ '.'(точка).\n3. Для обозначения порядка числа используется английские буквы 'e' или 'E',\nпосле которых задается порядок целым числом.\n4. Использование пробелов для логического разделения частей числа запрещено.\n\n");

    char buf1[MAXSTRSIZE + 1];
    char buf2[MAXSTRSIZE + 1];
    int error_code;
    printf("Введите первое число(для завершения ввода используйте клавишу 'ENTER'):\n");
    printf("0--------10--------20--------30\n");
    printf("|--------|---------|---------|\n");
    if (read_line(buf1) || check_str_to_real(buf1))
    {
        printf("К сожалению, Вы сделали ввод с ошибкой.\nПрограмма завершена.");
        return INCORRECT_NUM;
    }

    printf("Введите второе число(для завершения ввода используйте клавишу 'ENTER'):\n");
    printf("0--------10--------20--------30\n");
    printf("|--------|---------|---------|\n");
    if (read_line(buf2) || check_str_to_real(buf2))
    {
        printf("К сожалению, Вы сделали ввод с ошибкой.\nПрограмма завершена.");
        return INCORRECT_NUM;
    }
    if (!is_zero(buf1) || !is_zero(buf2))
    {
        printf("Результат: +0.0E0\n");
        printf("Программа успешно завершена.");
        return SUCCESS;
    }
    my_real_t num1, num2, num3;
    num1 = str_to_real(buf1);
    num2 = str_to_real(buf2);
    if (!(error_code = multi_reals(num1, num2, &num3)) || error_code == ZERO_NUM)
    {
        printf("Результат:\n");
        if (error_code == ZERO_NUM)
            printf("0");
        else
            print_my_real(num3);
        printf("\nПрограмма успешно завершена.");
        return SUCCESS;
    }
    else if (error_code)
    {
        printf("\nРезультат умножения выходит за пределы допустимых значений.\nПрограмма завершена.");
        return error_code;
    }
}