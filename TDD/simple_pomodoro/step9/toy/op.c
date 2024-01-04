#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "op.h"

int add(int a, int b)
{
	return a + b;
}

int minus(int a, int b)
{
	return a - b;
}

int mul(int a, int b)
{
	return a * b;
}

int divi(int a, int b)
{
	return a / b;
}

#define IS_OP(ch) ch == '+' || ch == '-' || ch == '*' || ch == '/'

static int check_valid_input(char p)
{
	if (isdigit(p)) {
		return 1;
	}

	if (IS_OP(p)) {
		return 2;
	}

	return 0;
}

int check_input(char *input)
{
	char *p = input;
	int op_cnt = 0;
	int ret = 0;
	int flag = 0;

	while (*p) {
		ret = check_valid_input(*p);
		switch (ret) {
			case 0:
				return 0;
			case 1:
				break;
			case 2:
				if (!flag && (*(p+1) == '-')) {
					p += 2;
					flag = 1;
					op_cnt++;
					continue;
				}

				op_cnt++;
				break;
		}

		p++;
	}

	if (op_cnt > 1) {
		return 0;
	}

	return 1;
}

int parse_input(char *input, struct parsed *parsed)
{
	char *op = NULL;
	char *str = NULL;

	if (input == NULL || parsed == NULL) {
		return 0;
	}

	str = strdup(input);
	if (str == NULL) {
		return 0;
	}

	op = str;
	while (!(IS_OP(*op))) {
		op++;
	}
	parsed->op = *op;

	*op = '\0';
	parsed->lval = atoi(str);
	parsed->rval = atoi(op+1);

	return 1;
}

int calculate(struct parsed *parsed)
{
	int ret = 0;

	switch (parsed->op) {
		case '+':
			ret = add(parsed->lval, parsed->rval);
			break;
		case '-':
			ret = minus(parsed->lval, parsed->rval);
			break;
		case '*':
			ret = mul(parsed->lval, parsed->rval);
			break;
		case '/':
			ret = divi(parsed->lval, parsed->rval);
			break;
	}

	return ret;
}
