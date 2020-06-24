#include <corewar2.h>

static const int SIGN_MASK[3] = {0xffffff00, 0xffff0000, 0xff000000};

int read_bytes(int size, unsigned char *battlefield, int pc)
{
	union {
		int integer;
		unsigned char bytes[4];
	} bytes_reader;

	bytes_reader.integer = 0;
	int i = size;
	// printf("Reading %d bytes => ", size);
	while(i)
	{
		i--;
		// printf("%.2x ", (unsigned char)battlefield[pc + (size - i)]);
		bytes_reader.bytes[i] = battlefield[pc + (size - i - 1)];
	}
	// printf(" \n");
	// sign
	if (bytes_reader.integer >> (7 + 8 *(size - 1)) == 1)
		bytes_reader.integer |= SIGN_MASK[size - 1];

	return bytes_reader.integer;
}

int get_byte_value(t_vm *machine, t_process *process, int *index, args_type_t type, char modulo)
{
	int res = 0;
	int address;
	switch (type)
	{
		case REG_CODE:
			res = process->registers[read_bytes(T_REG, machine->battlefield, ring(process->pc + *index))];
			*index += 1;
			break;
		case DIR_CODE:
			res = read_bytes(4, machine->battlefield, ring(process->pc + *index));
			*index += 4;
			break;
		case IND_CODE:
		address = read_bytes(T_IND, machine->battlefield, ring(process->pc + *index));
			if (modulo)
			{
				res = read_bytes(T_REG, machine->battlefield, ring(process->pc + (address % IDX_MOD)));
			}
			else
			{
				res = read_bytes(T_REG, machine->battlefield, ring(process->pc + address));
			}
			*index += 2;
			break;
	}
	return res;
}


int get_reg_number(t_vm *machine, t_process *process, int *index, args_type_t type)
{
	if (type != REG_CODE)
	{
		return -1;
	}
	int res = 0;
	res = read_bytes(T_REG, machine->battlefield, ring(process->pc + *index));
	*index += T_REG;
	return res;
}
