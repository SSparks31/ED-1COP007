#include "revisaoEx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* rfindCharacter(char *string, char query) { 
    /* Encontra ultima aparicao do caracter query em uma dada string */
    /* Caso string seja vazia ou invalida, retorna NULL */
    /* Caso query nao exista na string, retorna NULL */
    /* Retorna ponteiro para caracter na string */

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
    /* Retorna 0 caso string seja vazia ou NULL; caso contrário, retorna 1 */
    return string && strlen(string) != 0;
}

char *getPath(char *fullPath) {
    if (!validString(fullPath)) { /* String invalida ou vazia*/
        return NULL;
    }

    char *path = NULL;
    char *slashPosition = rfindCharacter(fullPath, '/');
    if (!slashPosition) { /* Nao ha barra no nome, nao inclui caminho */
        path = malloc(sizeof(char)); 
        strcpy(path, "");
    } else {
        size_t pathSize = strlen(fullPath) - strlen(slashPosition);
        path = malloc(sizeof(char) * pathSize); /* Path recebera todos os caracteres de fullPath antes de slashPosition, mais \0 */
        strncpy(path, fullPath, pathSize);
        path[pathSize] = '\0';
    }

    return path;
}

char *getFileName(char *fullPath) {
    if (!validString(fullPath)) { /* String invalida ou vazia */
        return NULL;
    }

    char *name = NULL;
    char *slashPosition = rfindCharacter(fullPath, '/');
    if (!slashPosition) {
        name = malloc(sizeof(char) * strlen(fullPath));
        strcpy(name, fullPath); // Nao copiar '/'
    } else {
        name = malloc(sizeof(char) * strlen(slashPosition));
        strcpy(name, slashPosition + 1);
    }

    return name;
}

char *getSuffix(char *name) {
    if (!validString(name)) { /* String invalida */
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
    size_t pathSize = 1; /* Espaco para \0 alocado no inicio */
    if (validString(path)) {
        pathSize += strlen(path) + !hasSlash(path);
    }
    if (validString(fileName)) {
        pathSize += strlen(fileName);
        if (!validString(path)) { /* Name valido e path invalido, tratar como caminho relativo */
            pathSize += strlen("./");
        }
    }

    if (pathSize == 1) { /* Tanto path quanto filename sao invalidos */
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