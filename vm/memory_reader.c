#include <corewar2.h>

int get_byte_value(t_vm *machine, t_process *process, int *index, args_type_t type)
{
	int res = 0;
	switch (type)
	{
		case REG_CODE:
			res = bytes_to_int(&machine->battlefield[(process->id + *index) % MEM_SIZE], REG_SIZE);
			*index += REG_SIZE;
			break;
		case DIR_CODE:
			res = bytes_to_int(&machine->battlefield[(process->id + *index) % MEM_SIZE], DIR_SIZE);
			*index += DIR_SIZE;
			break;
		case IND_CODE:
			res = bytes_to_int(&machine->battlefield[(process->id + *index) % MEM_SIZE], IND_CODE);
			*index += IND_SIZE;
			break;
	}
	return res;
}
