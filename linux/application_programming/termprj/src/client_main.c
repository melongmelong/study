#include "client.h"

int main(int argc, char **argv)
{
	char *comm = NULL, *ip = NULL, *port = NULL, *filepath = NULL;
	struct context_client *context_client = NULL;
	struct transport_client transport = {
		.socket = socket,
		.connect = connect,
		.close = close,
		.write = write,
		.read = read
	};
	char *write_data = NULL, read_data[1024] = "";
	FILE *fp = NULL;

	comm = argv[0];
	if (argc != 4) {
		printf("%s [ip] [port] [filepath]\n", comm);
		return -1;
	}

	ip = argv[1];
	port = argv[2];
	filepath = argv[3];
	if (strcmp(filepath, "stdin") == 0) {
		fp = stdin;
	}
	else {
		fp = fopen(filepath, "r");
	}

	client_init_signal();

	context_client = client_init(ip, atoi(port), &transport);

	while (1) {
		if (is_exit) {
			break;
		}

		write_data = client_input_from_file(fp);
		if (write_data == NULL) {
			break;
		}

		client_write(context_client, write_data, strlen(write_data) + 1);
		client_read(context_client, read_data, sizeof(read_data));
		printf("write : %s\n", write_data);
		printf("read : %s\n", read_data);
	}

	printf("exit.\n");

	client_close(&context_client);
	client_deinit_signal();

	return 0;
}
