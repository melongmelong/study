#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "../op.h"

void test_add(void)
{
	int val;

	val = add(2,3);
	CU_ASSERT_EQUAL_FATAL(val, 2+3);

	val = add(1,1);
	CU_ASSERT_EQUAL_FATAL(val, 1+1);

	val = add(1000000,20000);
	CU_ASSERT_EQUAL_FATAL(val, 1000000+20000);
}

void test_sub(void)
{
	int val;

	val = sub(1,1);
	CU_ASSERT_EQUAL_FATAL(val, 1-1);

	val = sub(10,3);
	CU_ASSERT_EQUAL_FATAL(val, 10-3);

	val = sub(1,3);
	CU_ASSERT_EQUAL_FATAL(val, 1-3);
}

void test_mul(void)
{
	int val;

	val = mul(2,5);
	CU_ASSERT_EQUAL_FATAL(val, 2*5);

	val = mul(1,1);
	CU_ASSERT_EQUAL_FATAL(val, 1*1);

	val = mul(-1,-5);
	CU_ASSERT_EQUAL_FATAL(val, -1*-5);

	val = mul(-1,5);
	CU_ASSERT_EQUAL_FATAL(val, -1*5);
}

void test_div(void)
{
	int val;

	val = divi(2,5);
	CU_ASSERT_EQUAL_FATAL(val, 2/5);

	val = divi(100,5);
	CU_ASSERT_EQUAL_FATAL(val, 100/5);

	val = divi(-100,-5);
	CU_ASSERT_EQUAL_FATAL(val, -100/-5);

	val = divi(-100,5);
	CU_ASSERT_EQUAL_FATAL(val, -100/5);
}

int main(int argc, char *argv)
{
	CU_pSuite suite;

	CU_initialize_registry();

	suite = CU_add_suite("suite", NULL, NULL);
	CU_add_test(suite, "test_add", test_add);
	CU_add_test(suite, "test_sub", test_sub);
	CU_add_test(suite, "test_mul", test_mul);
	CU_add_test(suite, "test_div", test_div);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();

	return 0;
}
