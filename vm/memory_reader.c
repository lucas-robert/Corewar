#include <corewar2.h>

int read_bytes(int size, char *battlefield, int pc)
{
	int res = 0;
	int index = 0;

	while (index < size)
	{
		res = res << 8;
		res |= (unsigned char)battlefield[(pc + index) % MEM_SIZE];
	}

	return res;
}

int get_byte_value(t_vm *machine, t_process *process, int *index, args_type_t type, char modulo)
{
	int res = 0;
	int address;
	switch (type)
	{
		case REG_CODE:
			res = process->registers[read_bytes(T_REG, machine->battlefield, process->pc)];
			*index += T_REG;
			break;
		case DIR_CODE:
			res = read_bytes(T_DIR, machine->battlefield, process->pc);
			*index += T_DIR;
			break;
		case IND_CODE:
		address = read_bytes(T_IND, machine->battlefield, process->pc);
			if (modulo)
			{
				res = read_bytes(T_REG, machine->battlefield, ((process->pc + address % IDX_MOD) % MEM_SIZE));
			}
			else
			{
				res = read_bytes(T_REG, machine->battlefield, ((process->pc + address) % MEM_SIZE));
			}

			*index += T_IND;
			break;
	}
	printf("Memory reader result is: %d", res);
	return res;
}


int get_reg_number(t_vm *machine, t_process *process, int *index, args_type_t type)
{
	if (type != REG_CODE)
		return -1;
	int res = 0;
	res = read_bytes(T_REG, machine->battlefield, process->pc);
	*index += T_REG;
	return res;
}
