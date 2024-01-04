#include <stdio.h>
#include "op.h"

int main(int argc, char **argv)
{
	int ret;
	struct parsed parsed;

	if (check_input(argv[1]) == 0) {
		printf("invalid input\n");
		return 1;
	}

	if (parse_input(argv[1], &parsed) == 0) {
		printf("parsing failed\n");
		return 1;
	}

	printf("%d\n", calculate(&parsed));
	
	return 0;
}
