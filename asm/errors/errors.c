#include <corewar1.h>

void my_error(ERRORS err, t_base *base)
{
    delete_base_struct(base);

    if (err == OPEN_ERROR)
        my_printf("Cant open file\n");
    else if (err == VALIDATION_FAILED)
        my_printf("Invalid filename\n");
    else if (err == NAME_DOES_NOT_EXIST)
        my_printf("Name does not exist\n");
    else if (err == COMMENT_DOES_NOT_EXIST)
        my_printf("Comment does not exist\n");
    else if (err == METADATA_DOES_NOT_EXIST)
        my_printf("Metadata does not exist\n");
    else if (err == COMMENT_SIZE_ERROR)
        my_printf("Error in comment size\n");
    else if (err == NAME_SIZE_ERROR)
        my_printf("Error in name size\n");
    else if (err == EMPTY_FILE)
        my_printf("File is empty\n");
    else if (err == NO_FILE)
        my_printf("Usage: asm <champion>.s\n");
    exit(1);
}

void my_parse_error(PARSE_ERRORS err, int line, t_base *base)
{
    delete_base_struct(base);

    if (err == UNDEFINED_TOKEN)
    {
        my_printf("undefined token line %d\n", line + base->EOM_number);
    }
    else if (err == TOO_MUCH_ARGUMENTS)
    {
        my_printf("too much arguments line %d\n", line + base->EOM_number);
    }
    else if (err == DOUBLE_LABEL)
    {
        my_printf("label duplicate line %d\n", line + base->EOM_number);
    }
    else if (err == DOUBLE_INST)
    {
        my_printf("instruction duplicate line %d\n", line + base->EOM_number);
    }
    else if (err == NOT_ENOUGH_ARGUMENTS)
    {
        my_printf("not enough arguments line %d\n", line + base->EOM_number);
    }
    exit(1);
}
