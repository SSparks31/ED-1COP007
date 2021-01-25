#include "revisaoEx.h"

char *getPath(char *fullPath) {
    if (!fullPath) { /* String invalida */
        return NULL;
    }

    size_t pathSize;
    for (pathSize = strlen(fullPath); pathSize >= 0; --pathSize) { /* Percorrer string do final ao comeco para encontrar caracter '/' */
        if (fullPath[pathSize] == '/') { 
            break; /* Caracter encontrado, encerrar loop */
        }
    }

    char *path = calloc(1, sizeof(char) * (pathSize + 1)); /* Ultima barra foi encontrada na posicao pathSize, portanto ha pathSize + 1 caracteres */
    if (!path) { /* Nao foi possivel alocar memoria para path */
        return NULL;
    }

    strncpy(path, fullPath, pathSize); /* Copiar pathSize caracteres da string original para o resultado */
    path[pathSize] = '\0'; /* Barra sera substituida por \0 para terminar a string */
    return path;
}

char *getFileName(char *fullPath) {
    if (!fullPath) { /* String invalida */
        return NULL;
    }

    size_t i, pathSize = strlen(fullPath);
    for (i = 0; i < pathSize; ++i) { /* Percorrer string do final ao comeco para encontrar caracter '/' */
        if (fullPath[pathSize - i] == '/') { 
            break; /* Caracter encontrado, encerrar loop */
        }
    }

    char *fileName = calloc(1, sizeof(char) * i); /* Barra foi encontrada i caracteres antes do final da string, portanto ha i - 1 caracteres */
    if (!fileName) { /* Nao foi possivel alocar memoria para fileName */
        return NULL;
    }

    strcpy(fileName, fullPath + (pathSize - (i - 1))); /* Copiar ultimos i - 1 caracteres, incluindo /0, da string original para o resultado */
    return fileName;
}

char *getSuffix(char *name) {
    if (!name) { /* String invalida */
        return NULL;
    }

    size_t i, pathSize = strlen(name);
    for (i = 0; i < pathSize; ++i) { /* Percorrer string do final ao comeco para encontrar caracter '.' */
        if (name[pathSize - i] == '.') { 
            break; /* Caracter encontrado, encerrar loop */
        }
    }

    char *suffix = calloc(1, sizeof(char) * i); /* Ponto foi encontrado i caracteres antes do final da string, portanto ha i - 1 caracteres */
    if (!suffix) { /* Nao foi possivel alocar memoria para suffix */
        return NULL;
    }

    strcpy(suffix, name + (pathSize - (i - 1))); /* Copiar ultimos i - 1 caracteres, incluindo /0, da string original para o resultado */
    return suffix;
}

int hasSlash(char *path) {
    return path[strlen(path) - 1] == '/';
}

char *concatPathFile(char *path, char *fileName) {
    if (!path || !fileName) { /* String invalida */
        return NULL;
    }

    char *fullPath = calloc(1, sizeof(char) * (strlen(path) + !hasSlash(path) + strlen(fileName) + 1)); /* Tamanho total do resultado = tamanho do path + 1 se path nao termina em / + tamanho do filename + 1 para o caracter de termino */
    if (!fullPath) { /* Nao foi possivel alocar memoria para fullPath */
        return NULL;
    }

    strcpy(fullPath, path); /* Copiar path para resultado */
    if (!hasSlash(path)) {
        strcat(fullPath, "/"); /* Adicionar barra caso ja nao haja */
    }
    strcat(fullPath, fileName); /* Adicionar filename para resultado*/
    return fullPath;
}