#include <corewar2.h>


void set_pc(t_vm *machine, int pc)
{
	t_coords location;
	chtype byte;

	get_position(ring(pc), &location);
	byte = mvwinch(machine->gui->core_w, location.y, location.x);
	mvwchgat(machine->gui->core_w, location.y, location.x, 3, A_STANDOUT | A_BOLD, PAIR_NUMBER(byte & A_COLOR), NULL);
}

// Reset gui at last position
void update_storage_gui(t_vm *machine, int address, int champion_id)
{
	t_coords location;
	char byte[4];
	//Set stored value in color
	wattron(machine->gui->core_w, COLOR_PAIR(champion_id));
	for (int i = 0; i < 4; i++)
	{
		get_position(ring(address), &location);
		sprintf(byte, "%.2x ", machine->battlefield[ring(address)]);
		mvwaddstr(machine->gui->core_w, location.y, location.x, byte);
		address++;
	}
	wattroff(machine->gui->core_w, COLOR_PAIR(champion_id * 10));
	wrefresh(machine->gui->core_w);
}

void update_core_gui(t_vm *machine, int pc, int champion_id)
{
	t_coords location;
	char byte[4];
	int size = get_op_size(machine, pc);

	// Print pc
	set_pc(machine, pc);
	pc++;

	//print next code to exec;
	wattron(machine->gui->core_w, COLOR_PAIR(champion_id * 10 + 1));
	for (int i = 0; i < size ; i++)
	{
		get_position(ring(pc), &location);
		sprintf(byte, "%.2x ", machine->battlefield[ring(pc)]);
		mvwaddstr(machine->gui->core_w, location.y, location.x, byte);
		pc++;
	}
	wattroff(machine->gui->core_w, COLOR_PAIR(champion_id * 10 + 1));
	wrefresh(machine->gui->core_w);
}
