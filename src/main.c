#include "header.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        write(STDERR_FILENO, "Usage: my_curl <URL>\n", 21);
        return -1;
    }

    // Parse URL
    url_t parsed_url;
    if (parse_url(argv[1], &parsed_url) == -1) {
        write(STDERR_FILENO, "Failed to parse URL\n", 20);
        return -1;
    }

    // Create connection
    int sockfd = create_connection(parsed_url.host, parsed_url.port);
    if (sockfd < 0) {
        return -1;
    }

    // Send HTTP request
    send_http_request(sockfd, &parsed_url);

    // Receive HTTP response
    receive_http_response(sockfd);
    
    close(sockfd);
    
    return 0;
}