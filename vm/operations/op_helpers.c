#include <corewar2.h>

int ring(int pc)
{
	while (pc < 0)
	{
		pc += MEM_SIZE;
	}
	return pc % MEM_SIZE;
}


void debug(int pc, unsigned char *battlefield)
{
	printf("==================================\n%.2x %.2x %.2x %.2x [%.2x] %.2x %.2x %.2x %.2x\n==================================\n",battlefield[pc -4], battlefield[pc -3], battlefield[pc -2], battlefield[pc -1], battlefield[pc], battlefield[pc + 1], battlefield[pc + 2], battlefield[pc + 3], battlefield[pc + 4]);
}

void operation_failed(t_process *process)
{
	process->cycle_till_exec = -1;
	return;
}

void copy_registers(t_process *new_process, t_process *root)
{
	for (int i = 0; i < REG_NUMBER + 1; i++)
	{
		new_process->registers[i] = root->registers[i];
	}
	return;
}

t_process *copy_process(t_vm *machine, t_process *root, int address)
{
	t_process *new_process = malloc(sizeof(t_process));
	new_process->champion_id = root->champion_id;
	new_process->id = stack_len(&machine->process_stack) + 1;
	new_process->carry = root->carry;
	new_process->pc = ring(address);
	new_process->last_live = root->last_live;
	new_process->cycle_till_exec = 0;
	new_process->next_op = -1;
	copy_registers(new_process, root);

	// printf("New process id:%d\n", new_process->id);
	return new_process;
}

int is_register(args_type_t type)
{
	return ((type & T_REG) == type);
}

int is_direct(args_type_t type)
{
	return((type & T_DIR) == type);
}

int is_indirect(args_type_t type)
{
	return ((type & T_IND) == type);
}
