#include "./install/include/CUnit/Basic.h"
#include "./install/include/CUnit/Automated.h"

void test1(void)
{
	CU_ASSERT_EQUAL(1, 1);
}

void test2(void)
{
	CU_ASSERT_EQUAL(1,2);
}


int main(int argc, char **argv)
{
	CU_pSuite pSuite1 = NULL;
	CU_pSuite pSuite2 = NULL;

	CU_initialize_registry();

	pSuite1 = CU_add_suite("suite1", NULL, NULL);
	CU_add_test(pSuite1, "test1", test1);

	pSuite2 = CU_add_suite("suite2", NULL, NULL);
	CU_add_test(pSuite2, "test2", test2);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();

	return 0;
}
