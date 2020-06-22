#include <my_lib.h>

static int pow(int a, int b)
{
    int res = 1;
    for (int i = 0; i != b; i++)
    {
        res = res * a;
    }
    return res;
}


int my_hex_to_dec(int hex)
{
    int dec = 0;
    int i = 0;

    while (hex != 0)
    {
        dec += (hex % 10) * pow(16, i);
        i++;
        hex /= 10;
    }
    return dec;
}
