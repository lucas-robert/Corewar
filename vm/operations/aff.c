#include <corewar2.h>

void my_aff(t_vm *machine, t_process *process, const cw_t *operation)
{
	// printf("Aff operation\n");
	(void)operation;
	int index = 2;
	// debug(process->pc,machine->battlefield);
	int reg = read_bytes(REGISTER, machine->battlefield, ring(process->pc + index));
	index += REGISTER;
	process->pc = ring(process->pc + index);
	// debug(process->pc,machine->battlefield);
	if (machine->verbosity & VERBOSE_OP)
	{
		printf("Process %d says: \"%c\"\n", process->id, (reg % 256));
	}
}
