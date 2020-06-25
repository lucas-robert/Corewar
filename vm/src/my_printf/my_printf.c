#include <my_lib.h>

char re_val(long long num)
{
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'a');
}

void strev(char *str)
{
    int len;
    int i;

    len = my_strlen(str);
    for (i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

char *lltob(char *res, int base, long long inputNum)
{
    int index;
    int negative;

    index = 0;
    negative = 0;
    if (inputNum == 0)
    {
        res[index] = '0';
        res[index + 1] = '\0';
        return res;
    }
    else if (inputNum < 0)
    {
        inputNum = -inputNum;
        negative = 1;
    }
    while (inputNum > 0)
    {
        res[index++] = re_val(inputNum % base);
        inputNum /= base;
    }
    if (negative) res[index++] = '-';
    res[index] = '\0';
    strev(res);
    return res;
}

int is_flag(char c)
{
    if (c == 'd' || c == 'o' || c == 'u' || c == 'x' || c == 'c' || c == 's' ||
        c == 'p')
        return 1;
    return 0;
}

int parse_flag(char *fmt, char *flag)
{
    if (!fmt || !*fmt) return -1;
    for (int i = 0; i < my_strlen(fmt); i++)
    {
        if (is_flag(fmt[i]))
        {
            *flag = fmt[i];
            return i + 1;
        }
    }
    return -1;
}

int format(char *flag, va_list args)
{
    int i;
    int d;
    unsigned int ouxp;
    char buff[256];

    i = 0;
    if (*flag == 'c')
    {
        char c = va_arg(args, int);
        buff[0] = c;
        buff[1] = '\0';
    }
    else if (*flag == 'd')
    {
        d = va_arg(args, int);
        lltob(buff, 10, d);
    }
    else if (*flag == 'o')
    {
        ouxp = (unsigned int)va_arg(args, unsigned int);
        lltob(buff, 8, ouxp);
    }
    else if (*flag == 'u')
    {
        ouxp = (unsigned int)va_arg(args, unsigned int);
        lltob(buff, 10, ouxp);
    }
    else if (*flag == 'x')
    {
        ouxp = (unsigned int)va_arg(args, unsigned int);
        lltob(buff, 16, ouxp);
    }
    else if (*flag == 'p')
    {
        long long int f = va_arg(args, long long);
        write(1, "0x", 2);
        i += 2;
        lltob(buff, 16, f);
    }
    else if (*flag == 's')
    {
        char *s = va_arg(args, char *);
        i = my_strlen(s);
        write(1, s, i);
        return i;
    }

    i += my_strlen(buff);
    write(1, buff, my_strlen(buff));
    return i;
}

int my_printf(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int tmp;
    int len;
    char flag;

    len = 0;
    tmp = -1;
    for (int i = 0; i < my_strlen(fmt); i++)
    {
        if (fmt[i] == '%')
        {
            tmp = parse_flag(&fmt[i + 1], &flag);
            if (tmp == -1) return len;
            i += tmp;
            len += format(&flag, args);
            flag = 0;
        }
        else
        {
            write(1, &fmt[i], 1);
            len++;
        }
    }
    va_end(args);
    return len;
}
