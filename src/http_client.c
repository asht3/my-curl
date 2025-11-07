#include "header.h"

void send_http_request(int sockfd, const url_t *url) {
    write(sockfd, "GET ", 4);
    write(sockfd, url->path, my_strlen(url->path));
    write(sockfd, " HTTP/1.1\r\nHost: ", 17);
    write(sockfd, url->host, my_strlen(url->host));
    write(sockfd, "\r\nConnection: close\r\n\r\n", 23);
}

void receive_http_response(int sockfd) {
    char buffer[4096];
    ssize_t bytes_read;
    
    // Detect headers
    bytes_read = read(sockfd, buffer, sizeof(buffer));
    if (bytes_read <= 0) return;
    
    char* body_start = my_strstr(buffer, "\r\n\r\n");
    if (body_start) {
        size_t skip = (body_start - buffer) + 4;
        write(STDOUT_FILENO, body_start + 4, bytes_read - skip);
    }
    
    // Read remaining data
    while ((bytes_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
}

void skip_hex(ssize_t bytes_read, char* buffer) {
    for (ssize_t i = 0; i < bytes_read; i++) {
        if (i == 0 || (i >= 2 && buffer[i-2] == '\r' && buffer[i-1] == '\n')) {
            if (my_isxdigit(buffer[i])) {
                while (i < bytes_read && !(buffer[i] == '\r' && i+1 < bytes_read && buffer[i+1] == '\n')) {
                    i++;
                }
                if (i < bytes_read) i++;
                continue;
            }
        }
        write(STDOUT_FILENO, &buffer[i], 1);
    }
}