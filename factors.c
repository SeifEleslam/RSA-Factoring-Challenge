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

void add_one(char *str)
{
    int i;

    for (i = 0; str[i + 1] != '\0';)
        i++;
    str[i] = str[i] < 9 + '0' ? str[i] + 1 : 0;
}

void print_factors(char *str)
{
    char factor1[1024], factor2[1024], rem[1024];
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
    if (strcmp(mpz_get_str(NULL, 10, reminder), "0") == 0)
    {
        printf("%s=%s*%s\n", str, mpz_get_str(NULL, 10, quotient), mpz_get_str(NULL, 10, divisor));
        mpz_clear(dividend), mpz_clear(divisor), mpz_clear(quotient), mpz_clear(reminder), mpz_clear(step);
        return;
    }
    mpz_add(divisor, divisor, step);
    mpz_set_str(step, "2", 10);
    mpz_tdiv_qr(quotient, reminder, dividend, divisor);
    while (strcmp(mpz_get_str(NULL, 10, reminder), "0") != 0)
    {
        mpz_add(divisor, divisor, step);
        mpz_tdiv_qr(quotient, reminder, dividend, divisor);
    }
    printf("%s=%s*%s\n", str, mpz_get_str(NULL, 10, quotient), mpz_get_str(NULL, 10, divisor));
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
    return 0;
}
