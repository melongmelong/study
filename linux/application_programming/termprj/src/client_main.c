#include "client.h"

int main(int argc, char **argv)
{
	char *comm = NULL, *ip = NULL, *port = NULL;
	struct context_client *context_client = NULL;
	struct transport_client transport = {
		.socket = socket,
		.connect = connect,
		.close = close,
		.write = write,
		.read = read
	};
	char *write_data = NULL, read_data[1024] = "";

	comm = argv[0];
	if (argc != 4) {
		printf("%s [ip] [port] [msg]\n", comm);
		return -1;
	}

	ip = argv[1];
	port = argv[2];
	write_data = argv[3];

	context_client = client_init(ip, atoi(port), &transport);

	client_write(context_client, write_data, strlen(write_data) + 1);
	client_read(context_client, read_data, sizeof(read_data));
	printf("write : %s\n", write_data);
	printf("read : %s\n", read_data);

	client_close(&context_client);

	return 0;
}
