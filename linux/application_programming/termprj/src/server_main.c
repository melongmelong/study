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
	int ret = 0;

	comm = argv[0];

	if (argc != 3) {
		printf("%s [ip] [port]\n", argv[0]);
		return -1;
	}

	ip = argv[1];
	port = argv[2];

	server_init_signal();

	context_server = server_init(ip, atoi(port), &transport);

	do {
		context_conn = server_accept(context_server);
	} while ((int)context_conn == -1 && errno == EINTR);

	while (1) {
		if (is_server_exit) {
			break;
		}

		if (is_server_alarm) {
			is_server_alarm = 0;

			if (server_check_conn_timeout(context_server, context_conn)) {
				printf("client timeout!\n");
				break;
			}
		}

		/*
		TODO : need to consider more...
			broadcast msg is interleaved, so echo msg is delayed...
		if (is_server_broadcasting) {
			is_server_broadcasting = 0;
			server_broadcast(context_server);
			printf("send braodcast!\n");
		}
		*/

		if ((ret = server_read(context_server, context_conn, read_data, sizeof(read_data))) <= 0) {
			if (ret < 0 && errno == EINTR)	continue;
			else	break;
		}
		printf("read(%s)\n", read_data);
		if ((ret = server_write(context_server, context_conn, read_data, strlen(read_data) + 1)) <= 0) {
			if (ret < 0 && errno == EINTR)	continue;
			else	break;
		}
	}

	printf("server close!\n");

	server_close(context_server, context_conn);

	server_deinit(&context_server);

	server_deinit_signal();

	return 0;
}
