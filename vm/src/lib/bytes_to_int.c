#include <my_lib.h>
int bytes_to_int(unsigned char *to_convert, int size)
{
	union
	{
		int integer;
		unsigned char bytes[sizeof(int)];
	} res;

	for (int i = 0; i < sizeof(int); i++)
	{
		if (!size)
		{
			res.bytes[i] = 0;
		}
		else
		{
			res.bytes[i] = to_convert[size - 1];
		}
		size--;
	}

	return res.integer;
}
