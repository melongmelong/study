#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "status.h"
#include "time.h"

char *get_input(void)
{
	static char input[16] = {'\0'};
	char *p = NULL;

	input[0] = '\0';

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
	char *input = NULL;
	int status = STATUS_NONE;
	int exit = 0;
	int cnt = 0;

	do {
		input = get_input();

		set_status(input);
		status = get_status();

		switch (status) {
			case STATUS_POMO:
				printf("start pomo!\n");
				for (cnt = 1; cnt <= get_pomo_time(); cnt++) {
					sleep(1);
					printf("elapsed time(pomo):%d\n", cnt);
				}
				break;
			case STATUS_QUIT:
				printf("quit!\n");
				exit = 1;
				break;
		}
	} while (!exit);

	return 0;
}
