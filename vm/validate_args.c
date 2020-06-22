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

void set_color(t_champion *champion)
{
	(void)champion;
	//Todo: set champion color

}

int set_id(t_champion_array *champions)
{
	int index = 0;

	while (index < champions->size)
	{
		champions->array[index].id = index;
		index++;
	}
	return 0;
}

char *disassemble(char *buffer)
{
	(void)buffer;
	printf("TODO: disasemble\n");
	return NULL;
}

int get_champion_data(t_champion *champion, int fd)
{
	struct stat info;
	int runner = EXEC_MAGIC_LEN;
	fstat(fd, &info);
	char buffer[info.st_size + 1];
	int reader = read(fd, buffer, info.st_size);
	buffer[reader] = 0;

	if (bytes_to_int(buffer, EXEC_MAGIC_LEN) != COREWAR_EXEC_MAGIC)
	{
		my_printf("%s: ", champion->filename);
		return (my_error(WRONG_MAGIC));
	}
	my_strncpy(champion->name, &buffer[runner], PROG_NAME_LENGTH);
	runner += PROG_NAME_LENGTH;
	runner += NULL_SEPARATOR_SIZE;
	champion->exec_code_size = bytes_to_int(&buffer[runner], sizeof(champion->exec_code_size));
	runner += sizeof(champion->exec_code_size);
	my_strncpy(champion->comment, &buffer[runner], COMMENT_LENGTH);
	runner += COMMENT_LENGTH;
	runner += NULL_SEPARATOR_SIZE;

	my_bzero(champion->code, PROCESS_MAX_SIZE + 1);
	my_strcpy(champion->code, &buffer[runner]);
	champion->color = COLOR_TABLE[champion->id];

	// printf("[%s] =>  %s %s %d %s\n", champion->filename, champion->name, champion->comment, champion->exec_code_size, champion->code);

	return 0;

}

int sort_champion_array(t_champion_array *champions)
{
	int index = 0;
	while (index < champions->size)
	{
		if (champions->array[index].id >= 0)
		{
			int dest = champions->array[index].id;
			if (dest >= champions->size)
				return(my_error(TOO_BIG_N_NUMBER));
			else if (dest != champions->array[dest].id)
			{
				swap(&champions->array[index], &champions->array[dest]);
			}
			else if (dest != index)
			{
				return my_error(SAME_N_NUMBER);
			}
		}
		index++;
	}
	return (set_id(champions));
}

int read_champions(t_champion_array *champions)
{
	int index = 0;
	if (sort_champion_array(champions) > 0)
		return 1;
	while(index < champions->size)
	{
		// printf("Parsing champion number %d: %s\n", champions->array[index].id, champions->array[index].filename);
		int fd = open(champions->array[index].filename, O_RDONLY);
		if (fd < 1)
		{
			my_printf("%s: ", champions->array[index].filename);
			return(my_error(NO_SUCH_CHAMPION));
		}
		if (get_champion_data(&(champions->array[index]), fd) > 0)
		{
			return(1);
		}
		close(fd);
		index++;
	}
	return 0;
}

int handle_option(char **av, int *index, int *dump_cycle, int *next_n)
{
	if (my_strcmp(av[*index], "-dump") == 0)
	{
		*dump_cycle = get_dump_cycle(av, index);
		if (*dump_cycle < 0)
		{
			return (my_error(NEGATIVE_DUMP_CYCLE));
		}
	}
	else if (my_strcmp(av[*index], "-n") == 0)
	{
		*next_n = get_next_n(av, index);
		if (*next_n < 0 || *next_n > MAX_PLAYERS_NUMBER)
		{
			return my_error(WRONG_N_NUMBER);
		}
	}
	else
	{
		return (my_error(ERR_ARG));
	}
	return 0;
}

int parse_champions(t_champion_array *champions, int ac, char **av)
{
	int index = 1;
	int dump_cycle = 0;
	int next_n = -1;
	int champion_id = 0;
	(void)ac;

	while(av[index])
	{
		if (av[index][0] == '-')
		{
			if (handle_option(av, &index, &dump_cycle, &next_n) > 0)
				return -1;
		}
		else
		{
			if (champion_id > MAX_PLAYERS_NUMBER)
			{
				my_error(TOO_MUCH_CHAMPIONS);
				return -1;
			}
			champions->array[champion_id].filename = av[index];
			champions->array[champion_id].id = next_n;
			next_n = -1;
			champion_id++;
		}
		index++;
	}
	champions->size = champion_id;
	if (read_champions(champions) > 0)
		return -1;
	return dump_cycle;
}
