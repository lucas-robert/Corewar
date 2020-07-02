# Corewar - Virtual machine

## Installation

Simply run `make` to compile the **corewar** executable. Ncurses library is needed to compile the program.

## Usage - Virtual machine

`./corewar [-d dump_cycles] [-n <champion.cor>] [-v] [-g]`

`-d`: Enable dump cycle. The executable will dump the memory to the standard output after `dump_cycles` cycles.

`-n <champion.cor>`: Input at least one `.cor` to run the program. Champions number can be determined using the `-n` flag.

`-v`: Enable verbose mode. 3 differents verbose mode are implemented (and can be combined together):

* 1: Show lives
* 2: Show cycles
* 4: Show operations

`-g`: Enable GUI interface. This will override the verbose mode.
