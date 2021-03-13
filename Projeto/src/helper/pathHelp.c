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
        return calloc(1, sizeof(char));
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
    char* fileName = malloc(sizeof(char) * (nameLen));
    strcpy(fileName, slashPos + 1);

    return fileName;
}

char* getSuffix(char* fileName) {
    if (isEmpty(fileName)) {
        return NULL;
    }

    char* dotPos = rfindCharacter(fileName, '.');
    if (!dotPos) {
        return calloc(1, sizeof(char));
    }

    int suffixLen = strlen(dotPos);
    char* suffix = malloc(sizeof(char) * (suffixLen));
    strcpy(suffix, dotPos + 1);

    return suffix;
}

char* stripSuffix(char* fileName) {
    if (isEmpty(fileName)) {
        return NULL;
    }

    char* dotPos = findCharacter(fileName, '.');

    if (!dotPos) {
        char* emptyString = "";
        dotPos = emptyString;
    }

    int nameLen = strlen(fileName) - strlen(dotPos);
    char* noSuffix = malloc(sizeof(char) * (nameLen + 1));
    if (!noSuffix) {
        return NULL;
    }

    strncpy(noSuffix, fileName, nameLen);
    noSuffix[nameLen] = '\0';

    return noSuffix;
}

int hasSlash(char* path) {
    if (isEmpty(path)) {
        return -1;
    }

    return path[strlen(path) - 1] == '/';
}

char* concatPathFile(char* path, char* fileName) {
    if (isEmpty(fileName)) {
        return NULL;
    }

    char* format;
    if (isEmpty(path)) {
        char* relPath = "./";
        path = relPath;        
    } 
    
    if (hasSlash(path)) {
        format = "%s%s";
    } else {
        format = "%s/%s";
    }

    char* fullPath = malloc(strlen(path) + !hasSlash(path) + strlen(fileName) + 1);
    sprintf(fullPath, format, path, fileName);

    return fullPath;
}

char* concatFileSuffix(char* fileName, char* suffix) {
    if (isEmpty(fileName)) {
        return NULL;
    }

    char* fullName;
    if (isEmpty(suffix)) {
        fullName = malloc(sizeof(char) * (strlen(fileName) + 1));
        strcpy(fullName, fileName);
        return fullName;
    }

    fullName = malloc(sizeof(char) * (strlen(fileName) + strlen(".") + strlen(suffix) + 1));
    sprintf(fullName, "%s.%s", fileName, suffix);

    return fullName;
}