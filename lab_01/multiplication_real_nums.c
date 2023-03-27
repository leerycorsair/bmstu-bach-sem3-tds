#include "multiplication_real_nums.h"
#include "err_codes.h"

int multi_reals(my_real_t num1, my_real_t num2, my_real_t *res)
{
    if (num1.mantisse_size < num2.mantisse_size)
    {
        my_real_t tmp;
        tmp = num1;
        num1 = num2;
        num2 = tmp;
    }
    if (num1.num_sign != num2.num_sign)
        (res->num_sign) = '-';
    else
        (res->num_sign) = '+';

    res->mantisse_size = 0;
    res->exp = num1.exp + num2.exp;
    int matrix[MAX_MANTISSE][MAX_MANTISSE * 2];
    for (size_t i = 0; i < MAX_MANTISSE; i++)
        for (size_t j = 0; j < MAX_MANTISSE * 2; j++)
            matrix[i][j] = 0;
    int mod;
    for (int i = num2.mantisse_size - 1; i > -1; i--)
    {
        mod = 0;
        for (int j = num1.mantisse_size - 1; j > -1; j--)
        {
            matrix[num2.mantisse_size - i - 1][2 * MAX_MANTISSE - num1.mantisse_size + j - (num2.mantisse_size - i - 1)] = (num2.mantisse[i] * num1.mantisse[j] + mod) % 10;
            mod = (num2.mantisse[i] * num1.mantisse[j] + mod) / 10;
            if (j == 0)
                matrix[num2.mantisse_size - i - 1][2 * MAX_MANTISSE - num1.mantisse_size + j - (num2.mantisse_size - i)] = mod;
        }
    }
    mod = 0;
    int sum;
    int result[MAX_MANTISSE * 2];
    for (size_t j = 0; j < MAX_MANTISSE * 2; j++)
        result[j] = 0;
    for (int i = MAX_MANTISSE * 2 - 1; i > -1; i--)
    {
        sum = 0;
        for (size_t j = 0; j < num1.mantisse_size; j++)
            sum += matrix[j][i];
        result[i] = (sum + mod) % 10;
        mod = (sum + mod) / 10;
    }

    int index = 2 * MAX_MANTISSE - num1.mantisse_size - num2.mantisse_size;
    while (result[index] == 0)
    {
        res->exp -= 1;
        index += 1;
    }
    while (res->mantisse_size < MAX_MANTISSE && index < 2 * MAX_MANTISSE)
    {
        if (res->mantisse_size != MAX_MANTISSE - 1 || (index == 2 * MAX_MANTISSE - 1 && res->mantisse_size == MAX_MANTISSE - 1))
        {
            res->mantisse[res->mantisse_size] = result[index];
            res->mantisse_size += 1;
            index += 1;
        }
        else
        {
            if (result[index + 1] < 5)
            {
                res->mantisse[res->mantisse_size] = result[index];
                res->mantisse_size += 1;
            }
            else

            {
                res->mantisse[res->mantisse_size] = (result[index] + 1) % 10;
                int divid = (result[index] + 1) / 10;
                for (int j = res->mantisse_size - 1; j > -1 && divid > 0; j--)
                {
                    int tmp = res->mantisse[j];
                    res->mantisse[j] = (res->mantisse[j] + divid) % 10;
                    divid = (tmp + divid) / 10;
                    if (j == 0 && divid == 1)
                    {
                        res->mantisse[0] = 1;
                        res->mantisse_size = 1;
                        res->exp += 1;
                    }
                }
                if (res->mantisse_size != 1 && res->mantisse[0] != 1)
                    res->mantisse_size += 1;
            }
            if (res->exp >= MIN_EXP && res->exp <= MAX_EXP)
                return SUCCESS;
            else
                return NUM_OVERFLOW;
        }
    }
    if (res->exp >= MIN_EXP && res->exp <= MAX_EXP)
        return SUCCESS;
    else
        return NUM_OVERFLOW;
}