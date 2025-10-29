#include "header.h"

int my_strlen(const char* str_1) {
    int length = 0;

    while (*str_1 != '\0') {
        length++;
        str_1++;
    }

    return length;
}

char* my_strstr(const char* haystack, const char* needle) {
    if (*needle == '\0') {
        return (char*)haystack;
    }

    for (; *haystack != '\0'; haystack++) {
        const char* h = haystack;
        const char* n = needle;

        while (*h != '\0' && *n != '\0' && *h == *n) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char*)haystack;
        }
    }

    return NULL;
}

char* my_strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original_dest;
}

char* my_strncpy(char* str_1, const char* str_2, int length) {
    int i;
    for (i = 0; i < length && str_2[i] != '\0'; i++) {
        str_1[i] = str_2[i];
    }
    
    str_1[i] = '\0';

    return str_1;
}