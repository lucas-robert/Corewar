#include <corewar2.h>

void my_lfork(t_vm *machine, t_process *process, const cw_t *operation)
{

	int address = bytes_to_int( &machine->battlefield[process->pc], T_DIR);
	address = (process->pc + address) % MEM_SIZE;
	t_process *new_process = copy_process(machine, process, address);
	push(&machine->process_stack, (void*)new_process);
	process->pc = (process->pc + (T_DIR)) % MEM_SIZE;
	printf("Process %d performed a fork operation. New address: %d", process->id, address);
}
