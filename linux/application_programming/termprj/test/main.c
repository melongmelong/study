#include "CUnit/Basic.h"
#include "CUnit/Console.h"

#include "server.h"
#include "client.h"

static int fake_transport_sock(int domain, int type, int protocol)
{
	// return 0 for meaning success
	return 0;
}

static int fake_transport_bind(int sock, const struct sockaddr *addr, socklen_t addrlen)
{
	// return 0 for meaning success
	return 0;
}

static int fake_transport_listen(int sock, int backlog)
{
	// return 0 for meaning success
	return 0;
}

static int fake_transport_accept(int sock, struct sockaddr *addr, socklen_t *addrlen)
{
	// return 0 for meaning success
	return 0;
}

static int fake_transport_close(int sock)
{
	// return 0 for meaning success
	return 0;
}

struct transport transport = {
	.socket = fake_transport_sock,
	.bind = fake_transport_bind,
	.listen = fake_transport_listen,
	.accept = fake_transport_accept,
	.close = fake_transport_close
};


void test_server_accept_multi_client(void)
{
	//test for sepc1-1
	struct context_server *context_server = NULL;
	struct context_conn *context_conn[5] = {NULL, };
	int cnt_client = 0;

	context_server = server_init("127.0.0.1", 12345, &transport);

	context_conn[0] = server_accept(context_server);
	context_conn[1] = server_accept(context_server);
	context_conn[2] = server_accept(context_server);
	context_conn[3] = server_accept(context_server);
	context_conn[4] = server_accept(context_server);

	cnt_client = server_get_cnt_conn(context_server);

	CU_ASSERT(cnt_client == 5);
}

void test_server_close_by_server(void)
{
	//test for sepc1-2
	struct context_server *context_server = NULL;
	struct context_conn *context_conn[5] = {NULL, };
	int cnt_client = 0;

	context_server = server_init("127.0.0.1", 12345, &transport);

	context_conn[0] = server_accept(context_server);
	context_conn[1] = server_accept(context_server);
	context_conn[2] = server_accept(context_server);
	context_conn[3] = server_accept(context_server);
	context_conn[4] = server_accept(context_server);

	server_close(context_server, context_conn[0]);
	server_close(context_server, context_conn[1]);

	cnt_client = server_get_cnt_conn(context_server);

	CU_ASSERT(cnt_client == 3);
}

static int fake_transport_client_sock(int domain, int type, int protocol)
{
	// return 0 for meaning success
	return 0;
}

static int fake_transport_client_connect(int sock, struct sockaddr *addr, socklen_t addrlen)
{
	// return 0 for meaning success
	return 0;
}

static int fake_transport_client_close(int sock)
{
	// return 0 for meaning success
	return 0;
}

struct transport_client transport_client = {
	.socket = fake_transport_client_sock,
	.connect = fake_transport_client_connect,
	.close = fake_transport_client_close
};

void test_client_connect_to_server(void)
{
	//test for spec2-1
	struct context_client *context_client = NULL;

	context_client = client_init("127.0.0.1", 12345, &transport_client);
	CU_ASSERT(context_client != NULL);
	
	client_close(&context_client);
	CU_ASSERT(context_client == NULL);
}

void test_client_close_by_client(void)
{
	//test for spec2-2
	struct context_client *context_client = NULL;

	context_client = client_init("127.0.0.1", 12345, &transport_client);
	client_close(&context_client);
	CU_ASSERT(context_client == NULL);
}

int main(int argc, char **argv)
{
	CU_pSuite test_suite = NULL;

	CU_initialize_registry();

	test_suite = CU_add_suite("test_suite", NULL, NULL);
	
	CU_add_test(test_suite, "test_server_accept_multi_client", test_server_accept_multi_client);
	CU_add_test(test_suite, "test_server_close_by_server", test_server_close_by_server);

	CU_add_test(test_suite, "test_client_connect_to_server", test_client_connect_to_server);
	CU_add_test(test_suite, "test_client_close_by_client", test_client_close_by_client);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();

	return 0;
}
