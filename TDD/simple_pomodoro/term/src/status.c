#include "status.h"

int g_status = STATUS_NONE;

void set_status(int status)
{
	g_status = status;
}

int get_status(void)
{
	return g_status;
}

int get_next_status(int status)
{
	int ret;

	switch (status) {
		case STATUS_NONE:
			ret = STATUS_POMO;
			break;
		case STATUS_POMO:
			ret = STATUS_BREAK;
			break;
		case STATUS_BREAK:
			ret = STATUS_NONE;
			break;
		default:
			break;
	}

	return ret;
}

int is_valid_status(int status)
{
	int ret = 0;

	switch (status) {
		case STATUS_NONE:
		case STATUS_POMO:
		case STATUS_BREAK:
			ret = 1;
			break;
		default:
			ret = 0;
			break;
	}

	return ret;
}
