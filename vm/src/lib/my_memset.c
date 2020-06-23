#include <my_lib.h>

void *my_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*cpy;

	if (n == 0)
		return (b);
	i = 0;
	cpy = (unsigned char *)b;
	while (i < n)
	{
		cpy[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
