#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include "http_core.h"

char *getMethod(const char buffer[BUFFER_SIZE]);

char *getURL(const char buffer[BUFFER_SIZE]);

char *get_endpoint(const char buffer[BUFFER_SIZE]);

char *getHTTPVersion(const char buffer[BUFFER_SIZE]);

char *getHeaderAttribute(const char buffer[BUFFER_SIZE], const char *attribute);

char *getBody(const char buffer[BUFFER_SIZE]);

#endif