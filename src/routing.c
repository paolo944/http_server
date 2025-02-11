#include "routing.h"
#include "hash_table.h"
#include "parser.h"

void route(const char buffer[BUFFER_SIZE], int client_socket, HashTable *table)
{
	//Get the endpoint in the hashtable and use the fonction
	char *endpoint = get_endpoint(buffer);
	FunctionPointer handler = getFunction(table, endpoint);

	if(handler == NULL)
	{
		printf("Didn't find the endpoint: %s\n", endpoint);
		const char *response = "HTTP/1.1 404 Not Found\r\n\r\n";
    	send(client_socket, response, strlen(response), 0);
		close(client_socket);
		return;
	}

	handler(client_socket, buffer);

	free(endpoint);
}