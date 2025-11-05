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
    
    // Reading until server closes connection
    while ((bytes_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    // (void) sockfd; // Debug
    // printf("Receiving http response (not implemented)\n");

}

// void print_response_body(const char *response) {
//     const char* body = my_strstr(response, "\r\n\r\n");

//     if (body != NULL) {
//         body += 4; // Skip delimiter
//         write(STDOUT_FILENO, body, my_strlen(body));
//     } else {
//         write(STDOUT_FILENO, "No body found in the response:\n", 31);
//         write(STDOUT_FILENO, response, my_strlen(response));
//     }
// }