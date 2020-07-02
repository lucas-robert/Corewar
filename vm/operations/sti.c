#include <corewar2.h>

void my_sti(t_vm *machine, t_process *process, const cw_t *operation)
{
	// T_DIR SIZE = 2;
	int arg[operation->num_args];
	unsigned char type;
	int index = 1;
	char acb = machine->battlefield[ring(process->pc + index)];
	index += 1;
	for (int i = 0; i < operation->num_args; i++)
	{
		type = (acb >> (2 * (3 - i)) & 3);
		if (is_direct(type))
		{
			arg[i] = read_bytes(ADDRESS, machine->battlefield, ring(process->pc + index));
			index += ADDRESS;
		}
		else
		{
			arg[i] = get_byte_value(machine, process, &index, type, MODULO);
		}
	}
	copy_bytes(machine, ring(process->pc + ((arg[1] + arg[2]) % IDX_MOD)), arg[0]);
	process->pc = ring(process->pc + index);
	if (machine->verbosity & VERBOSE_OP)
	{
		printf("Process %d | %s %d %d %d\n", process->id, operation->mnemonique, arg[0], arg[1], arg[2]);
	}
	if (machine->gui)
	{
		update_storage_gui(machine, ring(process->pc + ((arg[1] + arg[2]) % IDX_MOD)), process->champion_id);
	}
}
