#include <corewar2.h>

void speaker(t_champion_array *champions)
{
	printf("Ladies and gentlemen, welcome to the Arena!\n");
	printf("Let me introduce today's players!\n");
	for (int i = 0; i < champions->size; i++)
	{
		printf("Player %d : %s (%s), weighting [%d] bytes!\n", i + 1, champions->array[i].name,champions->array[i].comment, champions->array[i].exec_code_size);
	}
}


void delete_vm(t_vm *machine)
{
	if (machine->gui)
		endwin();
	//Todo: Free vm
	machine = NULL;
	return;
}

int main(int ac, char **av)
{
	t_vm machine;

	if (ac == 1)
		return(my_error(NO_INPUT_FILE, NULL));

	if (parse_champions(&machine, av) == EXIT_FAILURE)
		return EXIT_FAILURE;

	speaker(&machine.champions);
	if (!play(&machine))
	{
		print_results(&machine);
	}

	delete_vm(&machine);
	return EXIT_SUCCESS;
}
