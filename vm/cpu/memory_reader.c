#include <corewar2.h>

static const int SIGN_MASK[3] = {0xffffff00, 0xffff0000, 0xff000000};

void copy_bytes(t_vm *machine, int address, int storage)
{
	// printf("copying %d to %d\n", storage, address);

	// if (storage >> 23 == 1)
	// 	storage ^= SIGN_MASK[2];
	union
	{
		int integer;
		char bytes[4];
	} to_store;
	to_store.integer = storage;

	// printf("copying: ");
	for (int i = 0; i < 4; i++)
	{
		// printf("%.2x ", to_store.bytes[3 - i]);
		machine->battlefield[ring(address + i)] = to_store.bytes[3 - i];
	}
	// printf("\n");
	return ;
}

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
			res = process->registers[read_bytes(REGISTER, machine->battlefield, ring(process->pc + *index))];
			*index += REGISTER;
			break;
		case DIR_CODE:
			// debug(ring(process->pc + *index), machine->battlefield);
			res = read_bytes(NUMBER, machine->battlefield, ring(process->pc + *index));
			*index += NUMBER;
			break;
		case IND_CODE:
			address = read_bytes(ADDRESS, machine->battlefield, ring(process->pc + *index));
			if (modulo)
			{
				// printf("ADDRESS IS %d\n", ring(process->pc + (address % IDX_MOD)));
				// debug(ring(process->pc + (address % IDX_MOD)), machine->battlefield);
				res = read_bytes(NUMBER, machine->battlefield, ring(process->pc + (address % IDX_MOD)));
			}
			else
			{
				res = read_bytes(NUMBER, machine->battlefield, ring(process->pc + address));
			}
			*index += ADDRESS;
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
