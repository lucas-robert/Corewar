#include <corewar2.h>

void print_memory(char *battlefield)
{
	for (int line = 0; line < MEM_SIZE / BYTES_PER_LINE; line++)
	{
		for (int row = 0; row < BYTES_PER_LINE; row ++)
		{
			union
			{
				int integer;
				char bytes[sizeof(int)];
			} bytes_printer;
			bytes_printer.integer = bytes_to_int(&battlefield[line * BYTES_PER_LINE + row], 4);
			if (bytes_printer.integer)
			{
				printf("\033[0;31m");
			}
			for (int i = 0; i < (int)sizeof(int); i++)
			{
				printf("%.2x ", bytes_printer.bytes[i]);
			}
			printf("\033[0m");
		}
		printf("\n");
	}
	return ;
}
