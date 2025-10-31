#include "header.h"

unsigned short my_htons(unsigned short hostshort) {
    return (hostshort << 8) | (hostshort >> 8);
}

uint32_t my_inet_addr(const char *ip_str) {
    uint32_t ip = 0;
    const char *p = ip_str;
    
    for (int i = 0; i < 4; i++) {
        int octet = 0;
        
        // Convert to int
        while (*p >= '0' && *p <= '9') {
            octet = octet * 10 + (*p - '0');
            p++;
        }
        
        if (octet < 0 || octet > 255) {
            return 0; // Invalid IP
        }
        
        ip = (ip << 8) | (octet & 0xFF);
        
        // Skip the dot
        if (i < 3) {
            if (*p != '.') return 0;
            p++;
        }
    }
    
    if (*p != '\0') return 0;
    
    return ip;
}

int create_connection(const char *host, const char *port) {
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *result = NULL;
    struct addrinfo *rp = NULL;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP socket
    hints.ai_protocol = IPPROTO_TCP; // TCP protocol
    
    // DNS LOOKUP
    int status = getaddrinfo(host, port, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "DNS resolution failed: %s\n", gai_strerror(status));
        return -1;
    }
    
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        // debug
        struct sockaddr_in *addr = (struct sockaddr_in *)rp->ai_addr;
        char ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(addr->sin_addr), ip_str, sizeof(ip_str));

        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol); // not debug
        if (sockfd == -1) continue;
        
        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1) {
            printf("SUCCESS: Connected to %s:%s\n", ip_str, port);
            break;
        }
        
        close(sockfd); // Failed, try next address
    }
    
    freeaddrinfo(result);
    
    if (rp == NULL) {
        fprintf(stderr, "Could not connect to any address\n");
        return -1;
    }

    return sockfd;
}

// int create_connection(const char *host, const char *port) {
//     int sockfd;
//     struct sockaddr_in server_addr;
//     uint32_t ip_addr = my_inet_addr(host);
//     unsigned short port_num = (unsigned short)atoi(port); // TODO: replace atoi with custom

//     if (ip_addr == 0) {
//         write(STDERR_FILENO, "Invalid IP address\n", 19);
//         return -1;
//     }

//     sockfd = socket(AF_INET, SOCK_STREAM, 0);
//     if (sockfd < 0) {
//         write(STDERR_FILENO, "Socket creation failed\n", 23);
//         return -1;
//     }

//     memset(&server_addr, 0, sizeof(server_addr)); // TODO: replace memset with custom
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = my_htons(ip_addr);
//     server_addr.sin_port = my_htons(port_num);

//     if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
//         write(STDERR_FILENO, "Connection failed\n", 17);
//         close(sockfd);
//         return -1;
//     }
    
//     //Debug print results
//     printf("Connected to %s:%s\n", host, port);

//     return sockfd; // placeholder
// }