#include "server.h"

struct context_server* server_init(char *ip, int port, struct transport *transport)
{
	struct context_server *context_server = NULL;

	context_server = calloc(1, sizeof(struct context_server));
	if (context_server == NULL) {
		return NULL;
	}

	memcpy(&context_server->transport, transport, sizeof(context_server->transport));

	context_server->sock_listen = context_server->transport.socket(AF_INET, SOCK_STREAM, 0);
	if (context_server->sock_listen < 0) {
		free(context_server);
		return NULL;
	}

	context_server->sockaddr_in.sin_family = AF_INET;
	context_server->sockaddr_in.sin_port = htons(port);
	context_server->sockaddr_in.sin_addr.s_addr = inet_addr(ip);
	context_server->transport.bind(context_server->sock_listen, (const struct sockaddr*)&context_server->sockaddr_in, sizeof(context_server->sockaddr_in));

	context_server->transport.listen(context_server->sock_listen, 1000);

	return context_server;
}

void server_deinit(struct context_server **context_server)
{
	int idx = 0;

	for (idx = 0; idx < MAX_CONTEXT_CONN; idx++) {
		server_close(*context_server, (*context_server)->context_conn[idx]);
	}

	free(*context_server);
	*context_server = NULL;
}

struct context_conn* server_accept(struct context_server *context_server)
{
	struct context_conn *context_conn = NULL;
	int idx = 0;

	if (context_server == NULL) {
		return NULL;
	}

	for (idx = 0; MAX_CONTEXT_CONN; idx++) {
		if (context_server->context_conn[idx] == NULL) {
			break;
		}
	}
	if (idx == MAX_CONTEXT_CONN) {
		return NULL;
	}

	context_conn = calloc(1, sizeof(struct context_conn));
	if (context_conn == NULL) {
		return NULL;
	}

	context_conn->sock = context_server->transport.accept(context_server->sock_listen, (struct sockaddr*)&context_conn->sockaddr_in_peer, &context_conn->sockaddr_in_peer_len);
	if (context_conn->sock < 0) {
		free(context_conn);
		return (struct context_conn*)-1;
	}
	
	context_conn->context_server = context_server;
	context_conn->timestamp = time(NULL);

	context_server->context_conn[idx] = context_conn;
	context_server->cnt_context_conn++;

	return context_conn;
}

void server_close(struct context_server *context_server, struct context_conn *context_conn)
{
	int idx = 0;

	if (context_server == NULL || context_conn == NULL) {
		return;
	}

	for (idx = 0; context_server->context_conn[idx] != context_conn; idx++);
	if (idx == MAX_CONTEXT_CONN) {
		return;
	}

	context_server->transport.close(context_conn->sock);
	context_server->cnt_context_conn--;
	free(context_server->context_conn[idx]);
	context_server->context_conn[idx] = NULL;
}

int server_get_cnt_conn(struct context_server *context_server)
{
	if (context_server == NULL) {
		return -1;
	}

	return context_server->cnt_context_conn;
}

int server_write(struct context_server *context_server, struct context_conn *context_conn, char *write_buf, size_t write_buf_len)
{
	int ret = 0;

	if (context_server == NULL || context_conn == NULL || write_buf == NULL) {
		return -2;
	}

	ret = context_server->transport.write(context_conn->sock, write_buf, write_buf_len);

	return ret;
}

void server_broadcast(struct context_server *context_server)
{
	int i = 0;
	char *broadcast_msg = DEFAULT_SERVER_BROADCAST_MSG;

	for (i = 0; i < MAX_CONTEXT_CONN; i++) {
		server_write(context_server, context_server->context_conn[i], broadcast_msg, strlen(broadcast_msg) + 1);
	}
}

int server_read(struct context_server *context_server, struct context_conn *context_conn, char *read_buf, size_t read_buf_len)
{
	int ret = 0;

	if (context_server == NULL || context_conn == NULL || read_buf == NULL) {
		return -2;
	}

	ret = context_server->transport.read(context_conn->sock, read_buf, read_buf_len);

	if (ret > 0) {
		context_conn->timestamp = time(NULL);
	}
	
	return ret;
}

int is_server_exit = 0, is_server_alarm = 0, is_server_broadcasting = 0;
static struct sigaction oldact;

static void sigint_handler(int signo)
{
	is_server_exit = 1;
}

static void sigusr_handler(int signo)
{
	is_server_broadcasting = 1;
}

static void sigalrm_handler(int signo)
{
	is_server_alarm = 1;
	alarm(1);
}

void server_init_signal(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));

	act.sa_handler = sigint_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, &oldact);
	
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGPIPE, &act, NULL);

	act.sa_handler = sigusr_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);

	act.sa_handler = sigalrm_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, NULL);
	alarm(1);
}

void server_deinit_signal(void)
{
	struct sigaction act;

	sigaction(SIGINT, &oldact, NULL);

	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGPIPE, &act, NULL);

	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);

	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, NULL);
	alarm(0);
}

int server_check_conn_timeout(struct context_server *context_server, struct context_conn *context_conn)
{
	time_t curr_timestamp;

	if (context_server == NULL || context_conn == NULL) {
		return 0;
	}

	curr_timestamp = time(NULL);

	if (curr_timestamp - context_conn->timestamp >= TIMEOUT_CONN) {
		return 1;
	}

	return 0;
}
