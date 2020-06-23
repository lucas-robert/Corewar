#include <stdio.h>

//assumes little endian
#define FIRST(x) ((x & 192) >> 5);
#define SECOND(x) ((x & 48) >> 3);
#define THIRD(x) ((x & 12) >> 1);
#define FOURTH(x) ((x & 3));
#define VALID_ACB(X, Y) (((X & Y) == X) ? 1 : 0));
# define IND_SIZE                1 << 1
# define REG_SIZE                1 << 2
# define DIR_SIZE                REG_SIZE

# define T_REG                   1 << 0
# define T_DIR                   1 << 1
# define T_IND                   1 << 2

void print_bytes(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
			if (j %2 == 0)
			printf(" ");
        }
    }
    printf("\n");
}

// char get_type(unsigned char *ptr)
// {
// 	unsigned char *b = *ptr;
// }

int main()
{
	// unsigned char acb = 84;
	// //
	// // print_bytes(sizeof(acb), &acb);
	// // unsigned char type = FIRST(acb) ;
	// // print_bytes(sizeof(acb), &type);
	// // printf("%d\n", type);
   	// // type = SECOND(acb);
	// // print_bytes(sizeof(acb), &type);
	// // printf("%d\n", type);
	// // type = THIRD(acb);
	// // print_bytes(sizeof(acb), &type);
	// // printf("%d\n", type);
	// // // type = FOURTH(acb);
	// // // print_bytes(sizeof(acb), &type);
	// // // printf("%d\n", type);
	//
	// //
	// // printf("%d\n", VALID_ACB(3, T_REG | T_DIR | T_IND));
	// //
	// // printf("reg =>%d\n", REG_SIZE);
	// // printf("ind =>%d\n", IND_SIZE);
	// // printf("dir =>%d\n", DIR_SIZE);
	// // short test = 2;
	// // int test1 = test;
	// unsigned char type;
	// for (int i = 0; i < 4; i++)
	// {
	// 	type = (acb >> (2 * (4 - i)) & 3);
	// 	print_bytes(sizeof(char), &type);
	// }

	printf("%ld", sizeof(int));
	// type = (acb >> 6);
	// print_bytes(sizeof(char), &acb);
	// type = (acb >> 4);

}
