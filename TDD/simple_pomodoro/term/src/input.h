#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <string.h>

#define INPUT_START "start"
#define INPUT_QUIT "quit"

int is_valid_input(char *input);
char *get_input(void);

#endif
