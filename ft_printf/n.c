#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
int ft_putchar(char c)
{
    write(1, &c ,1);
    return (1);
}
int ft_putstr(char *str)
{
    int i;

    i = 0;
    if (!str)
        return(write(1, "(null)", 6));
    while (str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
    return (i);
}

int ft_putnbr(int nb)
{
    int i;

    i = 0;
    if (nb == -2147483648)
    {
        i += ft_putchar('-');
        i += ft_putchar('2');
        nb = 147483648;
    }
    if (nb < 0)
    {
        i += ft_putchar('-');
        nb = -nb;
    }
    if (nb > 10)
    {
        i += ft_putnbr(nb / 10);
        nb = nb % 10;
    }
    if (nb < 10)
        i += ft_putchar(nb + '0');
    return(i);
}

int ft_puthex(unsigned long long nb)
{
    char *digit;
    int i;

    i = 0;
    digit = "0123456789abcdef";
    if (nb > 16)
        ft_puthex(nb / 16);
    i += ft_putchar(digit[nb % 16]);
    return(i);
}

int ft_format(char c, va_list args)
{
    if (c == 's')
        return(ft_putstr(va_arg(args, char *)));
    else if(c == 'd')
        return(ft_putnbr(va_arg(args, int)));
    else if(c == 'x')
        return(ft_puthex(va_arg(args, long long)));
    else if(c == '%')
        return(ft_putchar('%'));
    return (0);
}

int ft_printf(const char * format, ... )
{
    int len;
    int i;
    va_list args;

    i = 0;
    len = 0;
    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1] != '\0')
            len += ft_format(format[i + 1], args);
        else
            len += ft_putchar(format[i]);
        i++;
    }
    va_end(args);
    return (len);
}


static void	ft_string_tests(void)
{
	int	return_ft_printf;
	int	return_printf;

	printf("Test 1: Simple string\n");
	return_ft_printf = ft_printf("Hello, World!\n");
	return_printf = printf("Hello, World!\n");
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
	printf("Test 2: String with %%s specifier\n");
	return_ft_printf = ft_printf("This is a %s.\n", "string");
	return_printf = printf("This is a %s.\n", "string");
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
}

static void	ft_numeric_tests(void)
{
	int	return_ft_printf;
	int	return_printf;

	printf("Test 3: Integer with %%d specifier\n");
	return_ft_printf = ft_printf("The answer is %d.\n", 42);
	return_printf = printf("The answer is %d.\n", 42);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
	printf("Test 4: Hexadecimal with %%x specifier\n");
	return_ft_printf = ft_printf("The value is %x.\n", 255);
	return_printf = printf("The value is %x.\n", 255);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
	printf("Test 5: Multiple specifiers\n");
	return_ft_printf = ft_printf("String: %s, Integer: %d, Hex: %x\n", \
			"test", 123, 0xabc);
	return_printf = printf("String: %s, Integer: %d, Hex: %x\n", \
			"test", 123, 0xabc);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
}

static void	ft_special_cases(void)
{
	int		return_ft_printf;
	int		return_printf;
	char	*null_string;

	null_string = NULL;
	printf("Test 6: Null string\n");
	return_ft_printf = ft_printf("Null string: %s\n", null_string);
	return_printf = printf("Null string: %s\n", null_string);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
	printf("Test 7: Percent sign\n");
	return_ft_printf = ft_printf("Print a percent sign: %%\n");
	return_printf = printf("Print a percent sign: %%\n");
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
}

static void	ft_edge_case_tests(void)
{
	int	return_ft_printf;
	int	return_printf;

	printf("Test 8: Maximum and minimum integers\n");
	return_ft_printf = ft_printf("INT_MAX: %d, INT_MIN: %d\n", \
			INT_MAX, INT_MIN);
	return_printf = printf("INT_MAX: %d, INT_MIN: %d\n", \
			INT_MAX, INT_MIN);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
	printf("Test 9: UINT_MAX with %%x\n");
	return_ft_printf = ft_printf("UINT_MAX in hex: %x\n", UINT_MAX);
	return_printf = printf("UINT_MAX in hex: %x\n", UINT_MAX);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
}

static void	ft_check_ft_printf(void)
{
	ft_printf("Testing ft_printf Started.\n");
	ft_string_tests();
	ft_numeric_tests();
	ft_special_cases();
	ft_edge_case_tests();
	ft_printf("Testing ft_printf complete.\n");
}

int	main(int argc, char **argv)
{
	ft_check_ft_printf();
	return (EXIT_SUCCESS);
}