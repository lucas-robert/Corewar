#include <corewar2.h>

void my_zjmp(t_vm *machine, t_process *process, const cw_t *operation)
{
	// T_DIR SIZE = 2;
	(void)operation;
	int address;
	if (process->carry)
	{
		address = read_bytes(2, machine->battlefield, process->pc);
		process->pc = (process->pc + (address % IDX_MOD)) % MEM_SIZE;
	}
	else
	{
		process->pc = (process->pc + 2) % MEM_SIZE;
	}
	printf("zjmp operation\n");
}
