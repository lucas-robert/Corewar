#include <corewar2.h>

void my_zjmp(t_vm *machine, t_process *process, const cw_t *operation)
{
	(void)operation;
	int address;
	if (process->carry)
	{
		address = read_bytes(T_DIR, machine->battlefield, process->pc);
		process->pc = (process->pc + (address % IDX_MOD)) % MEM_SIZE;
	}
	else
	{
		process->pc = (process->pc + (T_DIR)) % MEM_SIZE;
	}
	printf("zjmp operation\n");
}
