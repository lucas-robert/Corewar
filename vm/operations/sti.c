#include <corewar2.h>

void my_sti(t_vm *machine, t_process *process, const cw_t *operation)
{
	// T_DIR SIZE = 2;
	printf("reg1 = %d\n", process->registers[1]);
	int arg[operation->num_args];
	unsigned char type;
	int index = 0;
	char acb = machine->battlefield[ring(process->pc + index)];
	index += 1;
	for (int i = 0; i < operation->num_args; i++)
	{
		type = (acb >> (2 * (3 - i)) & 3);
		if (is_direct(type))
		{
			arg[i] = read_bytes(2, machine->battlefield, ring(process->pc + index));
			printf("DIRECT: %d\n", arg[i]);
			index += 2;
		}
		else
		{
			arg[i] = get_byte_value(machine, process, &index, type, MODULO);
		}
	}
	printf("sti r[%d] %d %d   => storing to %d\n ", arg[0],arg[1],arg[2], ring(process->pc + ((arg[1] + arg[2]) % IDX_MOD)));
	copy_bytes(machine, ring(process->pc + ((arg[1] + arg[2]) % IDX_MOD)), arg[0]);
	process->pc = ring(process->pc + index);
	printf("Process %d | %s %d %d %d", process->id, operation->mnemonique, arg[0], arg[1], arg[2]);
}
