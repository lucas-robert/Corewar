#include <corewar2.h>

void my_zjmp(t_vm *machine, t_process *process, const cw_t *operation)
{
	// T_DIR SIZE = 2;
	(void)operation;
	int address;
	int index = 1;
	printf("Entering zjmp ==>\n");;
	if (process->carry)
	{
		address = read_bytes(2, machine->battlefield, ring(process->pc + index));
		// printf("Jumpoing to %d\n", address);
		process->pc = ring(process->pc + (address % IDX_MOD));
		printf("Process %d Zjmp to %d\n",process->id, process->pc);
	}
	else
	{
		printf("Process %d failed zjmp\n",process->id);
		process->pc = ring(process->pc + index + 2);
	}
	// printf("zjmp operation\n");
}
