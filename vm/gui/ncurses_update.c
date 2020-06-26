#include <corewar2.h>

void update_gui(t_vm *machine, int pc, int opcode, int champion_id)
{
	t_coords location;
	char byte[3];
	int size = get_op_size(machine, pc, opcode);

	// Print pc
	attron(COLOR_PAIR(champion_id * 10));
	sprintf(byte, "%.2x ", machine->battlefield[pc]);
	get_position(pc, &location);
	mvaddstr(location.y, location.x, byte);
	attroff(COLOR_PAIR((champion_id * 10)));
	pc++;

	//print next code to exec;
	attron(COLOR_PAIR(champion_id * 10 + 1));
	for (int i = 0; i < size; i++)
	{
		get_position(ring(pc), &location);
		sprintf(byte, "%.2x ", machine->battlefield[ring(pc)]);
		mvaddstr(location.y, location.x, byte);
		pc++;
	}
	refresh();
}
