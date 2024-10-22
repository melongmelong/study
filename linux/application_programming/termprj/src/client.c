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
