#include <my_lib.h>

static int my_pow(int a, int b)
{
    if (b <= 0)
    {
        return 1;
    }
    int s = a;
    for (int i = 1; i < b; i++)
    {
        s *= a;
    }
    return s;
}

int my_atoi(char* a)
{
    int r;
    int l;
    int n;

    r = 0;
    l = 0;
    n = 1;
    int i = 0;
    if (a[0] == '-')
    {
        n = -1;
        i++;
    }
    for (; i < my_strlen(a); i++)
    {
        if (!(a[i] >= 48 && a[i] <= 57)) break;
        l++;
    }
    if (l <= 0) return 0;
    i = 0;
    int m = l;
    if (n == -1)
    {
        i++;
        l++;
    }
    for (; i < l; i++)
    {
        r += (a[i] - 48) * my_pow(10, m - 1);
        m--;
    }
    return r * n;
}
