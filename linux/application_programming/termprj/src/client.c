#include "client.h"

struct context_client* client_init(char *ip, int port, struct transport_client *transport)
{
	struct context_client *context_client = NULL;
	int ret = 0;

	context_client = calloc(1, sizeof(struct context_client));
	if (context_client == NULL) {
		return NULL;
	}

	memcpy(&context_client->transport, transport, sizeof(context_client->transport));

	context_client->sockaddr_in_peer.sin_family = AF_INET;
	context_client->sockaddr_in_peer.sin_port = htons(port);
	context_client->sockaddr_in_peer.sin_addr.s_addr = inet_addr(ip);

	context_client->sock = context_client->transport.socket(AF_INET, SOCK_STREAM, 0);
	if (context_client->sock < 0) {
		free(context_client);
		return NULL;
	}

	ret = context_client->transport.connect(context_client->sock, (struct sockaddr*)&context_client->sockaddr_in_peer, sizeof(context_client->sockaddr_in_peer));
	if (ret < 0) {
		free(context_client);
		return NULL;
	}

	return context_client;
}

void client_close(struct context_client **context_client)
{
	if (context_client == NULL || *context_client == NULL) {
		return;
	}

	(*context_client)->transport.close((*context_client)->sock);

	free(*context_client);

	*context_client = NULL;
}

void client_write(struct context_client *context_client, char *write_buf, size_t write_buf_len)
{
	if (context_client == NULL || write_buf == NULL) {
		return;
	}

	context_client->transport.write(context_client->sock, write_buf, write_buf_len);
}

void client_read(struct context_client *context_client, char *read_buf, size_t read_buf_len)
{
	if (context_client == NULL || read_buf == NULL) {
		return;
	}
	
	context_client->transport.read(context_client->sock, read_buf, read_buf_len);
}

char* client_input_from_stdin(void)
{
	static char line[1024] = "", *newline = NULL;

	fgets(line, sizeof(line), stdin);
	
	newline = strrchr(line, '\n');
	if (newline) {
		*newline = '\0';
	}

	return line;
}
