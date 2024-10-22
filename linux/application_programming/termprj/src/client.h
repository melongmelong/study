#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

struct transport_client {
	int (*socket)(int, int , int);
	int (*connect)(int, struct sockaddr*, int);
	int (*close)(int);
};

struct context_client {
	struct transport_client transport;
	int sock;
	struct sockaddr_in sockaddr_in_peer;	
};

struct context_client* client_init(char *ip, int port, struct transport_client *transport);

#endif
