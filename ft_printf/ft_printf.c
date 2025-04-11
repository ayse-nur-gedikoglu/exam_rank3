#include <unistd.h>
#include <stdarg.h>

int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

int ft_putstr(char *str)
{
    int i = 0;
    
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
    int i = 0;
    
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
    if (nb > 9)
    {
        i += ft_putnbr(nb / 10);
        nb = nb % 10;
    }
    i += ft_putchar(nb + '0');
    return (i);
}

int ft_puthex(unsigned int nb)
{
    char *hex = "0123456789abcdef";
    int i = 0;
    
    if (nb >= 16)
        i += ft_puthex(nb / 16);
    i += ft_putchar(hex[nb % 16]);
    return (i);
}

int ft_format(char c, va_list arg)
{
    if (c == 's')
        return (ft_putstr(va_arg(arg, char *)));
    else if (c == 'd')
        return (ft_putnbr(va_arg(arg, int)));
    else if (c == 'x')
        return (ft_puthex(va_arg(arg, unsigned int)));
    else if (c == '%')
        return (ft_putchar('%'));
    return (0);
}

int ft_printf(const char *str, ...)
{
    int len = 0;
    int i = 0;
    va_list arg;
    
    va_start(arg, str);
    while (str[i])
    {
        if (str[i] == '%' && str[i + 1])
        {
            len += ft_format(str[i + 1], arg);
            i++;
        }
        else
            len += ft_putchar(str[i]);
        i++;
    }
    va_end(arg);
    return (len);
}