#include "stringSearch.h"

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