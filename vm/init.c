#include <corewar2.h>

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
		new_process->next_op = -1;
		new_process->last_live = 0;
		init_registers(new_process, champion->id);
		push(&machine->process_stack, (void*)new_process);
		printf("INIT: Register[1] value is %d\n", new_process->registers[1]);
	}
	return ;
}

void place_champions(t_vm *machine, t_champion_array *champions)
{
	int padding = MEM_SIZE / champions->size;
	for (int i = 0; i < champions->size; i++)
	{
		my_memcpy(&machine->battlefield[padding * i], champions->array[i].code, PROCESS_MAX_SIZE);
		init_process(machine, (padding * i), &champions->array[i], i);
		machine->last_alive = &champions->array[i];
	}
	return ;
}

void init_vm(t_vm *machine, t_champion_array *champions, int dump_cycle)
{
	machine->cycle_to_die = CYCLE_TO_DIE;
	machine->nb_check = 0;
	machine->dump_cycle = dump_cycle;
	machine->current_cycle = 0;
	machine->process_stack = NULL;
	machine->champions = champions;
	my_memset(machine->battlefield, 0 , MEM_SIZE + 1);
	place_champions(machine, champions);
}
