#include "routing.h"
#include "hash_table.h"

void route(const char buffer[BUFFER_SIZE], int client_socket, HashTable table)
{
	//Get the endpoint in the hashtable and use the fonction
	char *endpoint = get_endpoint(buffer);
	FunctionPointer handler = getFunction(&table, endpoint);

	if(handler == NULL)
	{
		printf("Didn't find the endpoint: %s\n", endpoint);
		return;
	}

	handler(buffer);

	free(endpoint);
}