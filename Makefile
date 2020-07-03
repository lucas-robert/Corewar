ASM = asm/asm
VM = vm/vm

all:
	make -C ./vm/
	make -C ./asm/

clean:
	make -C vm/ clean
	make -C asm/ clean

fclean: clean
	rm -f $(VM)
	rm -f $(ASM)

re: fclean all
