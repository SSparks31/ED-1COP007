#include "path.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringHelp.h"

char *getPath(char *fullPath) {
    if (!validString(fullPath)) { 
        return NULL;
    }

    char *path = NULL;
    char *slashPosition = rfindCharacter(fullPath, '/');
    
    if (!slashPosition) { 
        path = malloc(sizeof(char)); 
        strcpy(path, "");
    } else {
        size_t pathSize = strlen(fullPath) - strlen(slashPosition);
        path = malloc(sizeof(char) * pathSize); 
        strncpy(path, fullPath, pathSize);
        path[pathSize] = '\0';
    }

    return path;
}

char *getFileName(char *fullPath) {
    if (!validString(fullPath)) { 
        return NULL;
    }

    char *name = NULL;
    char *slashPosition = rfindCharacter(fullPath, '/');
    if (!slashPosition) {
        name = malloc(sizeof(char) * strlen(fullPath));
        strcpy(name, fullPath); 
    } else {
        name = malloc(sizeof(char) * strlen(slashPosition));
        strcpy(name, slashPosition + 1);
    }

    return name;
}

char *getSuffix(char *name) {
    if (!validString(name)) { 
        return NULL;
    }

    char *suffix = NULL;
    char *dotPosition = rfindCharacter(name, '.');
    if (!dotPosition) {
        suffix = malloc(1);
        strcpy(suffix, "");
    } else {
        suffix = malloc(strlen(dotPosition));
        strcpy(suffix, dotPosition + 1);
    }
     
    return suffix;
}

int hasSlash(char *path) {
    if (!validString(path)) {
        return -1;
    }
    return path[strlen(path) - 1] == '/';
}

char *concatPathFile(char *path, char *fileName) {
    size_t pathSize = 1; 
    if (validString(path)) {
        pathSize += strlen(path) + !hasSlash(path);
    }
    if (validString(fileName)) {
        pathSize += strlen(fileName);
        if (!validString(path)) {
            pathSize += strlen("./");
        }
    }

    if (pathSize == 1) {
        return NULL;
    }
    
    char *fullPath = malloc(sizeof(char) * pathSize);

    if (validString(path)) {
        strcpy(fullPath, path);
        if (!hasSlash(path)) {
            strcat(fullPath, "/");
        }
    } else {
        strcpy(fullPath, "./");
    }
    if (validString(fileName)) {
        strcat(fullPath, fileName);
    }

    return fullPath;    
}