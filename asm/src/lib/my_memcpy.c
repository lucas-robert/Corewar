#include <my_lib.h>

void *my_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (n == 0 || dest == src)
		return (dest);
	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	while (--n)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = *s2;
	return (dest);
}
