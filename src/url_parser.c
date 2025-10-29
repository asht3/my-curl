#include "header.h"

int parse_url(const char *url, url_t *parsed) {
    // Find the scheme separator
    char* scheme_end = strstr(url, "://"); // TODO: replace strstr with own implementation
    // char scheme[10] = "http";

    if (scheme_end) {
        // strncpy(scheme, url, scheme_end - url); // TODO: replace with own implementation
        // scheme[scheme_end - url] = '\0';
        url += (scheme_end - url) + 3;
    }

    const char *current_pos = url;
    
    // Parse host
    get_host(current_pos, parsed);
    
    // Update current position after host
    current_pos += strlen(parsed->host);
    
    // Parse port
    if (*current_pos == ':') {
        get_port(parsed, current_pos);
        current_pos += 1 + strlen(parsed->port); // : + port
    } else {
        strcpy(parsed->port, "80");
    }
    
    // Parse path
    if (*current_pos == '/') {
        get_path(current_pos, parsed);
        current_pos += strlen(parsed->path);
    } else {
        strcpy(parsed->path, "/");
    }
    
    // Parse query
    if (*current_pos == '?') {
        get_query(current_pos, parsed);
        current_pos += 1 + strlen(parsed->query); // ? + query
    } else {
        strcpy(parsed->query, "");
    }
    
    // Parse fragment
    if (*current_pos == '#') {
        get_fragment(current_pos, parsed);
    } else {
        strcpy(parsed->fragment, "");
    }

    // DEBUG
    printf("Host: %s\n", parsed->host);
    printf("Port: %s\n", parsed->port);
    printf("Path: %s\n", parsed->path);
    printf("Query: %s\n", parsed->query);
    printf("Fragment: %s\n", parsed->fragment);

    return 0;
}

void get_host(const char *url, url_t *parsed) {
    const char *ptr = url;
    while (*ptr && *ptr != ':' && *ptr != '/' && *ptr != '?' && *ptr != '#') {
        ptr++;
    }
    
    size_t host_len = ptr - url;
    if (host_len > 0 && host_len < sizeof(parsed->host)) {
        strncpy(parsed->host, url, host_len);
        parsed->host[host_len] = '\0';
    } else {
        strcpy(parsed->host, "");
    }
}

void get_port(url_t *parsed, const char *port_start) {
    const char *ptr = port_start + 1; // Skip the ':'
    const char *port_begin = ptr;
    
    while (*ptr && *ptr != '/' && *ptr != '?' && *ptr != '#') {
        ptr++;
    }
    
    size_t port_len = ptr - port_begin;
    if (port_len > 0 && port_len < sizeof(parsed->port)) {
        strncpy(parsed->port, port_begin, port_len);
        parsed->port[port_len] = '\0';
    } else {
        strcpy(parsed->port, "80");
    }
}

void get_path(const char *path_start, url_t *parsed) {
    const char *ptr = path_start;
    const char *path_begin = ptr;
    
    while (*ptr && *ptr != '?' && *ptr != '#') {
        ptr++;
    }
    
    size_t path_len = ptr - path_begin;
    if (path_len > 0 && path_len < sizeof(parsed->path)) {
        strncpy(parsed->path, path_begin, path_len);
        parsed->path[path_len] = '\0';
    } else {
        strcpy(parsed->path, "/");
    }
}

void get_query(const char *query_start, url_t *parsed) {
    const char *ptr = query_start + 1; // Skip the '?'
    const char *query_begin = ptr;
    
    while (*ptr && *ptr != '#') {
        ptr++;
    }
    
    size_t query_len = ptr - query_begin;
    if (query_len > 0 && query_len < sizeof(parsed->query)) {
        strncpy(parsed->query, query_begin, query_len);
        parsed->query[query_len] = '\0';
    } else {
        strcpy(parsed->query, "");
    }
}

void get_fragment(const char *fragment_start, url_t *parsed) {
    const char *fragment_begin = fragment_start + 1; // Skip the '#'
    
    size_t frag_len = strlen(fragment_begin);
    if (frag_len > 0 && frag_len < sizeof(parsed->fragment)) {
        strcpy(parsed->fragment, fragment_begin);
    } else {
        strcpy(parsed->fragment, "");
    }
}