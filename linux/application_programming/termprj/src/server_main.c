#include "server.h"

int main(int argc, char **argv)
{
	struct context_server *context_server = NULL;
	struct transport transport = {
		.socket = socket,
		.bind = bind,
		.listen = listen,
		.accept = accept,
		.accept = close 
	};
	struct context_conn *context_conn = NULL;

	context_server = server_init("127.0.0.1", 12345, &transport);

	context_conn = server_accept(context_server);
	
	server_close(context_server, context_conn);

	return 0;
}
