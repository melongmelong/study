#include "server.h"

struct context_server* server_init(char *ip, int port)
{
	struct context_server *context_server = NULL;

	context_server = calloc(1, sizeof(struct context_server));
	if (context_server == NULL) {
		return NULL;
	}

	context_server->sock_listen = socket(AF_INET, SOCK_STREAM, 0);
	if (context_server->sock_listen < 0) {
		free(context_server);
		return NULL;
	}

	context_server->sockaddr_in.sin_family = AF_INET;
	context_server->sockaddr_in.sin_port = htons(port);
	context_server->sockaddr_in.sin_addr.s_addr = inet_addr(ip);
	bind(context_server->sock_listen, (const struct sockaddr*)&context_server->sockaddr_in, sizeof(context_server->sockaddr_in));

	listen(context_server->sock_listen, 1000);

	return context_server;
}

struct context_conn* server_accept(struct context_server *context_server)
{
	struct context_conn *context_conn = NULL;

	if (context_server == NULL) {
		return NULL;
	}

	context_conn = calloc(1, sizeof(struct context_conn));
	if (context_conn == NULL) {
		return NULL;
	}

	context_conn->sock = accept(context_server->sock_listen, (struct sockaddr*)&context_conn->sockaddr_in_peer, &context_conn->sockaddr_in_peer_len);
	if (context_conn->sock < 0) {
		free(context_conn);
		return NULL;
	}

	context_server->cnt_conn++;

	return NULL;
}

int server_get_cnt_conn(struct context_server *context_server)
{
	if (context_server == NULL) {
		return -1;
	}

	return context_server->cnt_conn;
}
