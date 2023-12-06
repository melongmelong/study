#ifndef __STATUS_H_
#define __STATUS_H_

#define STATUS_NONE 0
#define STATUS_POMO 1
#define STATUS_BREAK 2

extern int g_status;

void set_status(int status);
int get_status(void);
int is_valid_status(int status);
int get_next_status(int status);

#endif
