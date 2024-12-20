#include <pthread.h>
#include <sys/select.h>
#include <sys/select.h>
#include <sys/select.h>

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

	printf("connection closed(pid:%d)\n", getpid());
	server_close(context_server, context_conn);
}

static void process_main(struct context_server *context_server)
{
	pid_t pid; 
	struct context_conn *context_conn = NULL;

	server_init_signal();

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

	server_deinit_signal();
}

static struct thread_info {
	pthread_t tid;
	char valid;
	struct context_conn *context_conn;
	int is_server_exit, is_server_alarm;
} thread_info[MAX_CONTEXT_CONN];

static struct thread_info* thread_info_find_empty(void)
{
	int i = 0;

	for (i = 0; i < MAX_CONTEXT_CONN; i++) {
		if (thread_info[i].valid == 0) {
			return &thread_info[i];
		}
	}

	return NULL;
}

static struct thread_info* thread_info_find(pthread_t tid)
{
	int i = 0;

	for (i = 0; i < MAX_CONTEXT_CONN; i++) {
		if (thread_info[i].valid && thread_info[i].tid == tid) {
			return &thread_info[i];
		}
	}

	return NULL;
}

static void thread_info_broadcast_signal(int signo)
{
	int i = 0;

	for (i = 0; i < MAX_CONTEXT_CONN; i++) {
		if (thread_info[i].valid && thread_info[i].tid != pthread_self()) {
			pthread_kill(thread_info[i].tid, signo);
		}
	}
}

static void sigint_thread(int signo)
{
	int i = 0;

	for (i = 0; i < MAX_CONTEXT_CONN; i++) {
		if (thread_info[i].valid) {
			thread_info[i].is_server_exit = 1;
		}
	}

	thread_info_broadcast_signal(SIGUSR1);
}

static void sigalarm_thread(int signo)
{
	int i = 0;

	for (i = 0; i < MAX_CONTEXT_CONN; i++) {
		if (thread_info[i].valid) {
			thread_info[i].is_server_alarm = 1;
		}
	}

	thread_info_broadcast_signal(SIGUSR1);
	alarm(1);
}

static void sigusr_thread(int signo)
{
	//no-op
}

static void init_signal_thread(void)
{
	struct sigaction act;

	act.sa_handler = sigint_thread;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);

	act.sa_handler = sigusr_thread;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);

	act.sa_handler = sigalarm_thread;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, NULL);
	alarm(1);
}

static struct context_conn* do_accept_thread(struct context_server *context_server)
{
	struct thread_info *thread_info = thread_info_find(pthread_self());
	struct context_conn *context_conn = NULL;

	if (context_server == NULL) {
		return NULL;
	}

	printf("wait accept(tid:%ld)\n", pthread_self());

	do {
		context_conn = server_accept(context_server);
		if (thread_info->is_server_exit) {
			printf("sigint recieved!(pid:%d)\n", getpid());
			context_conn = NULL;
			break;
		}

		if (thread_info->is_server_alarm) {
			thread_info->is_server_alarm = 0;
		}
		
	} while ((int)context_conn == -1 && errno == EINTR);

	return context_conn;
}

static void* do_service_thread(struct thread_info *thread_info)
{
	struct context_server *context_server = NULL;
	struct context_conn *context_conn = NULL;
	char read_data[1024] = "";
	int ret = 0;

	context_conn = thread_info->context_conn;
	context_server = context_conn->context_server;

	if (context_conn == NULL) {
		return NULL;
	}

	printf("client acceptd(tid:%ld, accepted_sock:%d, cnt_context_conn:%d)!\n", pthread_self(), context_conn->sock, context_server->cnt_context_conn);

	while (1) {
		if (thread_info->is_server_exit) {
			printf("sigint recieved!(tid:%ld)\n", pthread_self());
			break;
		}

		if (thread_info->is_server_alarm) {
			thread_info->is_server_alarm = 0;

			if (server_check_conn_timeout(context_server, context_conn)) {
				printf("client timeout!(tid:%ld)\n", pthread_self());
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
		printf("read-tid:%ld(%s)\n", pthread_self(), read_data);
		if ((ret = server_write(context_server, context_conn, read_data, strlen(read_data) + 1)) <= 0) {
			if (ret < 0 && errno == EINTR)	continue;
			else	break;
		}
	}
			
	printf("connection closed(tid:%ld)\n", pthread_self());			
	server_close(context_server, context_conn);
	thread_info->valid = 0;

	return NULL;
}

static void thread_main(struct context_server *context_server)
{
	pthread_t pthread;
	struct thread_info *thread_info = NULL;
	struct context_conn *context_conn = NULL;

	// set up for listening thread.
	thread_info = thread_info_find_empty();
	thread_info->tid = pthread_self();
	thread_info->valid = 1;
	thread_info->context_conn = NULL;

	// use other signal handler on thread version.
	init_signal_thread();

	while (1) {
		context_conn = do_accept_thread(context_server);
		if (context_conn == NULL) {
			thread_info = thread_info_find(pthread_self());
			if (thread_info->is_server_exit) break;
			else continue;
		}

		thread_info = thread_info_find_empty();
		thread_info->valid = 1;
		thread_info->context_conn = context_conn;

		pthread_create(&thread_info->tid, NULL, do_service_thread, thread_info);
		pthread_detach(thread_info->tid);
	}
}

void multiplex_main(struct context_server *context_server)
{
	fd_set readset;
	int ret = 0, idx = 0, fd = 0;
	struct context_conn *context_conn = NULL;
	char read_data[1024] = "";

	server_init_signal();

	while (1) {
		if (is_server_exit) {
			printf("sigint recieved!\n");
			break;
		}

		if (is_server_alarm) {
			is_server_alarm = 0;

			for (idx = 0; idx < MAX_CONTEXT_CONN; idx++) {
				context_conn = context_server->context_conn[idx];
				if (server_check_conn_timeout(context_server, context_conn)) {
					printf("client timeout!(sock:%d)\n", context_conn->sock);
					server_close(context_server, context_conn);
				}
			}
		}

		FD_ZERO(&readset);
		FD_SET(context_server->sock_listen, &readset);
		for (idx = 0; idx < MAX_CONTEXT_CONN; idx++) {
			context_conn = context_server->context_conn[idx];
			if (context_conn) {
				FD_SET(context_conn->sock, &readset);
			}
		}

		ret = select(1024, &readset, NULL, NULL, NULL);
		if (ret < 0 && errno == EINTR) {
			continue;
		}

		if (FD_ISSET(context_server->sock_listen, &readset)) {
			context_conn = server_accept(context_server);
			printf("client acceptd(accepted_sock:%d, cnt_context_conn:%d)!\n", context_conn->sock, context_server->cnt_context_conn);
		}
		for (idx = 0; idx < MAX_CONTEXT_CONN; idx++) {
			context_conn = context_server->context_conn[idx];
			if (context_conn && FD_ISSET(context_conn->sock, &readset)) {
				ret = server_read(context_server, context_conn, read_data, sizeof(read_data));
				if (ret == 0) {
					printf("conn close!(sock:%d)\n", context_conn->sock);
					server_close(context_server, context_conn);
					continue;
				}
				printf("read-sock:%d(%s)\n", context_conn->sock, read_data);
				server_write(context_server, context_conn, read_data, strlen(read_data) + 1);
			}
		}
	}

	server_deinit_signal();
}

int main(int argc, char **argv)
{
	char *comm = NULL, *ip = NULL, *port = NULL, *type = NULL;
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
	
	comm = argv[0];

	if (argc != 4) {
		printf("%s [ip] [port] [type]\n", argv[0]);
		return -1;
	}

	ip = argv[1];
	port = argv[2];
	type = argv[3];

	printf("parent pid:%d, ip:%s, port:%s, type:%s\n", getpid(), ip, port, type);

	context_server = server_init(ip, atoi(port), &transport);

	switch (atoi(type)) {
	case 0:
		process_main(context_server);
		break;
	case 1:
		thread_main(context_server);
		break;
	case 2:
		multiplex_main(context_server);
		break;
	}

	server_deinit(&context_server);

	return 0;
}
