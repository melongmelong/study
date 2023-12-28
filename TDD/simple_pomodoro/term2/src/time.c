#include "time.h"

int get_pomo_time(void)
{
	return 25;
}

int get_break_time(int cnt)
{
	if (cnt % 4 == 0) {
		return 15;
	}

	return 5;
}
