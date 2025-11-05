#include "header.h"

// unsigned short my_htons(unsigned short hostshort) {
//     return (hostshort << 8) | (hostshort >> 8);
// }

// uint32_t my_inet_addr(const char *ip_str) {
//     uint32_t ip = 0;
//     const char *p = ip_str;
    
//     for (int i = 0; i < 4; i++) {
//         int octet = 0;
        
//         // Convert to int
//         while (*p >= '0' && *p <= '9') {
//             octet = octet * 10 + (*p - '0');
//             p++;
//         }
        
//         if (octet < 0 || octet > 255) {
//             return 0; // Invalid IP
//         }
        
//         ip = (ip << 8) | (octet & 0xFF);
        
//         // Skip the dot
//         if (i < 3) {
//             if (*p != '.') return 0;
//             p++;
//         }
//     }
    
//     if (*p != '\0') return 0;
    
//     return ip;
// }

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
        write(STDERR_FILENO, "DNS resolution failed: Site does not exist\n", 43);
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
            printf("SUCCESS: Connected to %s:%s\n", ip_str, port); // DEBUG
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