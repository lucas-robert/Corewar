# Corewar - Assembler

## Installation

Simply run `make` to compile the **asm** executable.

## Usage - Assembler

`./asm [filename.s]`

Generate a .cor file, which is be interpretable by the virtual machine.

It will take as input some files written in the RedCode assembly language and output a program interpretable by the virtual machine.

The assemblers reads the file(s) given in input and write the bytecode into files whose names are similar but with the .cor postfix (instead of .s).

## Project explanation

### The assembly language
The assembly language is made of only one instruction per line.

#### Labels
• An instruction is made of three parts: an optional label, an opcode, and its arguments.

* A label is a characters string composed of char choosen among LABEL_CHARS, and ends with LABEL_CHAR.

* A label can be followed by nothing or be written on the prevous line it operates on.

* COMMENT_CHAR notifies of the beginning of a comment.

* Arguments are separated by SEPARATOR_CHAR.

#### Arguments types

> Register: r[REG_NUMBER]

> Direct: DIRECT_CHAR followed by a number or a label (followed by LABEL_CHAR)

> Indirect: A number or a label (followed by LABEL_CHAR), which is the the value located at the address pointed to by the value (or the label). The address represents an offset from the program counter of the current process.


* Addressing is relative to the PC and IDX_MOD, except for lld, lldi, and lfork.

* For each instruction, the number of cycles it takes to execute, its mnemonic, its number of parameters and their types are describd in the op_tab array in the op.c file. Cycles are always consumed.

* Any other code consumes one cycle and make the process jumps to the next instruction.

#### Instructions

* [0x01] live: One 4 bytes long parameter, the champion's number. Makes the champion stay alive.
* [0x02] ld: Take a random argument and a registry. Load the value of the first argument in the registry. It changes the carry.
* [0x03] st: Takes a register and a register or an indirect as input and store the value of the register into the second argument. For instance, st r1, 7, store the value in r1 at the address PC + 7 mod IDX_MOD
* [0x04] add: Takes three registries, add up the first two and write the result in the third, before modifying the carry.
* [0x05] sub: Same as add but ... substracts.
* [0x06] and: And operation bit-to-bit over the first two arguments and store the result in a registry before modifying the carry.
* [0x07] or: Like and but ... or.
* [0x08] xor: Like and but ... xor.
* [0x09] zjmp: No argument coding byte. Takes an index and jump to this address it the carry is 1.
* [0x0A] ldi: Takes 2 indexes and 1 registry, add up the indexes, interpreting the result as an address, reads the a value as big as a registry size and put that value in the third argument.
* [0x0B] sti: Take a registr, and two indexes (which can be registries): add up the two indexes and use the result as an address where the value of the first parameter will be copied.
* [0x0C] fork: No parameter encoding. Takes an index. Creates a new process, which inherits from the states of its parent, except the PC, which starts from the address (PC + (index % IDX_MOD))
* [0x0D] lld: It is the same as ld, but without % IDX_MOD. It also modifies the carry.
* [0x0E] lldi: Same as ldi but does not apply modulo on the address. Modifies the carry.
* [0x0F] lfork: Like fork without modulo
* [0x10] aff: One encoding byte for parameter. It only takes one parameter, a register. The value (mod 256) of the register is interpreted as an ASCII char.
