#include "routing.h"
#include "hash_table.h"

void route(const char buffer[BUFFER_SIZE], int client_socket)
{
    char *url = getURL(buffer);

	if(strcmp(url, "/") == 0){
		sprintf(response,
			"HTTP/1.1 200 OK\r\n\r\n");
	}
	else if(strncmp(url, "/echo", 5) == 0){
		sprintf(response,
			"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: "
			"%ld\r\n\r\n%s",
			strlen(url+6), url+6);
	}
	else if(strcmp(url, "/user-agent") == 0){
		char *user_agent = getHeaderAttribute(buffer, "User-Agent");
		sprintf(response,
			"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: "
			"%ld\r\n\r\n%s",
			strlen(user_agent), user_agent);
	}
	else{
		sprintf(response,
			"HTTP/1.1 404 Not Found\r\n\r\n");
	}

    int bytes_sent = send(client_socket, response, strlen(response), 0);

	if(bytes_sent == 0){
		fprintf(stderr, "Erreur pendant l'envoi du message!\n");
		return NULL;
	}
	else{
		printf("Sent %d bytes\n", bytes_sent);
	}

	free(url);
}