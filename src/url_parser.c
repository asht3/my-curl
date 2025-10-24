#include "header.h"


int parse_url(const char *url, url_t *parsed) {
    // Find the scheme separator
    char* scheme_end = strstr(url, "://"); // TODO: replace strstr with own implementation
    char scheme[10];

    if (scheme_end) {
        strncpy(scheme, url, scheme_end - url); // TODO: replace with own implementation
        scheme[scheme_end - url] = '\0';
        url += (scheme_end - url) + 3;
    } else {
        // Default to http
        strcpy(scheme, ""); // TODO: replace with own implementation
    }

    const char *path_start = strchr(url, '/'); // TODO: replace with own implementation
    const char *port_start = strchr(url, ':'); // TODO: replace with own implementation
    
    get_host(url, parsed, path_start);
    get_port(url, parsed, path_start, port_start);
    
    const char *query_start = strchr(url, '?');
    get_path(url, parsed, query_start);

    const char *fragment_start = strchr(url, '#');
    get_query_and_fragments(url, parsed, query_start, fragment_start);

    // DEBUG
    printf("Scheme: %s\n", scheme);
    printf("Host: %s\n", parsed->host);
    printf("Port: %d\n", parsed->port);
    printf("Path: %s\n", parsed->path);
    printf("Query: %s\n", parsed->query);
    printf("Fragment: %s\n", parsed->fragment);

    return 0;
}

void get_host(const char *url, url_t *parsed, const char *path_start) {
    if (path_start) {
        strncpy(parsed->host, url, path_start - url); // TODO: replace with own implementation
        parsed->host[path_start - url] = '\0';
        url = path_start;
    } else {
        strcpy(parsed->host, url);
        url = "";
    }
}

void get_port(const char *url, url_t *parsed, const char *path_start, const char port_start) {
    if (port_start && port_start < path_start) {
        *parsed->port = atoi(port_start + 1); // TODO: replace with own implementation
        strncpy(parsed->host, url, port_start - *url); // TODO: replace with own implementation
        parsed->host[port_start - *url] = '\0';
    } else {
        strcpy(parsed->port, 80); // TODO: replace with own implementation
    }
}

void get_path(const char *url, url_t *parsed, const char *query_start) {
    if (query_start) {
        strncpy(parsed->path, url, query_start - url);
        parsed->path[query_start - url] = '\0';
        url = query_start + 1; // Move to query
    } else {
        strcpy(parsed->path, url);
        url = "";
    }
}

void get_query_and_fragments(const char *url, url_t *parsed, const char *query_start, const char *fragment_start) {
    if (fragment_start) {
        strncpy(parsed->query, url, fragment_start - url);
        parsed->query[fragment_start - url] = '\0';
        strcpy(parsed->fragment, fragment_start + 1);
    } else {
        strcpy(parsed->query, url);
        strcpy(parsed->fragment, "");
    }
}