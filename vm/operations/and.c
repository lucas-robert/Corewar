#include <corewar2.h>

void my_and(t_vm *machine, t_process *process, const cw_t *operation)
{
	//T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG
	printf("Process pc: ===> %d\n", process->pc);
	int arg[operation->num_args];
	unsigned char type;
	int index = 0;
	unsigned char acb = machine->battlefield[(process->pc + index) % MEM_SIZE];
	printf("AND ACB=>>  %d\n", acb);
	index += 1;
	for (int i = 0; i < operation->num_args; i++)
	{
		printf("Index is %d\n", index);
		type = (acb >> (2 * (3 - i)) & 3);
		if (!is_acb_valid(type, operation->type[i]))
		{
			return (operation_failed(process));
		}
		if (i == 2)
		{
			arg[i] = get_reg_number(machine, process, &index, type);
			if (arg[i] > REG_NUMBER)
			{
				return (operation_failed(process));
			}
		}
		else
		{
			arg[i] = get_byte_value(machine, process, &index, type, MODULO);
		}

	}
	printf("Index is %d\n", index);
	process->registers[arg[2]] = arg[0] & arg[1];
	process->carry = (process->registers[arg[2]] = 0 ? 1 : 0);
	process->pc = (process->pc + index) % MEM_SIZE;

	printf("Process %d: and operation\n", process->id);
}
