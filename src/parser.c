#include "parser.h"

char *getMethod(const char buffer[BUFFER_SIZE])
{
    const char *end_method = strstr(buffer, " ");
	size_t method_len = end_method - buffer;

	char *method = (char*)malloc((method_len + 1)*sizeof(char));
    if(method == NULL)
    {
        printf("Erreur pendant l'allocation\n");
        return NULL;
    }
    
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
    if(url == NULL)
    {
        printf("Erreur pendant l'allocation\n");
        return NULL;
    }

	strncpy(url, start_url, url_len);
	url[url_len] = '\0';
	return url;
}

char *get_endpoint(const char buffer[BUFFER_SIZE])
{
    const char *start_endpoint = strstr(buffer, "/") + 1;
	const char *first_end = strstr(start_endpoint, "/");
    const char *second_end = strstr(start_endpoint, " H");
    const char *end_endpoint = (first_end - start_endpoint) < (second_end - start_endpoint) ? first_end : second_end;
	size_t endpoint_len = end_endpoint - start_endpoint;

	char *endpoint = (char*)malloc((endpoint_len + 1)*sizeof(char));
    if(endpoint == NULL)
    {
        printf("Erreur pendant l'allocation\n");
        return NULL;
    }

	strncpy(endpoint, start_endpoint, endpoint_len);
	endpoint[endpoint_len] = '\0';
	return endpoint;
}

char *getHTTPVersion(const char buffer[BUFFER_SIZE])
{
    const char *start_http = strstr(buffer, "H");
	const char *end_http = strstr(buffer, "\n");
	size_t http_len = end_http - start_http;

	char *http = (char*)malloc((http_len + 1)*sizeof(char));
    if(http == NULL)
    {
        printf("Erreur pendant l'allocation\n");
        return NULL;
    }

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

    if(header_attribute == NULL)
    {
        printf("Erreur pendant l'allocation\n");
        return NULL;
    }

    strncpy(header_attribute, ua_start, ua_len);
    header_attribute[ua_len] = '\0';
    
    return header_attribute;
}

char *getBody(const char buffer[BUFFER_SIZE])
{
    const char *start_body = strstr(buffer, "\r\n\r\n") + 4;
	const char *end_body = buffer + strlen(buffer);

    if(end_body != start_body)
    {
        return NULL;
    }

	size_t body_len = end_body - start_body;

	char *body = (char*)malloc((body_len + 1)*sizeof(char));
    if(body == NULL)
    {
        printf("Erreur pendant l'allocation\n");
        return NULL;
    }

	strncpy(body, start_body, body_len);
	body[body_len] = '\0';
	return body;
}
