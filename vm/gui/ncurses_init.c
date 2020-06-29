#include <corewar2.h>

static const char *header_text[] = {" _____  _____ ______  _____  _    _   ___  ______ ","/  __ \\|  _  || ___ \\|  ___|| |  | | / _ \\ | ___ \\","| /  \\/| | | || |_/ /| |__  | |  | |/ /_\\ \\| |_/ /","| |    | | | ||    / |  __| | |/\\| ||  _  ||    / ","| \\__/\\ \\_/ /| |\\ \\ | |___ \\  /\\  /| | | || |\\ \\ "," \\____/ \\___/ \\_| \\_|\\____/  \\/  \\/ \\_| |_/\\_| \\_|", 0};

void set_header(t_vm *machine)
{
	wattron(machine->gui->header_w, A_BOLD);
	for (int i = 0; header_text[i]; i++)
	{
		mvwaddstr(machine->gui->header_w, i + 1,74, header_text[i]);
	}
}

void init_ncurses_battlefield(t_vm *machine)
{
	char address[ADDRESS_INDICATOR];
	char bytes[4]; //2 char per byte, plus space and \0

	wattron(machine->gui->core_w, COLOR_PAIR(0));
	for (int line = 0; line < MEM_SIZE / BYTES_PER_LINE; line++)
	{
		sprintf(address, "0x%.4x : ", line * BYTES_PER_LINE);
		waddstr(machine->gui->core_w, address);

		for (int row = 0; row < BYTES_PER_LINE; row ++)
		{
			sprintf(bytes, "%.2x ", 0);
			waddstr(machine->gui->core_w, bytes);
		}
		waddstr(machine->gui->core_w, "\n");
	}

	wrefresh(machine->gui->core_w);
	wattroff(machine->gui->core_w, COLOR_PAIR(0));
	return;
}

void init_color_pairs()
{
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	//CHAMP 1
	init_pair(1, COLOR_RED, COLOR_BLACK); // CODE
	init_pair(10, COLOR_CYAN, COLOR_RED); // PC
	init_pair(11, COLOR_WHITE, COLOR_RED); // NEXT_CODE_TO_EXEC

	//CHAMP 2
	init_pair(2, COLOR_BLUE, COLOR_BLACK); // CODE
	init_pair(20, COLOR_CYAN, COLOR_BLUE); // PC
	init_pair(21, COLOR_WHITE, COLOR_BLUE); // NEXT_CODE_TO_EXEC

	//CHAMP 3
	init_pair(3, COLOR_GREEN, COLOR_BLACK); // CODE
	init_pair(30, COLOR_CYAN, COLOR_GREEN); // PC
	init_pair(31, COLOR_WHITE, COLOR_GREEN); // NEXT_CODE_TO_EXEC

	// CHAMP 4
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // CODE
	init_pair(40, COLOR_CYAN, COLOR_MAGENTA); // PC
	init_pair(41, COLOR_WHITE, COLOR_MAGENTA); // NEXT_CODE_TO_EXEC

}

void init_windows(t_vm *machine)
{
	int parent_x;
	int parent_y;
	getmaxyx(stdscr, parent_y, parent_x);

	machine->gui = malloc(sizeof(t_gui));

	machine->gui->header_w = newwin(HEADER_SIZE, parent_x, 0, 0);
	machine->gui->core_w = newwin(parent_y, CORE_SIZE, HEADER_SIZE, 0);
	machine->gui->legend_w = newwin(parent_y, parent_x - CORE_SIZE, 0, CORE_SIZE);

	box(machine->gui->header_w, 0, 0);
	box(machine->gui->legend_w, 0, 0);
	set_header(machine);

	wattron(machine->gui->core_w, A_DIM);
	wattron(machine->gui->legend_w, A_DIM); //Set all prints to a bit dimmer

	wrefresh(machine->gui->header_w);
	wrefresh(machine->gui->core_w);
	wrefresh(machine->gui->legend_w);
}

void init_gui(t_vm *machine)
{
	initscr();
	if (has_colors() == FALSE)
	{
		machine->gui = 0;
    	endwin();
    	printf("Your terminal does not support color\n");
		return;
	}
	curs_set(FALSE);
	init_windows(machine);
	noecho();
	start_color();
	init_color_pairs();
	init_ncurses_battlefield(machine);
}

void ncurses_place_champion(t_vm *machine, int position, int id)
{
	t_coords location;
	char bytes[4];

	wattron(machine->gui->core_w, COLOR_PAIR(id + 1)); // Set the code in the defined color
	for (int i = 0; i < machine->champions.array[id].exec_code_size; i++)
	{
		get_position(position, &location);
		sprintf(bytes, "%.2x ", machine->champions.array[id].code[i]);
		mvwaddstr(machine->gui->core_w, location.y , location.x , bytes);
		position = ring(position + 1);
	}
	wattroff(machine->gui->core_w, COLOR_PAIR(id + 1));
	wrefresh(machine->gui->core_w);
}
