#include <corewar2.h>

void init_registers(t_process *process, int player_id)
{
	process->registers[0] = player_id;
	for (int i = 1; i < REG_NUMBER; i++)
	{
		process->registers[i] = 0;
	}
	return ;
}
void init_process(t_vm *machine, int position, t_champion *champion, int id)
{
	t_process *new_process = malloc(sizeof(t_process));

	if (new_process)
	{
		new_process->champion_id = champion->id;
		new_process->id = id;
		new_process->carry = 0;
		new_process->pc = position;
		new_process->cycle_till_exec = 0;
		new_process->next_op = 0;
		new_process->last_live = 0;
		init_registers(new_process, champion->id);
		push(&machine->process_stack, (void*)new_process);
	}
	return ;
}

void place_champions(t_vm *machine, t_champion_array *champions)
{
	int padding = MEM_SIZE / champions->size;
	for (int i = 0; i < champions->size; i++)
	{
		printf("CODE IS %s", champions->array[i].code);
		my_strcpy(&machine->battlefield[padding * i], champions->array[i].code);
		init_process(machine, (padding * i), &champions->array[i], i);
		machine->last_alive = &champions->array[i];
	}
	return ;
}

void init_vm(t_vm *machine, t_champion_array *champions, int dump_cycle)
{
	machine->cycle_to_die = CYCLE_TO_DIE;
	machine->cycle_to_die = CYCLE_DELTA;
	machine->nb_check = 0;
	machine->dump_cycle = dump_cycle;
	machine->current_cycle = 0;
	machine->process_stack = NULL;
	machine->champions = champions;
	my_bzero(machine->battlefield, MEM_SIZE + 1);
	place_champions(machine, champions);
}
