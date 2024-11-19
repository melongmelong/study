#include <unistd.h>

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

char g_server_echo_test_buf[1024] = "";

static int fake_transport_write(int sock, char *write_buf, size_t write_buf_len)
{
	memcpy(g_server_echo_test_buf, write_buf, write_buf_len);

	// return 0 for meaning success
	return 0;
}

static int fake_transport_read(int sock, char *read_buf, size_t read_buf_len)
{
	memcpy(read_buf, "server hello", read_buf_len);

	// return 0 for meaning success
	return 0;
}

struct transport transport = {
	.socket = fake_transport_sock,
	.bind = fake_transport_bind,
	.listen = fake_transport_listen,
	.accept = fake_transport_accept,
	.close = fake_transport_close,
	.write = fake_transport_write,
	.read = fake_transport_read
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

void test_server_deinit(void)
{
	//test for sepc1-3
	struct context_server *context_server = NULL;
	struct context_conn *context_conn[5] = {NULL, };
	int cnt_client = 0;

	context_server = server_init("127.0.0.1", 12345, &transport);

	context_conn[0] = server_accept(context_server);
	context_conn[1] = server_accept(context_server);
	context_conn[2] = server_accept(context_server);
	context_conn[3] = server_accept(context_server);
	context_conn[4] = server_accept(context_server);

	server_deinit(&context_server);

	CU_ASSERT(context_server == NULL);
}

void test_server_echo(void)
{
	//test for spec1-4
	struct context_server *context_server = NULL;
	struct context_conn *context_conn = NULL;
	char read_data[1024] = "";

	context_server = server_init("127.0.0.1", 12345, &transport);

	context_conn = server_accept(context_server);

	server_read(context_server, context_conn, read_data, sizeof(read_data));
	server_write(context_server, context_conn, read_data, strlen(read_data) + 1);

	server_deinit(&context_server);

	CU_ASSERT(strcmp(g_server_echo_test_buf, read_data) == 0);
}

void test_server_exit_on_signal(void)
{
	//test for spec1-5
	server_init_signal();

	raise(SIGINT);
	
	server_deinit_signal();

	CU_ASSERT(is_server_exit == 1);
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

char g_client_echo_test_buf[1024] = "";

static int fake_transport_client_write(int sock, char *write_buf, size_t write_buf_len)
{
	memcpy(g_client_echo_test_buf, write_buf, write_buf_len);

	// return 0 for meaning success
	return 0;
}

static int fake_transport_client_read(int sock, char *read_buf, size_t read_buf_len)
{
	memcpy(read_buf, g_client_echo_test_buf, read_buf_len);

	// return 0 for meaning success
	return 0;
}

struct transport_client transport_client = {
	.socket = fake_transport_client_sock,
	.connect = fake_transport_client_connect,
	.close = fake_transport_client_close,
	.write = fake_transport_client_write,
	.read = fake_transport_client_read
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

void test_client_echo(void)
{
	//test for spec2-3
	struct context_client *context_client = NULL;
	char write_data[1024] = "client hello", read_data[1024] = "";

	context_client = client_init("127.0.0.1", 12345, &transport_client);

	client_write(context_client, write_data, strlen(write_data) + 1);
	client_read(context_client, read_data, sizeof(read_data));

	client_close(&context_client);

	CU_ASSERT(strcmp(write_data, read_data) == 0);
}

static int g_fd_org_stdin, g_fd_new_stdin, g_pipe_fd[2];

static void pre_test_client_input_from_stdin(void)
{
	g_fd_org_stdin = dup(STDIN_FILENO);
	pipe(g_pipe_fd);
	close(STDIN_FILENO);
	g_fd_new_stdin = dup(g_pipe_fd[0]);
	close(g_pipe_fd[0]);
}

static void post_test_client_input_from_stdin(void)
{
	close(STDIN_FILENO);
	dup(g_fd_org_stdin);
	close(g_fd_org_stdin);
}

void test_client_input_from_stdin(void)
{
	//test for spec2-4
	#define LINE1 "line1"
	#define LINE2 "line2"
	#define LINE3 "line3"
	char *input_stream = LINE1"\n"LINE2"\n"LINE3;
	char *line = NULL;

	pre_test_client_input_from_stdin();

	write(g_pipe_fd[1], input_stream, strlen(input_stream) + 1);
	close(g_pipe_fd[1]);

	line = client_input_from_file(stdin);
	CU_ASSERT(strcmp(line, LINE1) == 0);

	line = client_input_from_file(stdin);
	CU_ASSERT(strcmp(line, LINE2) == 0);
	
	line = client_input_from_file(stdin);
	CU_ASSERT(strcmp(line, LINE3) == 0);
	
	post_test_client_input_from_stdin();
}

void test_client_exit_on_signal(void)
{
	//test for spec2-5	
	client_init_signal();

	raise(SIGINT);
	
	client_deinit_signal();

	CU_ASSERT(is_client_exit == 1);
}

void test_client_input_from_file(void)
{
	//test for spec2-6
	#define LINE1 "line1"
	#define LINE2 "line2"
	#define LINE3 "line3"
	char *test_file_path = "test.txt", *test_data= LINE1"\n"LINE2"\n"LINE3"\n";
	char *line = NULL;
	FILE *fp = NULL;

	// write testdata
	fp = fopen(test_file_path, "w");
	fwrite(test_data, strlen(test_data) + 1, 1, fp);
	fclose(fp);

	// test
	fp = fopen(test_file_path, "r");

	line = client_input_from_file(fp);
	CU_ASSERT(strcmp(line, LINE1) == 0);

	line = client_input_from_file(fp);
	CU_ASSERT(strcmp(line, LINE2) == 0);

	line = client_input_from_file(fp);
	CU_ASSERT(strcmp(line, LINE3) == 0);

	fclose(fp);

	unlink(test_file_path);
}

int main(int argc, char **argv)
{
	CU_pSuite test_suite = NULL;

	CU_initialize_registry();

	test_suite = CU_add_suite("test_suite", NULL, NULL);
	
	CU_add_test(test_suite, "test_server_accept_multi_client", test_server_accept_multi_client);
	CU_add_test(test_suite, "test_server_close_by_server", test_server_close_by_server);
	CU_add_test(test_suite, "test_server_deinit", test_server_deinit);
	CU_add_test(test_suite, "test_server_echo", test_server_echo);
	CU_add_test(test_suite, "test_server_exit_on_signal", test_server_exit_on_signal);

	CU_add_test(test_suite, "test_client_connect_to_server", test_client_connect_to_server);
	CU_add_test(test_suite, "test_client_close_by_client", test_client_close_by_client);
	CU_add_test(test_suite, "test_client_echo", test_client_echo);
	CU_add_test(test_suite, "test_client_input_from_stdin", test_client_input_from_stdin);
	CU_add_test(test_suite, "test_client_exit_on_signal", test_client_exit_on_signal);
	CU_add_test(test_suite, "test_client_input_from_file", test_client_input_from_file);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();

	return 0;
}
