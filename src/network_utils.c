#include "header.h"

int create_connection(const char *host, const char *port) {
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *result = NULL;
    struct addrinfo *rp = NULL;
    
    my_memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP socket
    hints.ai_protocol = IPPROTO_TCP; // TCP protocol
    
    // DNS LOOKUP
    int status = getaddrinfo(host, port, &hints, &result);
    if (status != 0) {
        // write(STDERR_FILENO, "DNS resolution failed: Site does not exist\n", 43);
        write(STDERR_FILENO, "could not resolve host: ", 24);
        write(STDERR_FILENO, host, my_strlen(host));
        write(STDOUT_FILENO, "\n", 1);
        return -1;
    }
    
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        // debug
        struct sockaddr_in *addr = (struct sockaddr_in *)rp->ai_addr;
        char ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(addr->sin_addr), ip_str, sizeof(ip_str));

        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1) continue;
        
        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1) {
            // write(STDOUT_FILENO, "SUCCESS: Connected to ", 22);
            // write(STDOUT_FILENO, ip_str, my_strlen(ip_str));
            // write(STDOUT_FILENO, ":", 1);
            // write(STDOUT_FILENO, port, my_strlen(port));
            // write(STDOUT_FILENO, "\n", 1);
            break;
        }
        
        close(sockfd); // Failed, try next address
    }
    
    freeaddrinfo(result);
    
    if (rp == NULL) {
        write(STDERR_FILENO, "Could not connect to any address\n", 33);
        return -1;
    }

    return sockfd;
}