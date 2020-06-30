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
			my_printf("Wrong op code, instruction %d\n", i);
		}
        if (l->arguments_number != base->cw_tab[l->op_code - 1].num_args)
		{
			my_printf("Error arguments number instruction %d\n", i);
		}
        for (int z = 0; z < l->arguments_number; z++)
        {
            if (!arg_validation_dispatcher(l->op_code, l->arguments[z].type, z))
			{
				my_printf("Error: argument number %d (%s) is invalid!\n", z, l->arguments[z].name);
			}

            if (has_acb(l->op_code))
			{
				set_acb(l);
			}
            set_value(l);
        }
    }
}

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
	printf("Writing bytecode to %s\n", asm_name);
    free(asm_name);

    buffer = (char *)malloc(sizeof(char) * ((base->instructions_len + 1) * 14));
    int byte_counter = fill_operation(base, buffer);

    fill_address(base, buffer);

	metadata->prog_size  = byte_counter;
	write_metadata(metadata, fd);
    write(fd, buffer, byte_counter);

    close(fd);
}
