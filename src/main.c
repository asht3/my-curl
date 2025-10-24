#include "header.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        write(STDERR_FILENO, "Usage: my_curl <URL>\n", 20);
        return -1;
    }

    // Parse URL

    // Create connection

    // Send HTTP request

    // Receive HTTP response
    
    return 0;
}