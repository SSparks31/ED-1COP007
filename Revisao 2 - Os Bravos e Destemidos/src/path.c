#include "path.h"

#include <string.h>
#include "stringHelp.h"

#include <stdio.h>

char *getPath(char *res, char *fullPath) {
    if (!res) {
        return NULL;
    }

    if (isEmpty(fullPath) != 0) {
        strcpy(res, "");
        return res;
    }

    char *slashPosition = rfindCharacter(fullPath, '/');
    if (!slashPosition) {
        strcpy(res, "./");
        return res;
    }

    *slashPosition = '\0';
    strcpy(res, fullPath);
    *slashPosition = '/';

    return res;
}

char *getFileName(char *res, char *fullPath) {
    if (!res) {
        return NULL;
    }

    if (isEmpty(fullPath) != 0) {
        strcpy(res, "");
        return res;
    }

    char *slashPosition = rfindCharacter(fullPath, '/');
    if (!slashPosition) {
        strcpy(res, fullPath);
        return res;
    }

    strcpy(res, slashPosition + 1);
    
    return res;
}

char *getSuffix(char *res, char *fullPath) {
    if (!res) {
        return NULL;
    }

    if (isEmpty(fullPath) != 0) {
        strcpy(res, "");
        return res;
    }

    if (!getFileName(res, fullPath)) {
        strcpy(res, "");
        return res;
    }

    char *dotPosition = rfindCharacter(res, '.');
    if (!dotPosition) {
        strcpy(res, "");
        return res;
    }

    strcpy(res, dotPosition + 1);
    
    return res;
}

int hasSlash(char *path) {
    if (!path) {
        return -1;
    }
    return path[strlen(path) - 1] == '/';
}

char *concatFileSuffix(char *res, char *fileName, char *suffix) {
    if (!res) {
        return NULL;
    }

    if (isEmpty(fileName) != 0) {
        strcpy(res, "");
        return res;
    }

    if (isEmpty(suffix) != 0) {
        strcpy(res, fileName);
        return res;
    }

    strcpy(res, fileName);
    if (res[strlen(res) - 1] != '.' && suffix[0] != '.') {
        strcat(res, ".");
    }
    strcat(res, suffix);

    return res;
}

char *concatPathFile(char *res, char *path, char *fileName) {
    if (!res) {
        return NULL;
    }

    if (isEmpty(fileName) != 0) {
        strcpy(res, "");
        return res;
    }

    if (isEmpty(path) != 0) {
        char relativePath[3] = "./";
        path = relativePath;
    }

    if (findCharacter(fileName, '/') || getSuffix(res, path)[0]) {
        strcpy(res, "");
        return res;
    }

    strcpy(res, path);
    if (res[strlen(res - 1)] != '/' && fileName[0] != '/') {
        strcat(res, "/");
    }
    strcat(res, fileName);
    
    return res;
}
