#include <corewar2.h>

int is_in_pc(int *pc, int len, int check)
{
	for (int i = 0; i < len; i++)
	{
		if (pc[i] == check)
			return 1;
	}
	return 0;
}

void print_memory(t_vm *machine)
{
	for (int line = 0; line < MEM_SIZE / BYTES_PER_LINE; line++)
	{
		printf("0x%.4x : ", line * BYTES_PER_LINE);
		for (int row = 0; row < BYTES_PER_LINE; row ++)
		{
			printf("%.2x ", machine->battlefield[line * BYTES_PER_LINE + row]);
		}
		printf("\n");
	}
	return;
}
