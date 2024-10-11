#include "CUnit/Basic.h"
#include "CUnit/Console.h"

#include "server.h"

void test_server_accept_multi_client(void)
{
	//test for sepc1-1
	struct context_server *context_server = NULL;
	struct context_conn *context_conn[5] = {NULL, };
	int cnt_client = 0;

	context_server = server_init("127.0.0.1", 12345);

	context_conn[0] = server_accept(context_server);
	context_conn[1] = server_accept(context_server);
	context_conn[2] = server_accept(context_server);
	context_conn[3] = server_accept(context_server);
	context_conn[4] = server_accept(context_server);

	cnt_client = server_get_cnt_conn(context_server);

	CU_ASSERT(cnt_client == 5);
}

int main(int argc, char **argv)
{
	CU_pSuite test_suite = NULL;

	CU_initialize_registry();

	test_suite = CU_add_suite("test_suite", NULL, NULL);
	
	CU_add_test(test_suite, "test_server_accept_multi_client", test_server_accept_multi_client);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();

	return 0;
}
