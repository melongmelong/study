#include "client.h"

int main(int argc, char **argv)
{
	struct context_client *context_client = NULL;
	struct transport_client transport = {
		.socket = socket,
		.connect = connect,
		.close = close
	};

	context_client = client_init("127.0.0.1", 12345, &transport);

	client_close(&context_client);

	return 0;
}
