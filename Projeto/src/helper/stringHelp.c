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

char *fgetLine(FILE *instream, char* retString, size_t stringLen) {
    if (!instream || !retString || stringLen <= 0) {
        return NULL;
    }
    char buf;
    int stringPos;
    for (stringPos = 0; stringPos < stringLen - 1; stringPos++) {
        buf = getc(instream);
        if (buf == '\n' || buf == '\r' || buf == EOF) {
            break;
        }
        retString[stringPos] = buf;
    }
    retString[stringPos] = '\0';
    return retString;
}