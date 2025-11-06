#include "header.h"

void send_http_request(int sockfd, const url_t *url) {
    // DEBUG: Print what we're about to send
    // write(STDERR_FILENO, "SENDING REQUEST:\n", 17);
    // write(STDERR_FILENO, "GET ", 4);
    // write(STDERR_FILENO, url->path, my_strlen(url->path));
    // write(STDERR_FILENO, " HTTP/1.1\r\nHost: ", 17);
    // write(STDERR_FILENO, url->host, my_strlen(url->host));
    // write(STDERR_FILENO, "\r\nConnection: close\r\n\r\n", 23);
    // write(STDERR_FILENO, "END REQUEST\n", 12);


    write(sockfd, "GET ", 4);
    write(sockfd, url->path, my_strlen(url->path));
    write(sockfd, " HTTP/1.1\r\nHost: ", 17);
    write(sockfd, url->host, my_strlen(url->host));
    write(sockfd, "\r\nConnection: close\r\n\r\n", 23);
}

void receive_http_response(int sockfd) {
    char buffer[4096];
    ssize_t bytes_read;
    int in_body = 0;
    
    // Reading until server closes connection
    // while ((bytes_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
    //     if (in_body == 0) {
    //         char* body_start = my_strstr(buffer, "\r\n\r\n");

    //         if (body_start) {
    //             size_t skip = (body_start - buffer) + 4; // +8 for \r\n\r\n and hex digits
    //             write(STDOUT_FILENO, buffer + skip, bytes_read - skip);
    //             in_body = 1;
    //         }
    //     } else {
    //         write(STDOUT_FILENO, buffer, bytes_read); // skip last hex digit and new line
    //     }
        
    // }

    while ((bytes_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
        if (!in_body) {
            char* body_start = my_strstr(buffer, "\r\n\r\n");
            if (body_start) {
                // Skip chunk size lines by detecting hex digits at line starts
                char *content = body_start + 4;
                ssize_t content_len = bytes_read - (content - buffer);
                
                for (ssize_t i = 0; i < content_len; i++) {
                    if (i == 0 || (i >= 2 && content[i-2] == '\r' && content[i-1] == '\n')) {
                        if (my_isxdigit(content[i])) {
                            while (i < content_len && !(content[i] == '\r' && i+1 < content_len && content[i+1] == '\n')) {
                                i++;
                            }
                            if (i < content_len) i++; // Skip the \n
                            continue;
                        }
                    }
                    write(STDOUT_FILENO, &content[i], 1);
                }
                in_body = 1;
            }
        } else {
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
    }
}