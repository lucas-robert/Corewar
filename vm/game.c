#include <corewar2.h>

int is_op_valid(int c)
{
	return ((c >= 0 && c < 18) || c == CONTINUE);
}

t_champion *get_champion_by_id(t_vm *machine, t_process *process)
{
	if (process)
		return (&machine->champions->array[process->champion_id]);
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
		if (nb_process == 0)
			machine->last_alive = get_champion_by_id(machine, (t_process*) tmp->data);
		nb_process++;
		tmp = tmp->next;
	}
	return (nb_process > 1 ? 0 : 1);
}

void print_list(t_node **head)
{
	t_node *tmp = *head;
	int index = 0;
	while (tmp)
	{
		printf("Node %d: Process id %d", index, ((t_process*)tmp->data)->id);
		index++;
		tmp = tmp ->next;
	}
}

void check_alive_processes(t_vm *machine)
{
	t_node *check = machine->process_stack;
	int nb_alive = 0;
	while (check)
	{
		if (((t_process*)check->data)->last_live >= machine->current_cycle - machine->cycle_to_die)
		{
			nb_alive += 1;
			check = check->next;
		}
		else
		{
			t_node *tmp = check;
			check = check->next;
			delete_node(&machine->process_stack, tmp->data);
		}
	}

	if (nb_alive > NBR_LIVE || machine->nb_check > MAX_CHECKS)
	{
		machine->cycle_to_die -= CYCLE_DELTA;
		machine->nb_check = 0;
	}
	else
	{
		machine->nb_check += 1;
	}
	if (nb_alive > 0)
	{
		machine->last_alive = get_champion_by_id(machine, machine->process_stack->data);
	}

	return ;
}

int get_op_id(char position)
{
	int index = 0;
	if (position == 0)
		return CONTINUE;
	printf("Get op id: looking for op %d\n", position);
	while (cw_tab[index].mnemonique)
	{
		if (cw_tab[index].code == position)
			return index;
		else
			index++;
	}
	return EXIT_FAILURE;
}

void execute_process(t_vm *machine, t_process *current_process)
{

	void (*operations[])(t_vm*, t_process*, const cw_t*) = {&my_live, &my_ld, &my_st, &my_add, &my_sub, &my_and, &my_or, &my_xor, &my_zjmp, &my_ldi, &my_sti, &my_fork, &my_lld, &my_lldi, &my_lfork, &my_aff};
	if (current_process->cycle_till_exec > 0)
	{
		printf("Procces [%d] will execute %d (%s) in %d cycles\n",  current_process->id, current_process->next_op, cw_tab[current_process->next_op].mnemonique, current_process->cycle_till_exec);
		current_process->cycle_till_exec -= 1;
		return ;
	}
	else
	{
		//printf("next op of process [%d] => %d (%s)\n", current_process->id, current_process->next_op, cw_tab[current_process->next_op].mnemonique);
		if (is_op_valid(current_process->next_op) && current_process->next_op != CONTINUE)
		{
			printf("Process [%d] enters op %d (%s)\n",  current_process->id, current_process->next_op, cw_tab[current_process->next_op].mnemonique);
			(*operations[current_process->next_op])(machine, current_process, &cw_tab[current_process->next_op]);
			printf("Process [%d] exits op. PC : %d now pointing to: %d\n",current_process->id, current_process->pc, machine->battlefield[current_process->pc]);
			if (current_process->cycle_till_exec == -1)
			{   // If op as an invalid acb
				printf("Process %d just died! He fought bravely till the end (wrong acb)\n", current_process->id);
				printf("He was playing for %s\n", get_champion_by_id(machine, current_process)->name);
				delete_node(&machine->process_stack, current_process);
				return ;
			}
		}
		current_process->next_op = get_op_id(machine->battlefield[current_process->pc]);
		printf("Process next op => %d", current_process->next_op);
		if (!is_op_valid(current_process->next_op))
		{
			printf("Process %d just died! Attempting to read an invalid op\n", current_process->id);
			int pc = current_process->pc;
			unsigned char *battlefield = machine->battlefield;
			printf("==================================\n%.2x %.2x %.2x %.2x [%.2x] %.2x %.2x %.2x %.2x\n==================================\n",battlefield[pc -4], battlefield[pc -3], battlefield[pc -2], battlefield[pc -1], battlefield[pc], battlefield[pc + 1], battlefield[pc + 2], battlefield[pc + 3], battlefield[pc + 4]);
			delete_node(&machine->process_stack, current_process);
			return ;
		}
		if (current_process->next_op != CONTINUE)
			current_process->cycle_till_exec = cw_tab[current_process->next_op].num_cycles;
		printf("Next op set. PC: %d pointing at %x\n", current_process->pc, machine->battlefield[current_process->pc]);
		current_process->pc = (current_process->pc + 1) % MEM_SIZE;
		printf("PC moved. PC: %d pointing at %x\n", current_process->pc, machine->battlefield[current_process->pc]);
	}
	return ;
}


int play(t_vm *machine)
{
	while(1)
	{
		printf("Cycle %d / %d\n", machine->current_cycle, machine->dump_cycle);
		if (machine->dump_cycle >= 0 && machine->current_cycle == machine->dump_cycle)
		{
			printf("Dump cycle\n");
			print_memory(machine->battlefield);
			return 1;
		}
		if (find_winner(machine))
		{
			printf("Found a winner!\n");
			return 0;
		}
		if (machine->current_cycle  && (machine->current_cycle % machine->cycle_to_die == 0))
		{
			printf("machine->cycle to die = %d\n", machine->cycle_to_die);
			printf("!!! CYCLE TO DIE !!!! Checking alive processes\n");
			check_alive_processes(machine);
		}
		t_node *runner = machine->process_stack;
		while (runner)
		{
			t_node *to_process = runner;
			runner = runner->next;
			execute_process(machine, to_process->data);
		}
		machine->current_cycle += 1;
	}
}
