#include <corewar1.h>

int main(int ac, char **av)
{
    t_base base = {0,  // Code
                   0,  // Lines
                   0,  // Instruction
                   {{"live", 1, {T_DIR}, 1, 10, "alive"},
                    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load"},
                    {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store"},
                    {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition"},
                    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction"},
                    {"and",
                     3,
                     {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
                     6,
                     6,
                     "et (and  r1, r2, r3   r1&r2 -> r3"},
                    {"or",
                     3,
                     {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
                     7,
                     6,
                     "ou  (or   r1, r2, r3   r1 | r2 -> r3"},
                    {"xor",
                     3,
                     {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
                     8,
                     6,
                     "ou (xor  r1, r2, r3   r1^r2 -> r3"},
                    {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero"},
                    {"ldi",
                     3,
                     {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
                     10,
                     25,
                     "load index"},
                    {"sti",
                     3,
                     {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
                     11,
                     25,
                     "store index"},
                    {"fork", 1, {T_DIR}, 12, 800, "fork"},
                    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load"},
                    {"lldi",
                     3,
                     {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
                     14,
                     50,
                     "long load index"},
                    {"lfork", 1, {T_DIR}, 15, 1000, "long fork"},
                    {"aff", 1, {T_REG}, 16, 2, "aff"},
                    {0, 0, {0}, 0, 0, 0}},
                   0,   // EOM
                   -1,  // Instructions len
                   0,   // STREAM
                   4};

    if (ac != 2)
    {
        my_error(NO_FILE, NULL);
    }

    validate_filename(av[1]);
    read_file(av[1], &base);

    // set default data for head
    header_t metadata;
    metadata.magic = COREWAR_EXEC_MAGIC;

    find_metadata(&base, &metadata);
    tokenize(&base);
    parse_tokens(&base);
    preprocess(&base);
    compile(&base, av[1], &metadata);
    delete_base_struct(&base);

    return (0);
}
