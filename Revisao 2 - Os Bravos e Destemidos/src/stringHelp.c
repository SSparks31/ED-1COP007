#include "stringHelp.h"

#include <string.h>

char *findCharacter(char *str, char query) {
    if (!str) {
        return NULL;
    }
    for (; *str; ++str) {
        if (*str == query) {
            return str;
        }
    }
    return NULL;
}

char *rfindCharacter(char *str, char query) {
    if (!str) {
        return NULL;
    }
    char *aux = str + strlen(str);
    for (; aux != str; --aux) {
        if (*aux == query) {
            return aux;
        }
    }
    return NULL;
}

int isEmpty(char *str) {
    if (!str) {
        return -1;
    }
    return strlen(str) == 0;
}

char *stripQuotes(char *res, char *str) {
    if (!res) {
        return NULL;
    }
    
    if (isEmpty(str)) {
        strcpy(res, "");
        return res;
    }

    if (str[0] == '"') {
        ++str;
    }
    
    strcpy(res, str);
    
    if (res[strlen(res) - 1] == '"') {
        res[strlen(res) - 1] = '\0';
    }

    return res;
}