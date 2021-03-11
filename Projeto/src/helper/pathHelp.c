#include "./pathHelp.h"

#include <stdlib.h>
#include <string.h>

#include "./stringHelp.h"

char* getPath(char* fullPath) {
    if (isEmpty(fullPath)) {
        return NULL;
    }
    
    char* slashPos = rfindCharacter(fullPath, '/');
    if (!slashPos) {
        return "";
    }

    int pathLen = strlen(fullPath) - strlen(slashPos);
    char* path = malloc(sizeof(char) * (pathLen + 1));
    strncpy(path, fullPath, pathLen);
    path[pathLen] = '\0';

    return path;
}

char* getFileName(char* fullPath) {
    if (isEmpty(fullPath)) {
        return NULL;
    }

    char* slashPos = rfindCharacter(fullPath, '/');
    if (!slashPos) {
        slashPos = fullPath - 1;
    }

    int nameLen = strlen(slashPos);
    char* name = malloc(sizeof(char) * (nameLen));
    strcpy(name, slashPos + 1);

    return name;
}

char* getSuffix(char* name) {
    if (isEmpty(name)) {
        return NULL;
    }

    char* dotPos = rfindCharacter(name, '.');
    if (!dotPos) {
        return "";
    }

    int suffixLen = strlen(dotPos);
    char* suffix = malloc(sizeof(char) * (suffixLen));
    strcpy(suffix, dotPos + 1);

    return suffix;
}

int hasSlash(char* path) {
    if (isEmpty(path)) {
        return -1;
    }

    return path[strlen(path) - 1] == '/';
}

char* concatPathFile(char *path, char* fileName) {
    size_t pathSize = 0;
    if (!isEmpty(path)) {
        pathSize += strlen(path);
    }
    if (!isEmpty(fileName)) {
        pathSize += strlen(fileName);
    }

    if (!pathSize) {
        return NULL;
    }

    if (pathSize == strlen(fileName)) {
        pathSize += strlen(".");
    }

    char* fullPath = malloc(sizeof(char) * (pathSize + !hasSlash(path) + 1));
    if (isEmpty(path)) {
        strcpy(fullPath, ".");
    } else {
        strcpy(fullPath, path);
    }
    if (!hasSlash(fullPath)) {
        strcat(fullPath, "/");
    } 
    strcat(fullPath, fileName);
    
    return fullPath;
}