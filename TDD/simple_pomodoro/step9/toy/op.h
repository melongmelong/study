#ifndef _OP_H_
#define _OP_H_

struct parsed {
	int lval;
	int rval;
	char op;
};

int add(int a, int b);
int minus(int a, int b);
int mul(int a, int b);
int divi(int a, int b);
int check_input(char *input);
int parse_input(char *input, struct parsed *parsed);
int calculate(struct parsed *parsed);

#endif
