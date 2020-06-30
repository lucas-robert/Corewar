char *my_strncpy(char *dest, const char *src, int n)
{
    int index;

    index = 0;
    while (src[index] != '\0' && index != n)
    {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return (dest);
}