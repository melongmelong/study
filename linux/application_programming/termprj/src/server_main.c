#include "server.h"

int main(int argc, char **argv)
{
	char *comm = NULL, *ip = NULL, *port = NULL;
	struct context_server *context_server = NULL;
	struct transport transport = {
		.socket = socket,
		.bind = bind,
		.listen = listen,
		.accept = accept,
		.close = close,
		.read = read,
		.write = write
	};
	struct context_conn *context_conn = NULL;
	char read_data[1024] = "";

	comm = argv[0];

	if (argc != 3) {
		printf("%s [ip] [port]\n", argv[0]);
		return -1;
	}

	ip = argv[1];
	port = argv[2];

	context_server = server_init(ip, atoi(port), &transport);

	context_conn = server_accept(context_server);

	while (1) {
		if (is_server_exit) {
			break;
		}

		server_read(context_server, context_conn, read_data, sizeof(read_data));
		server_write(context_server, context_conn, read_data, strlen(read_data) + 1);
		printf("read:%s\n", read_data);
	}

	server_close(context_server, context_conn);

	server_deinit(&context_server);

	return 0;
}
