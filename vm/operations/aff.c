#include <corewar2.h>

void my_aff(t_vm *machine, t_process *process, const cw_t *operation)
{
	// printf("Aff operation\n");
	(void)operation;
	int index = 2;
	int reg = get_byte_value(machine, process, &index, REG_CODE, MODULO);
	process->pc = ring(process->pc + index);
	if (machine->verbosity & VERBOSE_OP)
	{
		printf("Process %d says: \"%c\"\n", process->id, reg);
	}
}
