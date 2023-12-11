#include "input.h"
#include "status.h"
#include "time.h"

int main(int argc, char **argv)
{
	char *input = NULL;
	int pomo = 1;
	int cnt = 0;

	set_status(STATUS_NONE);

	do {
		input = get_input();

		if (is_valid_input(input) == 0) {
			continue;
		}

		if (strcmp(input, INPUT_QUIT) == 0) {
			break;
		}

		printf("===cur pomo : %d===\n", pomo);

		set_status(get_next_status(get_status()));
		for (cnt = 1; cnt <= get_pomo_time(); cnt++) {
			sleep(1);
			printf("pomo(%d/%d)\n", cnt, get_pomo_time());
		}
		pomo++;

		set_status(get_next_status(get_status()));
		for (cnt = 1; cnt <= get_break_time(pomo - 1); cnt++) {
			sleep(1);
			printf("break(%d/%d)\n", cnt, get_break_time(pomo - 1));
		}
		
		set_status(get_next_status(get_status()));
	} while (1);

	return 0;
}
