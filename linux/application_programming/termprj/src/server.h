#ifndef _SERVER_H_
#define _SERVER_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

struct transport {
	int (*socket)(int, int , int);
	int (*bind)(int , const struct sockaddr*, socklen_t);
	int (*listen)(int, int);
	int (*accept)(int, struct sockaddr*, socklen_t*);
	int (*close)(int);
	int (*write)(int, char *, size_t);
	int (*read)(int, char *, size_t);
};

struct context_server {
	struct transport transport;
	int sock_listen;
	struct sockaddr_in sockaddr_in;	
	#define MAX_CONTEXT_CONN 128
	struct context_conn* context_conn[MAX_CONTEXT_CONN];
	int cnt_context_conn;
};

struct context_conn {
	struct context_server *context_server;
	int sock;
	struct sockaddr_in sockaddr_in_peer;	
	int sockaddr_in_peer_len;

	#define TIMEOUT_CONN 3 
	time_t timestamp;
};

struct context_server* server_init(char *ip, int port, struct transport *transport);
void server_deinit(struct context_server **context_server);
struct context_conn* server_accept(struct context_server *context_server);
void server_close(struct context_server *context_server, struct context_conn *context_conn);
int server_get_cnt_conn(struct context_server *context_server);

int server_write(struct context_server *context_server, struct context_conn *context_conn, char *write_buf, size_t write_buf_len);
int server_read(struct context_server *context_server, struct context_conn *context_conn, char *read_buf, size_t read_buf_len);

extern int is_server_exit, is_server_alarm;
void server_init_signal(void);
void server_deinit_signal(void);

int server_check_conn_timeout(struct context_server *context_server, struct context_conn *context_conn);
#endif
