#include <my_lib.h>

static int count(int nb)
{
    int count;
    if (!nb)
        return 1;
    else
    {
        count = nb >= 0 ? 0 : 1;
        while (nb)
        {
            count++;
            nb /= 10;
        }
    }

    return (count);
}

char *itoa(int nb)
{
    char *s;
    int i;
    int len = count(nb);

    if (!(s = (char *)malloc(sizeof(char) * (len + 1))))
        return NULL;
    else
    {
        s[len] = '\0';
        i = len - 1;

        if (nb == 0) s[0] = 48;
        if (nb < 0)
        {
            s[i--] = -(nb % 10) + 48;
            s[0] = '-';
            nb = -(nb / 10);
        }

        while (i >= 0 && s[i] != '-')
        {
            s[i--] = nb % 10 + 48;
            nb /= 10;
        }
    }

    return (s);
}