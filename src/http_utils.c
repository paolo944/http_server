#include "http_utils.h"
#include "routing.h"

void *handle_connection(void *arg)
{
	ThreadArgs *args = (ThreadArgs*)arg;
	int client_socket = args->client_socket;
	HashTable *table = args->table;

	char buffer[BUFFER_SIZE] = {0};	

	int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);

	if(bytes_received == 0){
		printf("J'ai rien reçu!\n");
		return NULL;
	}

	route(buffer, client_socket, table);

	return NULL;
}