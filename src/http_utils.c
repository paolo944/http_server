#include "http_utils.h"
#include "routing.h"

void *handle_connection(void *pclient_socket)
{
	int client_socket = *((int *)pclient_socket);

	char buffer[BUFFER_SIZE] = {0};	

	int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);

	if(bytes_received == 0){
		printf("J'ai rien reçu!\n");
		return NULL;
	}

	route(buffer, client_socket);

	return NULL;
}