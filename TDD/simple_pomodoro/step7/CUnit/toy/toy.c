#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "CUnit/Console.h"

#define SUITE_NUM 5
#define TEST_NUM 1

void knwtest(void)
{
	CU_ASSERT(1 == 1);
	CU_ASSERT(2 == 2);
//	CU_FAIL("fail");
	CU_PASS("success");
}

int main(int argc, char **argv)
{
	CU_pSuite test_suite[SUITE_NUM] = {NULL,};
	int i, j;

	if (CU_initialize_registry() != CUE_SUCCESS) {
		printf("init failed\n");
		return CU_get_error();
	}

	for (i = 0; i < SUITE_NUM; i++) {
		test_suite[i] = CU_add_suite("knwtestsuite1", NULL, NULL);	
		if (test_suite[i] == NULL) {
			printf("suite%d is NULL\n", i);
			return CU_get_error();
		}

		if (CU_add_test(test_suite[i], "knwtest test", knwtest) == NULL) {
			printf("test is NULL\n");
			return CU_get_error();
		}
		
		printf("run tests\n");
		CU_basic_run_suite(test_suite[i]);
	}

//	CU_console_run_tests();

	CU_cleanup_registry();

	return 0;
}
