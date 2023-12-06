#ifndef __STATUS_H_
#define __STATUS_H_

#define STATUS_NONE 0
#define STATUS_POMO 1
#define STATUS_BREAK 2

#define POMO_TIME 25
#define BREAK_TIME 5
#define LONG_BREAK_TIME 15

extern int g_status;

void set_status(int status);
int get_status(void);
int is_valid_status(int status);
int get_next_status(int status);

int get_pomo_time(void);
int get_break_time(int pomo_cnt);

#endif
