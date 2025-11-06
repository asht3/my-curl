#include "header.h"

void send_http_request(int sockfd, const url_t *url) {
    write(sockfd, "GET ", 4);
    write(sockfd, url->path, strlen(url->path));
    write(sockfd, " HTTP/1.1\r\nHost: ", 17);
    write(sockfd, url->host, strlen(url->host));
    write(sockfd, "\r\nConnection: close\r\n\r\n", 23);
}

void receive_http_response(int sockfd) {
    char buffer[4096];
    ssize_t bytes_read;
    int in_body = 0;

    // while ((bytes_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
    //     write(STDOUT_FILENO, "=== RAW ===\n", 12);
    //     write(STDOUT_FILENO, buffer, bytes_read);
    //     write(STDOUT_FILENO, "=== END ===\n", 12);
    // }
    
    // Reading until server closes connection
    while ((bytes_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
        if (in_body == 0) {
            char* body_start = my_strstr(buffer, "\r\n\r\n");

            if (body_start) {
                size_t skip = (body_start - buffer) + 8; // +8 for \r\n\r\n and hex digits
                write(STDOUT_FILENO, buffer + skip, bytes_read - skip);
                in_body = 1;
            }
        } else {
            write(STDOUT_FILENO, buffer, bytes_read - 3); // skip last hex digit and new line
        }
        
    }
}