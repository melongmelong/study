#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

struct transport_client {
	int (*socket)(int, int , int);
	int (*connect)(int, struct sockaddr*, socklen_t);
	int (*close)(int);
	int (*write)(int, char *, size_t);
	int (*read)(int, char *, size_t);
};

struct context_client {
	struct transport_client transport;
	int sock;
	struct sockaddr_in sockaddr_in_peer;	
};

struct context_client* client_init(char *ip, int port, struct transport_client *transport);
void client_close(struct context_client **context_client);

int client_write(struct context_client *context_client, char *write_buf, size_t write_buf_len);
int client_read(struct context_client *context_client, char *read_buf, size_t read_buf_len);

char* client_input_from_file(FILE *fp);

extern int is_client_exit;
void client_init_signal(void);
void client_deinit_signal(void);

#endif
