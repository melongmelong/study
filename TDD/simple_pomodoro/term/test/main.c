#include <stdio.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"

#include "input.h"
#include "status.h"

void test_input(void)
{
	CU_ASSERT(is_valid_input(INPUT_START) == 1);
	CU_ASSERT(is_valid_input(INPUT_START" ") == 0);

	CU_ASSERT(is_valid_input(INPUT_QUIT) == 1);
	CU_ASSERT(is_valid_input(INPUT_QUIT" ") == 0);

	CU_ASSERT(is_valid_input("sdkfjsdkfj ") == 0);
}

void test_pomo(void)
{
	set_status(STATUS_NONE);
	CU_ASSERT(is_valid_status(get_status()) == 1);

	set_status(STATUS_POMO);
	CU_ASSERT(is_valid_status(get_status()) == 1);

	set_status(STATUS_BREAK);
	CU_ASSERT(is_valid_status(get_status()) == 1);

	CU_ASSERT(get_next_status(STATUS_NONE) == STATUS_POMO);
	CU_ASSERT(get_next_status(STATUS_NONE) != STATUS_BREAK);
	CU_ASSERT(get_next_status(STATUS_POMO) == STATUS_BREAK);
	CU_ASSERT(get_next_status(STATUS_POMO) != STATUS_NONE);
	CU_ASSERT(get_next_status(STATUS_BREAK) == STATUS_NONE);
	CU_ASSERT(get_next_status(STATUS_BREAK) != STATUS_POMO);

	CU_ASSERT(get_pomo_time() == POMO_TIME);

	CU_ASSERT(get_break_time(1) == BREAK_TIME);
	CU_ASSERT(get_break_time(111) == BREAK_TIME);
	CU_ASSERT(get_break_time(4) == LONG_BREAK_TIME);
	CU_ASSERT(get_break_time(8) == LONG_BREAK_TIME);
	CU_ASSERT(get_break_time(888) == LONG_BREAK_TIME);
}

int main(int argc, char **argv)
{
	CU_pSuite test_suite = NULL;

	CU_initialize_registry();

	test_suite = CU_add_suite("test_suite", NULL, NULL);

	CU_add_test(test_suite, "test_input", test_input);
	CU_add_test(test_suite, "test_pomo", test_pomo);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return 0;
}
