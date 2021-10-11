#include <stdio.h>
#include <stdlib.h>
#include "op.h"

int main(int argc, char **argv)
{
	printf("add : %d\n", add(atoi(argv[1]), atoi(argv[2])));
	printf("sub : %d\n", sub(atoi(argv[1]), atoi(argv[2])));
	printf("mul : %d\n", mul(atoi(argv[1]), atoi(argv[2])));
	printf("div : %d\n", divi(atoi(argv[1]), atoi(argv[2])));

	return 0;
}
