#include <corewar2.h>

void my_lfork(t_vm *machine, t_process *process, const cw_t *operation)
{
	(void) operation;
	t_process *new_process;

	int index = 1;
	int address = read_bytes(2, machine->battlefield, ring(process->pc + index));

	address = ring(process->pc + address);
	new_process = copy_process(machine, process, address);
	index += 2;

	push(&machine->process_stack, (void*)new_process);
	set_next_op(machine, new_process);
	process->pc = ring(process->pc + index);
	if (machine->verbosity == 4)
		printf("Process %d | %s %d\n", process->id, operation->mnemonique, address);
}
