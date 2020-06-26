#include <corewar2.h>

void my_fork(t_vm *machine, t_process *process, const cw_t *operation)
{
	(void) operation;
	t_process *new_process;

	int index = 1;
	int address = read_bytes(ADDRESS, machine->battlefield, ring(process->pc + index));

	address = ring(process->pc + (address % IDX_MOD));
	new_process = copy_process(machine, process, address);
	index += ADDRESS;

	push(&machine->process_stack, (void*)new_process);
	set_next_op(machine, new_process);
	process->pc = ring(process->pc + index);
	if (machine->verbosity & VERBOSE_CYCLE)
	{
		printf("Process %d | %s %d\n", process->id, operation->mnemonique, address);
	}
}
