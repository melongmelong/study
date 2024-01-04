#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "CUnit/Console.h"

#include "op.h"

void test_add(void)
{
	CU_ASSERT(add(1, 1) == 2);
	CU_ASSERT(add(-1, 1) == 0);
	CU_ASSERT(add(-1, -1) == -2);
}

void test_minus(void)
{
	CU_ASSERT(minus(1,1) == 0);
	CU_ASSERT(minus(-1,1) == -2);
	CU_ASSERT(minus(-1,-1) == 0);
}

void test_mul(void)
{
	CU_ASSERT(mul(2,2) == 4);
	CU_ASSERT(mul(-2,2) == -4);
	CU_ASSERT(mul(-2,-2) == 4);
}

void test_divi(void)
{
	CU_ASSERT(divi(2,2) == 1);
	CU_ASSERT(divi(2,-2) == -1);
	CU_ASSERT(divi(-2,2) == -1);
	CU_ASSERT(divi(-2,-2) == 1);
}

void test_input(void)
{
	CU_ASSERT(check_input("1+1") == 1);
	CU_ASSERT(check_input("1 + 1") == 0);
	CU_ASSERT(check_input("1-1") == 1);
	CU_ASSERT(check_input("1 - 1") == 0);
	CU_ASSERT(check_input("1*1") == 1);
	CU_ASSERT(check_input("1 * 1") == 0);
	CU_ASSERT(check_input("1/1") == 1);
	CU_ASSERT(check_input("1 / 1") == 0);
	CU_ASSERT(check_input("1a+1a") == 0);
	CU_ASSERT(check_input("1b+1b") == 0);
	CU_ASSERT(check_input("1c + 1c") == 0);
	CU_ASSERT(check_input("1$+1$") == 0);
	CU_ASSERT(check_input("1+1+1") == 0);
	CU_ASSERT(check_input("4*-2") == 1);
	CU_ASSERT(check_input("5---1") == 0);
}

void test_parse(void)
{
	struct parsed parsed;

	parse_input("1+1", &parsed);
	CU_ASSERT(parsed.lval == 1 && parsed.rval == 1 && parsed.op == '+');

	parse_input("3-1", &parsed);
	CU_ASSERT(parsed.lval == 3 && parsed.rval == 1 && parsed.op == '-');

	parse_input("2*2", &parsed);
	CU_ASSERT(parsed.lval == 2 && parsed.rval == 2 && parsed.op == '*');

	parse_input("4/2", &parsed);
	CU_ASSERT(parsed.lval == 4 && parsed.rval == 2 && parsed.op == '/');
}

void test_case(void)
{
	struct parsed parsed;

	parse_input("1+1", &parsed);
	CU_ASSERT(calculate(&parsed) == 2);

	parse_input("3-1", &parsed);
	CU_ASSERT(calculate(&parsed) == 2);

	parse_input("2*2", &parsed);
	CU_ASSERT(calculate(&parsed) == 4);

	parse_input("4/2", &parsed);
	CU_ASSERT(calculate(&parsed) == 2);
}

int main(int argc, char **argv)
{
	CU_pSuite test_suite = NULL;

	CU_initialize_registry();

	test_suite = CU_add_suite("test_suite", NULL, NULL);	

	CU_add_test(test_suite, "test_add", test_add);
	CU_add_test(test_suite, "test_minus", test_minus);
	CU_add_test(test_suite, "test_mul", test_mul);
	CU_add_test(test_suite, "test_divi", test_divi);
	CU_add_test(test_suite, "test_input", test_input);
	CU_add_test(test_suite, "test_parse", test_parse);

	CU_basic_set_mode(CU_BRM_VERBOSE);	
	CU_basic_run_tests();

	CU_cleanup_registry();

	return 0;
}
