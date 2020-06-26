#include <corewar2.h>

void my_zjmp(t_vm *machine, t_process *process, const cw_t *operation)
{
	// T_DIR SIZE = 2;
	int address;
	int index = 1;
	address = read_bytes(ADDRESS, machine->battlefield, ring(process->pc + index));
	index += ADDRESS;
	if (process->carry)
	{
		process->pc = ring(process->pc + (address % IDX_MOD));
		if (machine->verbosity & VERBOSE_CYCLE)
		{
			printf("Process %d | %s %d OK\n", process->id, operation->mnemonique, address);
		}
	}
	else
	{
		if (machine->verbosity & VERBOSE_CYCLE)
		{
			printf("Process %d | %s %d FAIL\n", process->id, operation->mnemonique, address);
		}
		process->pc = ring(process->pc + index);
	}
}
