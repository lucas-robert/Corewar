#include <corewar2.h>

int is_op_valid(int c)
{
	return ((c >= 0 && c < 18) || c == CONTINUE);
}

int get_op_id(char position)
{
	int index = 0;
	if (position == 0)
	{
		return CONTINUE;
	}
	while (cw_tab[index].mnemonique)
	{
		if (cw_tab[index].code == position)
		{
			return index;
		}
		else
		{
			index++;
		}

	}
	return -1;
}
void set_next_op(t_vm *machine, t_process *process)
{
	process->next_op = get_op_id(machine->battlefield[process->pc]);
	if (!is_op_valid(process->next_op))
	{
		delete_node(&machine->process_stack, process);
		return;
	}
	if (process->next_op != CONTINUE)
	{
		process->cycle_till_exec = cw_tab[process->next_op].num_cycles - 1;
	}

	else
	{
		process->pc = ring(process->pc + 1);
	}

	if (machine->gui)
	{
		update_gui(machine, process->pc, process->next_op, -process->champion_id);
	}
}

void execute_process(t_vm *machine, t_process *current_process)
{

	void (*operations[])(t_vm*, t_process*, const cw_t*) = {&my_live, &my_ld, &my_st, &my_add, &my_sub, &my_and, &my_or, &my_xor, &my_zjmp, &my_ldi, &my_sti, &my_fork, &my_lld, &my_lldi, &my_lfork, &my_aff};
	if (current_process->cycle_till_exec > 0)
	{
		// printf("Cycle : [%d]   Procces [%d] will execute %d (%s) in %d cycles\n", machine->current_cycle, current_process->id, current_process->next_op, cw_tab[current_process->next_op].mnemonique, current_process->cycle_till_exec);
		current_process->cycle_till_exec -= 1;
		return;
	}
	else
	{
		if (current_process->next_op != CONTINUE)
		if (is_op_valid(current_process->next_op) && current_process->next_op != CONTINUE)
		{
			(*operations[current_process->next_op])(machine, current_process, &cw_tab[current_process->next_op]);
			if (current_process->cycle_till_exec == -1)
			{   // If op as an invalid acb
				printf("Process %d just died! He fought bravely till the end (wrong acb) while executing (%s) \n", current_process->id, cw_tab[current_process->next_op].mnemonique);
				printf("He was playing for %s\n", get_champion_by_process(machine, current_process)->name);
				delete_node(&machine->process_stack, current_process);
				return;
			}
		}
		set_next_op(machine, current_process);
	}
	return;
}
