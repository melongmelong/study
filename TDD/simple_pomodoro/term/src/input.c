#include "input.h"

int is_valid_input(char *input)
{
	if (strcmp(input, INPUT_START) == 0) {
		return 1;
	}

	if (strcmp(input, INPUT_QUIT) == 0) {
		return 1;
	}

	return 0;
}
