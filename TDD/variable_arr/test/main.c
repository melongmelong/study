#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include "../src/arr.h"

void test_array(void)
{
	struct vararr arr;

	vararr_init(&arr, 128);

	vararr_set(&arr, 0, 1);
	CU_ASSERT_EQUAL_FATAL(arr.arr[0], 1);
	CU_ASSERT_EQUAL_FATAL(vararr_get(&arr, 0), 1);

	vararr_set(&arr, 5, 5);
	CU_ASSERT_EQUAL_FATAL(arr.arr[5], 5);
	CU_ASSERT_EQUAL_FATAL(vararr_get(&arr, 5), 5);
}

void test_array_init(void)
{
	struct vararr arr;

	vararr_init(&arr, 128);
	CU_ASSERT_EQUAL_FATAL(arr.len, 128);
	CU_ASSERT_EQUAL_FATAL(vararr_get_len(&arr), 128);
}

void test_array_overflow(void)
{
	struct vararr arr;

	vararr_init(&arr, 128);
	vararr_set(&arr, 129, 1);
	CU_ASSERT_EQUAL_FATAL(arr.len, 256);
	CU_ASSERT_EQUAL_FATAL(vararr_get_len(&arr), 256);
	CU_ASSERT_EQUAL_FATAL(arr.arr[129], 1);
	CU_ASSERT_EQUAL_FATAL(vararr_get(&arr, 129), 1);

	vararr_set(&arr, 300, 1);
	CU_ASSERT_EQUAL_FATAL(arr.len, 384);
	CU_ASSERT_EQUAL_FATAL(vararr_get_len(&arr), 384);
	CU_ASSERT_EQUAL_FATAL(arr.arr[300], 1);
	CU_ASSERT_EQUAL_FATAL(vararr_get(&arr, 300), 1);
}

int main(int argc, char *argv)
{
	CU_pSuite suite;
	CU_pRunSummary summary;

	CU_initialize_registry();

	suite = CU_add_suite("suite", NULL, NULL);
	CU_add_test(suite, "test_array", test_array);
	CU_add_test(suite, "test_array_init", test_array_init);
	CU_add_test(suite, "test_array_overflow", test_array_overflow);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();

	return 0;
}
