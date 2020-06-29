#include <corewar2.h>

int is_in_pc(int *pc, int len, int check)
{
	for (int i = 0; i < len; i++)
	{
		if (pc[i] == check)
			return 1;
	}
	return 0;
}

// void print_memory(t_vm *machine)
// {
// 	for (int line = 0; line < MEM_SIZE / BYTES_PER_LINE; line++)
// 	{
// 		printf("0x%.4x : ", line * BYTES_PER_LINE);
// 		for (int row = 0; row < BYTES_PER_LINE; row ++)
// 		{
// 			printf("%.2x ", machine->battlefield[line * BYTES_PER_LINE + row]);
// 		}
// 		printf("\n");
// 	}
// 	printf("Exiting loop\n");
// 	return;
// }

// 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00


void print_memory(t_vm *machine)
 {
    int len;
    int *PCs;
	t_node *tmp;
	char flag = 1;

       if (flag)
       {
           len = stack_len(&machine->process_stack);
           PCs = malloc(sizeof(int)*len);
           tmp = machine->process_stack;
           for (int i = 0; i < len; i++)
           {
                   PCs[i] = ((t_process*)(tmp->data))->pc;
                   tmp = tmp->next;
           }
        }

        for (int line = 0; line < MEM_SIZE / BYTES_PER_LINE; line++)
        {
                printf("0x%.4x : ", line * BYTES_PER_LINE);
                for (int row = 0; row < BYTES_PER_LINE; row ++)
                {
                       if (machine->battlefield[line * BYTES_PER_LINE + row])
                               printf(RED);
                       if (flag && is_in_pc(PCs, len, line * BYTES_PER_LINE + row))
                               printf(CYAN);
                        printf("%.2x ", machine->battlefield[line * BYTES_PER_LINE + row]);
                       printf(RESET);
                }
                printf("\n");
        }
        return;
}
