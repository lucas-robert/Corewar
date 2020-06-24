#include <corewar2.h>

void my_zjmp(t_vm *machine, t_process *process, const cw_t *operation)
{
	// T_DIR SIZE = 2;
	(void)operation;
	int address;
	int index = 1;
	address = read_bytes(2, machine->battlefield, ring(process->pc + index));
	index += 2;
	if (process->carry)
	{
		process->pc = ring(process->pc + (address % IDX_MOD));
		printf("Process %d | %s %d OK\n", process->id, operation->mnemonique, address);
	}
	else
	{
		printf("Process %d | %s %d FAIL\n", process->id, operation->mnemonique, address);
		process->pc = ring(process->pc + index);
	}
}
