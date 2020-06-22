#include <my_lib.h>
int		my_n_atoi_base(char *str, int len, int base)
{
	int nb;
	int sign;
	int i;

	i = 0;
	nb = 0;
	while(i < len)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			nb = nb * base + (str[i] - '0');
		}
		else if (str[i] >= 'a' && str[i] <= 'f')
		{
			nb = nb * base + (str[i] - 'a');
		}
		else if (str[i] >= 'A' && str[i] <= 'F')
		{
			nb = nb * base + (str[i] - 'A');
		}
		i++;
	}
	return ((int)nb);
}
