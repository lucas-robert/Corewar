#include <corewar2.h>

// Champion 1 code
// Champion 2 code
// Champion 3 code
// Champion 4 code

// Champion 1 pc
// Champion 2 pc
// Champion 3 pc
// Champion 4 pc

// Champion 1 code_exec
// Champion 2 code_exec
// Champion 3 code_exec
// Champion 4 code_exec

void init_ncurses_battlefield(t_vm *machine)
{
	for (int line = 0; line < MEM_SIZE / BYTES_PER_LINE; line++)
	{
		attron(COLOR_PAIR(0));
		char address[ADDRESS_INDICATOR];
		sprintf(address, "0x%.4x : ", line * BYTES_PER_LINE);
		// waddstr(machine->core, address);
		addstr(address);
		for (int row = 0; row < BYTES_PER_LINE; row ++)
		{
			char bytes[4];
			sprintf(bytes, "%.2x ", machine->battlefield[line * BYTES_PER_LINE + row]);
			// waddstr(machine->core, bytes);
			addstr(bytes);
		}
		addstr("\n");
		// waddstr(machine->core, "\n");
	}
	// wrefresh(machine->core);
	attroff(COLOR_PAIR(0));
	refresh();
	return;
}

void init_color_pairs()
{
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	//CHAMP 1
	init_pair(1, COLOR_RED, COLOR_BLACK); // CODE
	init_pair(10, COLOR_BLACK, COLOR_RED); // PC
	init_pair(11, COLOR_WHITE, COLOR_RED); // NEXT_CODE_TO_EXEC

	//CHAMP 2
	init_pair(2, COLOR_BLUE, COLOR_BLACK); // CODE
	init_pair(20, COLOR_BLACK, COLOR_BLUE); // PC
	init_pair(21, COLOR_WHITE, COLOR_BLUE); // NEXT_CODE_TO_EXEC

	//CHAMP 3
	init_pair(3, COLOR_GREEN, COLOR_BLACK); // CODE
	init_pair(30, COLOR_BLACK, COLOR_GREEN); // PC
	init_pair(31, COLOR_WHITE, COLOR_GREEN); // NEXT_CODE_TO_EXEC

	// CHAMP 4
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // CODE
	init_pair(40, COLOR_BLACK, COLOR_MAGENTA); // PC
	init_pair(41, COLOR_WHITE, COLOR_MAGENTA); // NEXT_CODE_TO_EXEC

	attron(A_BOLD);
}

void init_windows(t_vm *machine)
{
	int parent_x;
	int parent_y;

	getmaxyx(stdscr, parent_y, parent_x);
	machine->core = newwin(parent_y, parent_x - LEGEND_SIZE, 0, 0);
	machine->legend = newwin(parent_y, LEGEND_SIZE, 0, parent_x - LEGEND_SIZE);
	// draw to our windows
	// mvwprintw(arena, 0, 0, "Arena");
	// mvwprintw(legend, 0, 0, "legend");
	wborder(machine->core, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(machine->legend, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(machine->core);
	wrefresh(machine->legend);
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
	// if (COLS < MIN_ROW || LINES < MIN_LINE)
	// {
	// 	machine->gui = 0;
	// 	endwin();
    // 	printf("We recommend a minimum terminal size of %d x %d\n", MIN_ROW, MIN_LINE);
	// 	return;
	// }
	curs_set(FALSE);
	// init_windows(machine);
	noecho();
	// wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
	start_color();
	init_color_pairs();
	init_ncurses_battlefield(machine);
	refresh();
}

void ncurses_place_champion(WINDOW* core, unsigned char *champion_code, int pc, int champion_number, int exec_code_size)
{
	// Set attribute
	t_coords location;
	(void)core;
	attron(COLOR_PAIR(champion_number)); // Set the code in the defined color
	for (int i = 0; i < exec_code_size; i++)
	{
		get_position(pc, &location);
		char bytes[4];
		sprintf(bytes, "%.2x ", champion_code[i]);
		// mvwaddstr(core, location.y, location.x, bytes);
		mvaddstr(location.y, location.x, bytes);
		pc = ring(pc + 1);
	}
	attroff(COLOR_PAIR(champion_number));
	refresh();
	// wrefresh(core);
}
