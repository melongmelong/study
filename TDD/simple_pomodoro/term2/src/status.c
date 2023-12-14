#include <string.h>
#include "status.h"

int g_status = -1;

void set_status(char *input)
{
	if (strcmp(input, "quit") == 0) {
		g_status = 0;
	}
	else {
		g_status = -1;
	}
}

int get_status(void)
{
	return g_status;
}
