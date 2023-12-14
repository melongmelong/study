#include <stdio.h>
#include <string.h>
#include "status.h"

char *get_input(void)
{
	static char input[16];
	char *p;

	printf(">");
	fgets(input, sizeof(input), stdin);

	p = strchr(input, '\n');
	if (p) {
		*p = '\0';
	}

	return input;
}

int main(int argc, char **argv)
{
	char *input;
	int status;
	int exit = 0;

	do {
		input = get_input();

		set_status(input);
		status = get_status();

		switch (status) {
			case STATUS_QUIT:
				printf("quit!\n");
				exit = 1;
			break;
		}
	} while (!exit);

	return 0;
}
