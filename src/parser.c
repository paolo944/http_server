#include "parser.h"

char *getMethod(const char buffer[BUFFER_SIZE])
{
    const char *end_method = strstr(buffer, " ");
	size_t method_len = end_method;
	char *method = (char*)malloc((method_len + 1)*sizeof(char));
	strncpy(method, buffer, method_len);
	method[method_len] = '\0';
	return method;
}

char *getURL(const char buffer[BUFFER_SIZE])
{
    const char *start_url = strstr(buffer, "/");
	const char *end_url = strstr(buffer, " H");
	size_t url_len = end_url - start_url;
	char *url = (char*)malloc((url_len + 1)*sizeof(char));
	strncpy(url, start_url, url_len);
	url[url_len] = '\0';
	return url;
}

char *getHTTPVersion(const char buffer[BUFFER_SIZE])
{
    const char *start_http = strstr(buffer, "H");
	const char *end_http = strstr(buffer, "\n");
	size_t http_len = end_http - start_http;
	char *http = (char*)malloc((http_len + 1)*sizeof(char));
	strncpy(http, start_http, http_len);
	http[http_len] = '\0';
	return http;
}

char *getHeaderAttribute(const char buffer[BUFFER_SIZE], const char *attribute)
{
    char *attr_formated = (char*)malloc((strlen(attribute) + 2)*sizeof(char));
    sprintf(attr_formated, "%s: !", attribute);

    const char *ua_start = strstr(buffer, attr_formated);
    
    if (!ua_start) {
        return NULL;
    }
    
    ua_start += strlen(attr_formated);
    const char* ua_end = strstr(ua_start, "\r\n");
    
    if (!ua_end) {
        return NULL;
    }

    size_t ua_len = ua_end - ua_start;
    if (ua_len >= BUFFER_SIZE) {
        ua_len = BUFFER_SIZE - 1;
    }

	char *header_attribute = (char*)malloc((ua_len + 1)*sizeof(char));

    strncpy(header_attribute, ua_start, ua_len);
    header_attribute[ua_len] = '\0';
    
    return header_attribute;
}

char *getBody(const const char buffer[BUFFER_SIZE])
{
    const char *start_body = strstr(buffer, "\r\n\r\n") + 4;
	const char *end_body = strlen(buffer);
    if(end_body != start_body)
    {
        return NULL;
    }
	size_t body_len = end_body - start_body;
	char *body = (char*)malloc((body_len + 1)*sizeof(char));
	strncpy(body, start_body, body_len);
	body[body_len] = '\0';
	return body;
}