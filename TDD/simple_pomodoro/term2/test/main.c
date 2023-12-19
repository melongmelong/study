#include <stdio.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"

#include "status.h"
#include "time.h"

void test_start(void)
{
	set_status("start");
	CU_ASSERT(get_status() == STATUS_POMO);

	set_status("quit");
	CU_ASSERT(get_status() != STATUS_POMO);

	set_status("skjfksjfdkjskdf");
	CU_ASSERT(get_status() != STATUS_POMO);
}

void test_quit(void)
{
	set_status("start");
	CU_ASSERT(get_status() != STATUS_QUIT);

	set_status("quit");
	CU_ASSERT(get_status() == STATUS_QUIT);

	set_status("abcd");
	CU_ASSERT(get_status() != STATUS_QUIT);
}

void test_time(void)
{
	CU_ASSERT(get_pomo_time() == 25);
	CU_ASSERT(get_pomo_time() != 5);
	
	CU_ASSERT(get_break_time() == 5);
	CU_ASSERT(get_break_time() != 25);
}

int main(int argc, char **argv)
{
	CU_pSuite test_suite = NULL;

	CU_initialize_registry();

	test_suite = CU_add_suite("test_suite", NULL, NULL);

	CU_add_test(test_suite, "test_start", test_start);
	CU_add_test(test_suite, "test_quit", test_quit);
	CU_add_test(test_suite, "test_time", test_time);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return 0;
}
