#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
    char host[256];
    char port[8];
    char path[1024];
    char query[256];
    char fragment[256];
} url_t;

// url_parser.c
int parse_url(const char *url, url_t *parsed);
void get_host(const char *url, url_t *parsed);
void get_port(url_t *parsed, const char *current_pos);
void get_path(const char *url, url_t *parsed);
void get_query(const char *url, url_t *parsed);
void get_fragment(const char *url, url_t *parsed);

unsigned short my_htons(unsigned short hostshort);
uint32_t my_inet_addr(const char *ip_str);
int create_connection(const char *host, const char *port);
void send_http_request(int sockfd, const url_t *url);
void receive_http_response(int sockfd);
void print_response_body(const char *response);

// Helper functions
int my_strlen(const char* str_1);
char* my_strstr(const char* haystack, const char* needle);
char* my_strcpy(char* dest, const char* src);
char* my_strncpy(char* str_1, const char* str_2, int length);

#endif