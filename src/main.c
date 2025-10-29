#include "header.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        write(STDERR_FILENO, "Usage: my_curl <URL>\n", 20);
        return -1;
    }

    // Parse URL
    url_t parsed_url;
    if (parse_url(argv[1], &parsed_url) == -1) {
        write(STDERR_FILENO, "Failed to parse URL\n", 20);
        return -1;
    }

    // Create connection

    // Send HTTP request

    // Receive HTTP response
    
    return 0;
}