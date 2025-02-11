#ifndef HTTP_CORE_H
#define HTTP_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include "hash_table.h"

#define BUFFER_SIZE 1024

typedef struct {
    int client_socket;
    HashTable *table;
}ThreadArgs;

#endif