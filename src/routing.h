#ifndef ROUTING_H
#define ROUTING_H

#include "http_core.h"

void route(const char buffer[BUFFER_SIZE], int client_socket);

#endif