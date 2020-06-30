#include <corewar1.h>

static const int NULL_SEPARATOR_SIZE = 4;

int convert_int(unsigned char *res, int number, int size)
{
    union
    {
        unsigned int integer;
        unsigned char byte[4];
    } byte_writer;

    byte_writer.integer = number;
    // int i = size;
	int i = 0;
	int end = size - 1;

    while (i < size)
    {
		// --i;
        res[end] = byte_writer.byte[i];
		--end;
		i++;
    }
    return size;
}

// 4 byte                   magic header 0xea83f3
// PROG_NAME_LENGTH byte    champion name
// 4 byte                   null
// 4 byte                   CHAMP_MAX_SIZE
// COMMENT_LENGTH byte      comment
// 4 byte                   null
// n byte                   champion exec code

void write_metadata(header_t *metadata, int fd)
{
    int header_size = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH +
                      NULL_SEPARATOR_SIZE + sizeof(metadata->prog_size) +
                      COMMENT_LENGTH + NULL_SEPARATOR_SIZE;
    unsigned char writable_header[header_size];
    int runner = 0;

    my_memset(writable_header, 0, header_size);

    runner += convert_int(writable_header, metadata->magic,
                          sizeof(COREWAR_EXEC_MAGIC));

    my_memcpy(&writable_header[runner], metadata->prog_name, PROG_NAME_LENGTH);

    runner += PROG_NAME_LENGTH + NULL_SEPARATOR_SIZE;

    runner += convert_int(&writable_header[runner], metadata->prog_size,
                          sizeof(metadata->prog_size));

    my_memcpy(&writable_header[runner], metadata->comment, COMMENT_LENGTH);

    write(fd, writable_header, header_size);
}
