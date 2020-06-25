#include <corewar2.h>

static const char *COLOR_TABLE[] = {RED, GREEN, YELLOW, BLUE};

int get_dump_cycle(char **av, int *index)
{
	if (av[*index + 1])
	{
		(*index)++;
		return (my_atoi(av[*index]));
	}
	else
		return 0;
}

void swap(t_champion *a, t_champion *b)
{
	t_champion tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int get_next_n(char **av, int *index)
{
	if (av[*index + 1])
	{
		(*index)++;
		return (my_atoi(av[*index]));
	}
	else
		return 0;
}

int set_id(t_champion_array *champions)
{
	int id = STARTING_CHAMPION_NUMBER;

	for (int i = 0; i < champions->size; i++)
	{
		champions->array[i].id = id;
		id++;
	}
	return EXIT_SUCCESS;
}

int get_champion_data(t_champion *champion, int fd)
{
	struct stat info;
	fstat(fd, &info);
	unsigned char buffer[info.st_size + 1];
	int reader = read(fd, buffer, info.st_size);
	int runner = EXEC_MAGIC_LEN;
	buffer[reader] = 0;

	if (read_bytes(sizeof(int), buffer, 0) != COREWAR_EXEC_MAGIC)
	{
		return (my_error(WRONG_MAGIC, champion->filename));
	}
	my_memcpy(champion->name, (char *)&buffer[runner], PROG_NAME_LENGTH);

	runner += PROG_NAME_LENGTH;
	runner += NULL_SEPARATOR_SIZE;

	champion->exec_code_size = read_bytes(4, buffer, runner);
	if (champion->exec_code_size > PROCESS_MAX_SIZE)
		return (my_error(TOO_LONG_CODE, champion->name));

	runner += sizeof(champion->exec_code_size);
	my_memcpy(champion->comment, &buffer[runner], COMMENT_LENGTH);

	runner += COMMENT_LENGTH;
	runner += NULL_SEPARATOR_SIZE;

	my_memset(champion->code, 0, PROCESS_MAX_SIZE + 1);
	my_memcpy(champion->code, &buffer[runner], champion->exec_code_size);

	champion->color = COLOR_TABLE[champion->id - 1];
	champion->last_live = 0;

	return EXIT_SUCCESS;

}

int sort_champion_array(t_champion_array *champions)
{
	int index = 0;
	while (index < champions->size)
	{
		if (champions->array[index].id > 0)
		{
			int dest = champions->array[index].id;
			if (dest > champions->size)
				return(my_error(TOO_BIG_N_NUMBER, NULL));

			else if (dest != champions->array[dest].id)
			{
				swap(&champions->array[index], &champions->array[dest]);
			}
			else if (dest != index)
			{
				return my_error(SAME_N_NUMBER, NULL);
			}
		}
		index++;
	}
	return (set_id(champions));
}

int read_champions(t_champion_array *champions)
{
	int index = 0;

	if (champions->size == 0)
		return (my_error(NO_INPUT_FILE, NULL));

	if (sort_champion_array(champions) > 0)
		return EXIT_FAILURE;

	while(index < champions->size)
	{
		int fd = open(champions->array[index].filename, O_RDONLY);
		if (fd < 1)
		{
			return(my_error(NO_SUCH_CHAMPION, champions->array[index].filename));
		}
		if (get_champion_data(&(champions->array[index]), fd) > 0)
		{
			return EXIT_FAILURE;
		}
		close(fd);
		index++;
	}
	return EXIT_SUCCESS;
}

int get_verbosity(char **av, int *index)
{
	if (av[*index + 1])
	{
		(*index)++;
		return (my_atoi(av[*index]));
	}
	else
		return 0;
}

int handle_option(char **av, t_vm *machine, int *index, int *next_n)
{
	if (my_strcmp(av[*index], "-dump") == 0 || my_strcmp(av[*index], "-d") == 0)
	{
		machine->dump_cycle = get_dump_cycle(av, index);
		if (machine->dump_cycle < 0)
		{
			return (my_error(NEGATIVE_DUMP_CYCLE, NULL));
		}
	}
	else if (my_strcmp(av[*index], "-n") == 0)
	{
		*next_n = get_next_n(av, index);
		if (*next_n < 0 || *next_n > MAX_PLAYERS_NUMBER)
		{
			return my_error(WRONG_N_NUMBER, NULL);
		}
	}
	else if (my_strcmp(av[*index], "-v") == 0)
	{
		machine->verbosity = get_verbosity(av, index);
		if (machine->verbosity < 0 || machine->verbosity > 4)
		{
			return my_error(WRONG_VERBOSE, NULL);
		}
	}
	else
	{
		return (my_error(ERR_ARG, av[*index]));
	}
	return EXIT_SUCCESS;
}

int parse_champions(t_vm *machine, t_champion_array *champions, char **av)
{
	int index = 1;
	int next_n = 0;
	int champion_id = 0;

	machine->dump_cycle = -1;
	machine->verbosity = 0;

	while(av[index])
	{
		if (av[index][0] == '-')
		{
			if (handle_option(av, machine, &index, &next_n) > 0)
				return EXIT_FAILURE;
		}
		else
		{
			if (champion_id > MAX_PLAYERS_NUMBER)
			{
				return (my_error(TOO_MUCH_CHAMPIONS, NULL));
			}
			champions->array[champion_id].filename = av[index];
			champions->array[champion_id].id = next_n - 1;
			next_n = 0;
			champion_id++;
		}
		index++;
	}
	champions->size = champion_id;
	if (read_champions(champions) > 0)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
