int my_strlen(char *str)
{
    int i = 0;
    if (str)
    {
        while (str[i]) i++;
    }

    return i;
}