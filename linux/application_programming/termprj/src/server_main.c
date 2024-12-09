#include "server.h"

static struct context_conn* do_accept(struct context_server *context_server)
{
	struct context_conn *context_conn = NULL;

	if (context_server == NULL) {
		return NULL;
	}

	printf("wait accept(pid:%d)\n", getpid());

	do {
		context_conn = server_accept(context_server);
		if (is_server_exit) {
			printf("sigint recieved!(pid:%d)\n", getpid());
			context_conn = NULL;
			break;
		}

	} while ((int)context_conn == -1 && errno == EINTR);

	return context_conn;
}

static void do_service(struct context_conn *context_conn)
{
	struct context_server *context_server = NULL;
	char read_data[1024] = "";
	int ret = 0;

	if (context_conn == NULL) {
		return;
	}

	context_server = context_conn->context_server;

	// reinit signal just for re-set alarm()!
	// it seems too much... :)
	server_init_signal();

	printf("client acceptd(pid:%d, accepted_sock:%d, cnt_context_conn:%d)!\n", getpid(), context_conn->sock, context_server->cnt_context_conn);

	while (1) {
		if (is_server_exit) {
			printf("sigint recieved!(pid:%d)\n", getpid());
			break;
		}

		if (is_server_alarm) {
			is_server_alarm = 0;

			if (server_check_conn_timeout(context_server, context_conn)) {
				printf("client timeout!(pid:%d)\n", getpid());
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
		printf("read-pid:%d(%s)\n", getpid(), read_data);
		if ((ret = server_write(context_server, context_conn, read_data, strlen(read_data) + 1)) <= 0) {
			if (ret < 0 && errno == EINTR)	continue;
			else	break;
		}
	}
			
	server_close(context_server, context_conn);
}

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
	pid_t pid;

	comm = argv[0];

	if (argc != 3) {
		printf("%s [ip] [port]\n", argv[0]);
		return -1;
	}

	ip = argv[1];
	port = argv[2];

	printf("parent pid:%d, ip:%s, port:%s\n", getpid(), ip, port);

	server_init_signal();

	context_server = server_init(ip, atoi(port), &transport);

	while (1) {
		context_conn = do_accept(context_server);
		if (context_conn == NULL) {
			if (is_server_exit) break;
			else continue;
		}

		pid = fork();
		if (pid == 0) {
			do_service(context_conn);
			break;
		}
		else {
			server_close(context_server, context_conn);
		}
	}

	printf("server close(pid:%d)!\n", getpid());

	server_deinit(&context_server);

	server_deinit_signal();

	return 0;
}
