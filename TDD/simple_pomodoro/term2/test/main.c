#include <stdio.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"

#include "status.h"

void test_quit(void)
{
	set_status("start");
	CU_ASSERT(get_status() != 0);

	set_status("quit");
	CU_ASSERT(get_status() == 0);

	set_status("abcd");
	CU_ASSERT(get_status() != 0);
}

int main(int argc, char **argv)
{
	CU_pSuite test_suite = NULL;

	CU_initialize_registry();

	test_suite = CU_add_suite("test_suite", NULL, NULL);

	CU_add_test(test_suite, "test_quit", test_quit);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return 0;
}
