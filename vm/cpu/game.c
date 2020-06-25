#include <corewar2.h>

int is_op_valid(int c)
{
	return ((c >= 0 && c < 18) || c == CONTINUE);
}

t_champion *get_champion_by_process(t_vm *machine, t_process *process)
{
	if (process)
	{
		return (&machine->champions.array[process->champion_id]);
	}
	return NULL;
}

int find_winner(t_vm *machine)
{
	if(machine->process_stack == NULL)
	{
		printf("No process stack\n");
		return 1;
	}

	int nb_process = 0;
	t_node *tmp = machine->process_stack;
	while (tmp)
	{
		nb_process++;
		tmp = tmp->next;
	}
	if (nb_process == 1)
	{
		machine->last_alive = set_last_alive(machine);
	}

	return (nb_process > 1 ? 0 : 1);
}

void print_list(t_node **head)
{
	t_node *tmp = *head;
	int index = 0;
	while (tmp)
	{
		index++;
		printf("[%d] ->", ((t_process*)tmp->data)->id);
		tmp = tmp->next;
	}
	printf("\n");
}

void print_champions_last_live(t_vm *machine)
{
	for (int i = 0; i < machine->champions.size; i++)
	{
		printf("Champion [%s] (%d): last_alive: %d\n", machine->champions.array[i].name, machine->champions.array[i].id, machine->champions.array[i].last_live);
	}
}

void check_alive_processes(t_vm *machine)
{
	t_node *check = machine->process_stack;
	printf("Entering check alive: %d\n", stack_len(&machine->process_stack));

	while (check)
	{

		if (((t_process*)check->data)->last_live > machine->current_cycle - machine->cycle_to_die)
		{
			check = check->next;
		}
		else
		{
			// printf("Process %d has not been reported alive since %d\n", ((t_process*)check->data)->id, ((t_process*)check->data)->last_live);
			t_node *tmp = check;
			check = check->next;
			delete_node(&machine->process_stack, tmp->data);
		}
	}

	machine->last_check = machine->current_cycle;
	if (machine->nb_alive >= NBR_LIVE || machine->nb_check >= MAX_CHECKS)
	{
		machine->cycle_to_die -= CYCLE_DELTA;
		machine->nb_check = 0;
	}
	else
	{
		machine->nb_check += 1;
	}
	machine->nb_alive = 0;
	print_champions_last_live(machine);

	printf("Exiting check alive: %d\n", stack_len(&machine->process_stack));
}

int get_op_id(char position)
{
	int index = 0;
	if (position == 0)
		return CONTINUE;
	// printf("Get op id: looking for op %d\n", position);
	while (cw_tab[index].mnemonique)
	{
		if (cw_tab[index].code == position)
			return index;
		else
			index++;
	}
	return -1;
}

void set_next_op(t_vm *machine, t_process *process)
{
	process->next_op = get_op_id(machine->battlefield[process->pc]);
	// printf("Process next op => %d (%s)", process->next_op, cw_tab[process->next_op].mnemonique);
	if (!is_op_valid(process->next_op))
	{
		// printf(CYAN"Process %d just died! Attempting to read an invalid op\n"RESET, current_process->id);
		// debug(current_process->pc, machine->battlefield);
		delete_node(&machine->process_stack, process);
		return ;
	}
	if (process->next_op != CONTINUE)
		process->cycle_till_exec = cw_tab[process->next_op].num_cycles - 1;
	else
		process->pc = ring(process->pc + 1);
}

void execute_process(t_vm *machine, t_process *current_process)
{

	void (*operations[])(t_vm*, t_process*, const cw_t*) = {&my_live, &my_ld, &my_st, &my_add, &my_sub, &my_and, &my_or, &my_xor, &my_zjmp, &my_ldi, &my_sti, &my_fork, &my_lld, &my_lldi, &my_lfork, &my_aff};
	if (current_process->cycle_till_exec > 0)
	{
		// printf("Cycle : [%d]   Procces [%d] will execute %d (%s) in %d cycles\n", machine->current_cycle, current_process->id, current_process->next_op, cw_tab[current_process->next_op].mnemonique, current_process->cycle_till_exec);
		current_process->cycle_till_exec -= 1;
		return ;
	}
	else
	{
		if (current_process->next_op != CONTINUE)
			// printf("next op of process [%d] => %d (%s)\n", current_process->id, current_process->next_op, cw_tab[current_process->next_op].mnemonique);
		if (is_op_valid(current_process->next_op) && current_process->next_op != CONTINUE)
		{
			// printf("Process [%d] enters op %d (%s) at cycle [%d]\n",  current_process->id, current_process->next_op, cw_tab[current_process->next_op].mnemonique, machine->current_cycle);
			(*operations[current_process->next_op])(machine, current_process, &cw_tab[current_process->next_op]);
			// printf("Process [%d] exits op. PC : %d now pointing to: %d\n",current_process->id, current_process->pc, machine->battlefield[current_process->pc]);
			if (current_process->cycle_till_exec == -1)
			{   // If op as an invalid acb
				printf("Process %d just died! He fought bravely till the end (wrong acb) while executing (%s) \n", current_process->id, cw_tab[current_process->next_op].mnemonique);
				printf("He was playing for %s\n", get_champion_by_process(machine, current_process)->name);
				// debug(current_process->pc, machine->battlefield);
				delete_node(&machine->process_stack, current_process);
				return ;
			}
		}
		set_next_op(machine, current_process);
	}
	return ;
}

int death_checker(t_vm *machine)
{
	if (machine->cycle_to_die < 0)
	{
		printf("should check at cycle %d\n", machine->current_cycle);
	}
	if ((machine->current_cycle && (machine->current_cycle == machine->last_check + machine->cycle_to_die)) || machine->cycle_to_die < 0)
	{
		printf("Check alive \n");
		check_alive_processes(machine);
		printf("cycle_to_die is now %d at cycle %d\n", machine->cycle_to_die, machine->current_cycle);
		if (find_winner(machine))
		{
			printf("Found a winner!\n");
			print_memory(machine, 0);
			return 1;
		}
	}
	return 0;
}


int play(t_vm *machine)
{
	while(1)
	{
		if (machine->verbosity == 2)
			printf("Cycle %d / %d\n", machine->current_cycle, machine->dump_cycle);
		t_node *runner = machine->process_stack;
		while (runner)
		{
			t_node *to_process = runner;
			runner = runner->next;
			execute_process(machine, to_process->data);
		}
		if (machine->current_cycle == machine->dump_cycle)
		{
			printf("Cycle to die: %d\n", machine->cycle_to_die);
			print_list(&machine->process_stack);
			print_memory(machine, 1);
			delete_list(&machine->process_stack);
			return 1;
		}
		if (find_winner(machine))
		{
			printf("Found a winner!\n");
			print_memory(machine, 0);
			return 0;
		}

		if (death_checker(machine))
			return 0;
		// print_memory(machine, 1);
		// printf("\n\n\n");
		machine->current_cycle += 1;
	}
}
