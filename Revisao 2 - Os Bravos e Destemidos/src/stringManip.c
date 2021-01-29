#include "stringManip.h"

#include <string.h>

char* findCharacter(char *string, char query) { 
    if (!string || strlen(string) == 0) {
        return NULL;
    }

    for (char *i = string; i < string + strlen(string); ++i) { /* Aritmetica de ponteiro para visualizar cada posicao individualmente */
        if (*i == query) {
            return i;
        }
    }

    return NULL; /* Saiu do loop, query nao foi encontrado */
}

char* rfindCharacter(char *string, char query) { 
    if (!string || strlen(string) == 0) {
        return NULL;
    }

    for (char *i = string + strlen(string); i >= string; --i) { /* Aritmetica de ponteiro para visualizar cada posicao individualmente */
        if (*i == query) {
            return i;
        }
    }

    return NULL; /* Saiu do loop, query nao foi encontrado */
}

int validString(char* string) {
    return string && strlen(string) != 0;
}