#include "input.h"

int is_valid_input(char *input)
{
	if (strcmp(input, INPUT_START) == 0) {
		return 1;
	}

	if (strcmp(input, INPUT_QUIT) == 0) {
		return 1;
	}

	return 0;
}

char* get_input(void)
{
	static char buff[128] = {0};
	char *p = NULL;

	p = fgets(buff, sizeof(buff), stdin);
	if (p == NULL) {
		return "";
	}

	while (*p) {
		if (*p == '\n') {
			*p = '\0';
		}
		p++;
	}

	return buff;
}
