#include <corewar1.h>
#include <sys/stat.h>  //for the open() permission flags

void set_acb(t_instruction *i)
{
    for (int z = 0; z < i->arguments_number; z++)
    {
        if (i->arguments[z].set)
        {
            i->acb = i->acb | (get_acb(i->arguments[z].type) << (6 - 2 * z));
        }
    }
}

int get_number(char *l)
{
    int i = my_atoi(l);
    return i;
}

int get_reg(char *l)
{
    int i = my_atoi(&l[1]);
    return i;
}

// for label will set 0
// for register will set 1 byte
// for ind will set 4
void set_value(t_instruction *i)
{
    for (int z = 0; z < i->arguments_number; z++)
    {
        if (i->arguments[z].set)
        {
            if (is_reg(i->arguments[z].type))
            {
                i->arguments[z].value.integer = get_reg(i->arguments[z].name);
            }
            else if (is_number(i->arguments[z].type))
            {
                i->arguments[z].value.integer =
                    get_number(i->arguments[z].name);
            }
        }
    }
}

// will prepare bin structure
void preprocess(t_base *base)
{
    for (int i = 0; i < base->instructions_len + 1; i++)
    {
        t_instruction *l = &base->instructions[i];

        if (l->op_code <= 0 || l->op_code >= 17)
		{
			my_printf("error op code");
		}
        if (l->arguments_number != base->cw_tab[l->op_code - 1].num_args)
		{
			my_printf("Error arguments number\n");
		}
        for (int z = 0; z < l->arguments_number; z++)
        {
            if (!arg_validation_dispatcher(l->op_code, l->arguments[z].type, z))
			{
				my_printf("ERRRORRRR for %d %d %d\n", z, l->op_code,
                          l->arguments[z].type);
			}

            if (has_acb(l->op_code))
			{
				set_acb(l);
			}
            set_value(l);
        }
    }

    // for (int i = 0; i < base->instructions_len + 1; i++)
    // {
    //     printf("%d %d %x %x %x %x\n", i, base->instructions[i].op_code,
    //            base->instructions[i].acb,
    //            base->instructions[i].arguments[0].value.integer,
    //            base->instructions[i].arguments[1].value.integer,
    //            base->instructions[i].arguments[2].value.integer);
    // }
}
// for each inst
// use code
// set acb or not depends on code
// for range args
// add 1, 2, 4 bytes value
// get arg bin

// on error exit

// 2 bytes ind
// 2-4 bytes dir
// 1 byte register

// ACB 1 byte 00 00 00 00
//            1  2   3
// T_REG = 01
// T_DIR = 10
// T_IND = 11

// first argument
// (f || REGISTER)

// if acb != operation acb
// exit

argument_value find_label_address(t_base *base, char *s)
{
    argument_value a;

    a.integer = 0;

    for (int i = 0; i < base->instructions_len + 1; i++)
    {
        if (base->instructions[i].label_exist == true &&
            my_strcmp(base->instructions[i].label.name, s) == 0)
            return (base->instructions[i].label.address);
    }
    return (a);
}

typedef struct s_comp
{
    int fd;
    char *buffer;
    int byte_counter;

} t_comp;

char *get_asm_name(char *filename)
{
    int len = my_strlen(filename);
    char *res = malloc(len + 3);
    my_bzero(res, len + 3);
    res = my_strcpy(res, filename);
    res[len - 1] = 'c';
    res[len] = 'o';
    res[len + 1] = 'r';
    return res;
}

int is_direct_or_indirect(TOKEN type)
{
    if (type == DIRECT_LABEL || type == INDIRECT_LABEL) return (1);
    return (0);
}

// depends on type will >> to 3 2 1 go go go
// will write champion to file

int fill_operation(t_base *base, char *buffer)
{
    int byte_counter = 0;

    for (int i = 0; i < base->instructions_len + 1; i++)
    {
        // if (byte_counter == 0)
        // {
        //     printf("zero %d\n", i);
        // }
        base->instructions[i].label.address.integer = byte_counter;
        buffer[byte_counter] = base->instructions[i].op_code;
        // my_printf("d %d %d\n", byte_counter, base->instructions[i].op_code);
        byte_counter++;

        if (has_acb(base->instructions[i].op_code))
        {
            buffer[byte_counter] = base->instructions[i].acb;
            byte_counter++;
        }

        for (int z = 0; z < base->instructions[i].arguments_number; z++)
        {
            if (base->instructions[i].arguments[z].set)
            {
                if (is_direct_or_indirect(
                        base->instructions[i].arguments[z].type))
                    base->instructions[i].arguments[z].label = byte_counter;

	            if (is_reg(base->instructions[i].arguments[z].type))
	            {
	                buffer[byte_counter] =
	                    base->instructions[i].arguments[z].value.byte[0];
	                byte_counter++;
	            }
	            else if (is_dir(base->instructions[i].arguments[z].type))
	            {
	                int s = t_dir_size(base->instructions[i].op_code);
	                // printf("%d %d\n", base->instructions[i].op_code, s);
	                for (int q = s - 1; q >= 0; q--)
	                {
	                    buffer[byte_counter] =
	                        base->instructions[i].arguments[z].value.byte[q];
	                    byte_counter++;
	                }
	            }
	            else if (is_ind(base->instructions[i].arguments[z].type))
	            {
	                int s = 2;
	                // printf("%d %d\n", base->instructions[i].op_code, s);
	                for (int q = s - 1; q >= 0; q--)
	                {
	                    buffer[byte_counter] =
	                        base->instructions[i].arguments[z].value.byte[q];
	                    byte_counter++;
	                }
				}
            }
        }
    }

    return byte_counter;
}

void fill_address(t_base *base, char *buffer)
{
    for (int i = 0; i < base->instructions_len + 1; i++)
    {
        for (int z = 0; z < base->instructions[i].arguments_number; z++)
        {
            if (base->instructions[i].arguments[z].type == DIRECT_LABEL)
            {
                int s = t_dir_size(base->instructions[i].op_code);
                int l = base->instructions[i].arguments[z].label;
                argument_value c = base->instructions[i].label.address;
                argument_value label = find_label_address(
                    base, base->instructions[i].arguments[z].name);

                argument_value where;
                where.integer = -(c.integer - label.integer);
                for (int q = s - 1; q >= 0; q--)
                {
                    buffer[l] = where.byte[q];
                    l++;
                }
            }
            if (base->instructions[i].arguments[z].type == INDIRECT_LABEL)
            {
                int s = 4;
                // 1
                int l = base->instructions[i].arguments[z].label;
                argument_value c = base->instructions[i].label.address;
                argument_value label = find_label_address(
                    base, base->instructions[i].arguments[z].name);

                argument_value where;
                where.integer = -(c.integer - label.integer);
                // printf("label %x\n", where.integer);
                for (int q = s - 1; q >= 0; q--)
                {
                    buffer[l] = where.byte[q];
                    l++;
                }
            }
        }
    }
}

void compile(t_base *base, char *filename, header_t *metadata)
{
    int fd;
    char *buffer;
    char *asm_name = get_asm_name(filename);
    fd = open(asm_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    free(asm_name);

    //                          op acb arg1 arg2 arg3
    // 4 byte arg1 T_DIR 4 arg1
    // 2 byte arg1 T_DIR 2 arg1 << 16 arg1 >> 16
    // 4 byte arg1 T_IND 4 arg1
    // 1 byte arg1 T_REG arg1 << 24 arg >> 24

    // if label > find label operation start point byte [0, PROG_SIZE]

    buffer = (char *)malloc(sizeof(char) * ((base->instructions_len + 1) * 14));
    int byte_counter = fill_operation(base, buffer);

    fill_address(base, buffer);

	metadata->prog_size  = byte_counter;
	printf("Byte counter: %d\n", byte_counter);
	write_metadata(metadata, fd);
    write(fd, buffer, byte_counter);

    close(fd);
    free(buffer);

    // 1 need address of direct | indirect label
    // 2 need address of instruction where label is called
    // 3 need address of label instruction that was called

    // this part for linux based compiler
    // int c = 0;
    // for (int i = 0; i < byte_counter; i++)
    // {
    //     printf("%x  ", buffer[i]);
    //     if (c == 0 )
    //     {
    //         c = 1;
    //         write(fd, &buffer[i + 1], 1);
    //     } else
    //     {
    //         c = 0;
    //         write(fd, &buffer[i - 1], 1);
    //     }
    // }
}
