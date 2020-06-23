#include <corewar2.h>

void speaker(t_champion_array *champions)
{
	my_printf("Ladies and gentlemen, welcome to the Arena!\n");
	my_printf("Let me introduce today's players!\n");
	for (int i = 0; i < champions->size; i++)
	{
		my_printf("Player %d : %s (%s), weighting [%d] bytes!\n", i + 1, champions->array[i].name,champions->array[i].comment, champions->array[i].exec_code_size);
	}
}


void delete_vm(t_vm *machine)
{
	//Todo: Free vm
	machine = NULL;
	return ;
}

int main(int ac, char **av)
{
	if (ac == 1)
		return(my_error(NO_INPUT_FILE));
	t_champion_array champions;
	t_vm machine;
	int dump_cycle = parse_champions(&champions, ac, av);
	if (dump_cycle < -1)
		return 1;
	init_vm(&machine, &champions, dump_cycle);
	speaker(&champions);
	if (!play(&machine))
	{
		print_results(&machine);
	}
	delete_vm(&machine);
	return 0;
}
