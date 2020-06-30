#include <my_lib.h>

static int end_of(char const *s, int len)
{
    while (s[len] == '\t' || s[len] == '\n' || s[len] == ' ')
    {
        len--;
    }
    return (len);
}

static int start(char const *s, int end)
{
    int q;

    q = 0;
    while (q < end && (*s == '\t' || *s == ' ' || *s == '\n'))
    {
        q++;
        s++;
    }
    return (q);
}

char *my_strip(char *s)
{
    int len;
    int st;
    int end;
    unsigned char *c;
    int i;

    if (!s) return (NULL);
    i = 0;
    len = my_strlen(s);
    end = end_of(s, len - 1);
    st = start(s, end);
    c = (unsigned char *)malloc(sizeof(char) * (end - st) + 2);
    if (!c) return (NULL);
    while (i <= (end - st))
    {
        c[i] = (unsigned char)s[st + i];
        i++;
    }
    c[i] = '\0';
    return ((char *)c);
}