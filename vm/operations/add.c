#include <corewar2.h>

void my_add(t_vm *machine, t_process *process, const cw_t *operation)
{
	//T_REG | T_REG | T_REG
	printf("process %d: Add operation\n", process->id);
	int reg[operation->num_args];
	unsigned char type;
	unsigned char acb  = machine->battlefield[process->pc % MEM_SIZE];
	int index = 1;

	for (int i = 0; i < operation->num_args; i++)
	{
		type = (acb >> (2 * (3 - i)) & 3);
		if (!is_acb_valid(type, operation->type[i]))
		{
			return (operation_failed(process));
		}
		reg[i] = get_reg_number(machine, process, &index, type);
		if (reg[i] > REG_NUMBER)
		{
			return (operation_failed(process));
		}
	};
	process->registers[reg[2]] = process->registers[reg[0]] + process->registers[reg[1]];
	process->pc = (process->pc + index) % MEM_SIZE;
	process->carry = (process->registers[reg[2]] ? 1 : 0);

}
