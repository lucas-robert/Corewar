#include <corewar2.h>

int read_bytes(int size, unsigned char *battlefield, int pc)
{

	union {
		int integer;
		char bytes[4];
	} bytes_reader;


	bytes_reader.integer = 0;
	int i = size;
	printf("Reading %d bytes => ", size);
	while(i)
	{
		i--;
		printf("%.2x ", battlefield[pc + (size - i - 1)]);
		bytes_reader.bytes[i] = battlefield[pc + (size - i - 1)];
	}
	printf(" \n");
	return bytes_reader.integer;
}

int get_byte_value(t_vm *machine, t_process *process, int *index, args_type_t type, char modulo)
{
	int res = 0;
	int address;
	switch (type)
	{
		case REG_CODE:
			res = process->registers[read_bytes(T_REG, machine->battlefield, (process->pc + *index) % MEM_SIZE)];
			*index += 1;
			break;
		case DIR_CODE:
			res = read_bytes(4, machine->battlefield, (process->pc + *index) % MEM_SIZE);
			*index += 4;
			break;
		case IND_CODE:
		address = read_bytes(T_IND, machine->battlefield, (process->pc + *index) % MEM_SIZE);
			if (modulo)
			{
				res = read_bytes(T_REG, machine->battlefield, ((process->pc + address % IDX_MOD) % MEM_SIZE));
			}
			else
			{
				res = read_bytes(T_REG, machine->battlefield, ((process->pc + address) % MEM_SIZE));
			}

			*index += 2;
			break;
	}
	printf("Memory reader result is: %d\n", res);
	return res;
}


int get_reg_number(t_vm *machine, t_process *process, int *index, args_type_t type)
{
	int res = 0;
	res = read_bytes(T_REG, machine->battlefield, (process->pc + *index) % MEM_SIZE);
	*index += T_REG;
	printf("Reg number is %d\n", res);
	return res;
}
