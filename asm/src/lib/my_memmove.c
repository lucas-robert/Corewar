#include <my_lib.h>

void *my_memmove(void *dest, const void *src, size_t n)
{
	unsigned char			*cpy;
	unsigned char			*cpy2;

	cpy = (unsigned char *)dest;
	cpy2 = (unsigned char *)src;
	if (!n)
		return (dest);
	if (dest <= src)
		return (my_memcpy(dest, src, n));
	while (n--)
		cpy[n] = cpy2[n];
	return (dest);
}
