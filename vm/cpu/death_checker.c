#include <corewar2.h>

int find_winner(t_vm *machine)
{
	if(machine->process_stack == NULL)
	{
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

int death_checker(t_vm *machine)
{
	if ((machine->current_cycle && (machine->current_cycle == machine->last_check + machine->cycle_to_die)) || machine->cycle_to_die < 0)
	{

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
