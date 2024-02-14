#include <string.h>
#include "status.h"

int g_status = STATUS_NONE;

void set_status(char *input)
{
	if (strcmp(input, "quit") == 0) {
		g_status = STATUS_QUIT;
	}
	else if (strcmp(input, "start") == 0) {
		g_status = STATUS_POMO;
	}
	else {
		g_status = STATUS_NONE;
	}
}

int get_status(void)
{
	return g_status;
}
