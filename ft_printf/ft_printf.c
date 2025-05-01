#include <stdarg.h>
#include <unistd.h>

int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}
int ft_putstr(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (write(1, "(null)", 6));
    while (str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
    return (i);
}

int ft_putnbr(int nb)
{
    long n = nb;
    int i = 0;
    
    if (n < 0)
    {
        i += ft_putchar('-');
        n = -n;
    }
    if (n >= 10)
        i += ft_putnbr(n / 10);
    i += ft_putchar((n % 10) + '0');
    return (i);
}

int ft_puthex(unsigned int nb)
{
    int i;
    char *hex = "0123456789abcdef";
    
    i = 0;
    if (nb >= 16)
        i += ft_puthex(nb / 16);
    i += ft_putchar(hex[nb % 16]);
    return (i);
}

int ft_format(char c, va_list args)
{
    if (c == 's')
        return (ft_putstr(va_arg(args, char *)));
    else if (c == 'd')
        return (ft_putnbr(va_arg(args, int)));
    else if (c == 'x')
        return (ft_puthex(va_arg(args, unsigned int)));
    else if (c == '%')
        return (ft_putchar('%'));
    return (0);
} 

int ft_printf(const char *format, ...)
{
    va_list args;
    int i;
    int len;

    i = 0;
    len = 0;
    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1] != '\0')
        {
            len += ft_format(format[i + 1], args);
            i++;
        }
        else
            len += ft_putchar(format[i]);
        i++;
    }
    va_end(args);
    return (len);
}
