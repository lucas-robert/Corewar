#include <corewar2.h>

t_champion *set_last_alive(t_vm *machine)
{
	return (get_champion_by_process(machine, ((t_process *)((t_node*)get_last_in_stack(&machine->process_stack))->data)));
}


void init_registers(t_process *process, int player_id)
{
	process->registers[0] = 0; // Unused, as registers start from r1..r16
	process->registers[1] = -player_id;
	for (int i = 2; i < REG_NUMBER + 1; i++)
	{
		process->registers[i] = 0;
	}
	return ;
}

void init_process(t_vm *machine, int position, int id)
{
	t_process *new_process = malloc(sizeof(t_process));

	if (new_process)
	{
		new_process->champion_id = id;
		new_process->id = id;
		new_process->carry = 0;
		new_process->pc = position;
		new_process->cycle_till_exec = 0;
		new_process->next_op = -1;
		new_process->last_live = 0;
		init_registers(new_process, id);
		push(&machine->process_stack, (void*)new_process);
		printf("Process id : %d with champion_id %d\n", new_process->id, new_process->champion_id);
	}
	return ;
}

void place_champions(t_vm *machine)
{
	int padding = MEM_SIZE / machine->champions.size;
	for (int i = 0; i < machine->champions.size; i++)
	{
		my_memcpy(&machine->battlefield[padding * i], machine->champions.array[i].code, PROCESS_MAX_SIZE);
		init_process(machine, (padding * i), i + 1);
	}
	return ;
}

void init_vm(t_vm *machine)
{
	machine->cycle_to_die = CYCLE_TO_DIE;
	machine->nb_check = 0;
	machine->current_cycle = 0;
	machine->nb_alive = 0;
	machine->last_check = 0;
	machine->process_stack = NULL;
	machine->dump_cycle = -1;
	machine->verbosity = 0;
	machine->gui = NULL;
	my_memset(machine->battlefield, 0 , MEM_SIZE + 1);
}
