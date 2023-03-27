#include "real_nums_io.h"

int print_my_real(my_real_t num)
{
    printf("%c0.", num.num_sign);
    for (size_t i = 0; i < num.mantisse_size; i++)
        printf("%d", num.mantisse[i]);
    printf("E%d", num.exp);
    return SUCCESS;
}

int read_line(char *str)
{
    int ch, i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF && ch != '\0' && i < MAXSTRSIZE)
    {
        str[i] = ch;
        i++;
    }
    if (((ch == '\n' || ch == EOF || ch == '\0') && i == 0) || i == MAXSTRSIZE)
        return READING_ERROR;
    else
    {
        str[i] = '\0';
        return SUCCESS;
    }
}

int check_str_to_real(char *str)
{
    int dot_check = 0, e_check = 0, plus_minus_check = 0;
    for (size_t i = 0; str[i]; i++)
    {
        if ((str[i] > '9' || str[i] < '0') && str[i] != '+' && str[i] != '-' && str[i] != 'e' && str[i] != 'E' && str[i] != '.')
            return INCORRECT_NUM;
        if (str[i] == '.')
            dot_check += 1;
        if (str[i] == '+' || str[i] == '-')
            plus_minus_check += 1;
        if (str[i] == 'e' || str[i] == 'E')
            e_check += 1;
        if ((dot_check > 1 || e_check > 1) || (plus_minus_check > 1 && e_check == 0) || (str[i] == '.' && e_check == 1) || ((str[i] == '+' || str[i] == '-') && dot_check == 1 && e_check == 0) || ((str[i] == '+' || str[i] == '-') && (('0' <= str[i - 1] && str[i - 1] <= '9') || str[i - 1] == '.')))
            return INCORRECT_NUM;
        if (i > 1 && (str[i] == 'e' || str[i] == 'E') && str[i - 1] == '.')
            return INCORRECT_NUM;
    }
    if (((str[0] == '+' || str[0] == '-') && (str[1] == 'e' || str[1] == 'E')) || (str[0] == 'e' || str[0] == 'E') || strcmp(str, ".") == 0 || (str[strlen(str) - 1] == 'e' || str[strlen(str) - 1] == 'E' || str[strlen(str) - 1] == '-' || str[strlen(str) - 1] == '+'))
        return INCORRECT_NUM;
    size_t mantisse_nums = 0, exp_nums = 0, e_check1 = 0;
    for (size_t i = 0; str[i]; i++)
    {
        if (isdigit(str[i]) && e_check1 == 0)
            mantisse_nums += 1;
        if (str[i] == 'e' || str[i] == 'E')
            e_check1 = 1;
        if (isdigit(str[i]) && e_check1 == 1)
            exp_nums += 1;
    }
    if (mantisse_nums > 30 || exp_nums > 5)
        return INCORRECT_NUM;
    return SUCCESS;
}

my_real_t str_to_real(char *str)
{
    my_real_t tmp;
    char num_sign = '+';
    int e_check = 0, exp_sign = 1;
    tmp.exp = 0;
    int expon = 0;
    size_t mantise_i = 0, dot_check = 0, f_digit = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (str[i] == '-' && e_check == 0)
            num_sign = str[i];
        if (str[i] == 'e' || (str[i]) == 'E')
            e_check = 1;
        if ((str[i] == '-') && e_check == 1)
            exp_sign = -1;
        if (isdigit(str[i]) && e_check == 1)
            expon = expon * 10 + (str[i] - '0');
        if (isdigit(str[i]) && e_check == 0)
        {
            if (str[i] != '0' || dot_check == 1)
                f_digit = 1;
            if (f_digit == 1)
            {
                tmp.mantisse[mantise_i] = (str[i] - '0');
                mantise_i += 1;
                if (dot_check == 0)
                    tmp.exp += 1;
            }
        }
        if (str[i] == '.')
            dot_check = 1;
    }

    tmp.num_sign = num_sign;
    tmp.exp = tmp.exp + expon * exp_sign;
    tmp.mantisse_size = mantise_i;
    for (int i = 0; tmp.mantisse[i] == 0; i++)
    {
        for (size_t j = i; j < tmp.mantisse_size - 1; j++)
            tmp.mantisse[j] = tmp.mantisse[j + 1];
        tmp.mantisse_size -= 1;
        tmp.exp -= 1;
        i--;
    }
    return tmp;
}

int is_zero(char *str)
{
    int e_check = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (isdigit(str[i]) && str[i] != '0' && e_check == 0)
            return -1;
        if (str[i] == 'e' || str[i] == 'E')
            e_check = 1;
    }
    return 0;
}
