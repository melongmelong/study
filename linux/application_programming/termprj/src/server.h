#ifndef _SERVER_H_
#define _SERVER_H_

#include <stddef.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

struct transport {
	int (*socket)(int, int , int);
	int (*bind)(int , const struct sockaddr*, socklen_t);
	int (*listen)(int, int);
	int (*accept)(int, struct sockaddr*, socklen_t*);
};

struct context_server {
	struct transport transport;
	int sock_listen;
	struct sockaddr_in sockaddr_in;	
	int cnt_conn;
};

struct context_conn {
	int sock;
	struct sockaddr_in sockaddr_in_peer;	
	int sockaddr_in_peer_len;
};

struct context_server* server_init(char *ip, int port, struct transport *transport);
struct context_conn* server_accept(struct context_server *context_server);
int server_get_cnt_conn(struct context_server *context_server);

#endif
