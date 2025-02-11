#include "http_utils.h"
#include "http_core.h"
#include "hash_table.h"

void launch_server(HashTable *table)
{
    int server_fd, client_addr_len;
	struct sockaddr_in client_addr;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		printf("Socket creation failed: %s...\n", strerror(errno));
		return;
	}

	struct sockaddr_in serv_addr = { .sin_family = AF_INET ,
									 .sin_port = htons(4221),
									 .sin_addr = { htonl(INADDR_ANY) },
									};

	if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != 0)
	{
		printf("Bind failed: %s \n", strerror(errno));
		return;
	}

	int connection_backlog = 10;
	if (listen(server_fd, connection_backlog) != 0)
	{
		printf("Listen failed: %s \n", strerror(errno));
		return;
	}

	printf("Waiting for a client to connect...\n");
	client_addr_len = sizeof(client_addr);

	while(1)
	{
		int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t * restrict)&client_addr_len);

		if(client_fd == -1)
			continue;

		pthread_t new_process;
    	ThreadArgs *args = malloc(sizeof(ThreadArgs));
    	args->client_socket = client_fd;
    	args->table = table;
    	pthread_create(&new_process, NULL, handle_connection, args);
	}

	close(server_fd);

    return;
}