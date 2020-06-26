#include <corewar2.h>

void my_aff(t_vm *machine, t_process *process, const cw_t *operation)
{
	// printf("Aff operation\n");
	(void)operation;
	int index = 1;
	int reg = read_bytes(T_REG, machine->battlefield, ring(process->pc + index));
	index += 1;
	process->pc = ring(process->pc + index);
	if (machine->verbosity & VERBOSE_CYCLE)
	{
		printf("Process %d says: \"%c\"\n", process->id, (reg % 256));
	}
}
