#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

int _getline(char *line, FILE *fp)
{
    char *ptr;
    int ch;

    ptr = line;
    while ((ch = fgetc(fp)) != EOF && ch != '\n')
        *ptr++ = (char)ch;

    if (ch == EOF)
        return (-1);

    *ptr = '\0';
    return (0);
}

void print_factors(char *str)
{
    char *str_quotient, *str_divisor, *str_reminder;
    mpz_t dividend, divisor, quotient, reminder, step;
    mpz_init(dividend);
    mpz_init(divisor);
    mpz_init(quotient);
    mpz_init(reminder);
    mpz_init(step);

    mpz_set_str(dividend, str, 10);
    mpz_set_str(divisor, "2", 10);
    mpz_set_str(step, "1", 10);
    mpz_tdiv_qr(quotient, reminder, dividend, divisor);
    str_reminder = mpz_get_str(NULL, 10, reminder);
    if (strcmp(str_reminder, "0") == 0)
    {
        free(str_reminder);
        str_quotient = mpz_get_str(NULL, 10, quotient);
        str_divisor = mpz_get_str(NULL, 10, divisor);
        printf("%s=%s*%s\n", str, str_quotient, str_divisor);
        free(str_divisor), free(str_quotient);
        mpz_clear(dividend), mpz_clear(divisor), mpz_clear(quotient), mpz_clear(reminder), mpz_clear(step);
        return;
    }
    free(str_reminder);
    mpz_add(divisor, divisor, step);
    mpz_set_str(step, "2", 10);
    mpz_tdiv_qr(quotient, reminder, dividend, divisor);
    str_reminder = mpz_get_str(NULL, 10, reminder);
    while (strcmp(str_reminder, "0") != 0)
    {
        free(str_reminder);
        mpz_add(divisor, divisor, step);
        mpz_tdiv_qr(quotient, reminder, dividend, divisor);
        str_reminder = mpz_get_str(NULL, 10, reminder);
    }
    free(str_reminder);
    str_quotient = mpz_get_str(NULL, 10, quotient);
    str_divisor = mpz_get_str(NULL, 10, divisor);
    printf("%s=%s*%s\n", str, str_quotient, str_divisor);
    free(str_divisor), free(str_quotient);
    mpz_clear(dividend), mpz_clear(divisor), mpz_clear(quotient), mpz_clear(reminder), mpz_clear(step);
}

int main(int argc, char const *argv[])
{
    FILE *fp;
    unsigned int i;
    size_t n;
    char buff[1024];

    fp = fopen(argv[1], "r");
    while (_getline(buff, fp) != -1)
    {
        print_factors(buff);
    }
    fclose(fp);
    return 0;
}
