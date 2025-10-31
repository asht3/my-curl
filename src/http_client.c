#include "header.h"

void send_http_request(int sockfd, const url_t *url);
void receive_http_response(int sockfd);
void print_response_body(const char *response);