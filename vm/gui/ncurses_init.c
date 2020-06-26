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
	for (int line = 0; line < MEM_SIZE / BYTES_PER_LINE; line++)
	{
		attron(COLOR_PAIR(0));
		char address[ADDRESS_INDICATOR];
		sprintf(address, "0x%.4x : ", line * BYTES_PER_LINE);
		waddstr(machine->gui->core_w, address);
		// addstr(address);
		for (int row = 0; row < BYTES_PER_LINE; row ++)
		{
			char bytes[4];
			sprintf(bytes, "%.2x ", machine->battlefield[line * BYTES_PER_LINE + row]);
			waddstr(machine->gui->core_w, bytes);
			// addstr(bytes);
		}
		// addstr("\n");
		waddstr(machine->gui->core_w, "\n");
	}
	wrefresh(machine->gui->core_w);
	attroff(COLOR_PAIR(0));
	// refresh();
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
	// Set attribute
	t_coords location;
	wattron(machine->gui->core_w, COLOR_PAIR(id)); // Set the code in the defined color
	for (int i = 0; i < machine->champions.array[id - 1].exec_code_size; i++)
	{
		get_position(position, &location);
		char bytes[4];
		sprintf(bytes, "%.2x ", machine->champions.array[id - 1].code[i]);
		mvwaddstr(machine->gui->core_w, location.y , location.x , bytes);
		position = ring(position + 1);
	}
	wattroff(machine->gui->core_w, COLOR_PAIR(id));
	wrefresh(machine->gui->core_w);
}
