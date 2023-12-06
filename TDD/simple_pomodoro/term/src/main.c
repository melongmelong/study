#include "input.h"

int main(int argc, char **argv)
{
	char *input = NULL;

	input = get_input();

	printf("%d\n", is_valid_input(input));

	return 0;
}
