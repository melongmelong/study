#ifndef _STATUS_H_
#define _STATUS_H_

enum {
	STATUS_NONE = -1,
	STATUS_QUIT
};

void set_status(char *input);
int get_status(void);

#endif
