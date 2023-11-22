#include <stdio.h>
#include "CUnit/Basic.h"
#include "CUnit/Console.h"

int main(int argc, char **argv)
{
	CU_pSuite test_suite = NULL;

	CU_initialize_registry();

	test_suite = CU_add_suite("test_suite", NULL, NULL);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return 0;
}