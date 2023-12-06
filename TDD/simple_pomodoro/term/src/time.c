#include "time.h"

int get_pomo_time(void)
{
	return POMO_TIME;
}

int get_break_time(int pomo_cnt)
{
	int ret = BREAK_TIME; 

	if (pomo_cnt % 4 == 0) {
		ret = LONG_BREAK_TIME;
	}

	return ret;
}
