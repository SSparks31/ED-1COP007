#include "commandParse.h"

#include <stdlib.h>

int charToInt(char num) {
    if (num < '0' || num > '9') {
        return -1;
    }
    return num - '0';
}

int commandParse(FILE *input, dataStoreT *dataStore) {
    if (!input || feof(input) || !dataStore) {
        return -1;
    }
    char command[3] = "", *argument = malloc(sizeof(char));
    strcpy(argument, "");

    char buf;
    int i = 0;
    while ((buf = fgetc(input)) != ' ') {
        command[i++] = buf;
    }

    i = 1;
    while ((buf = fgetc(input)) != '\n' && buf != EOF) {
        argument[i - 1] = buf;
        argument = realloc(argument, sizeof(char) * ++i);
    }
    argument[i - 1] = '\0';

    if (strcmp(command, "+x") == 0) {
        commandParseSetX(dataStore, argument);
    } else if (strcmp(command, "+y") == 0) {
        commandParseSetY(dataStore, argument);
    } else if (strcmp(command, "+z") == 0) {
        commandParseSetZ(dataStore, argument);
    } else if (strcmp(command, "x") == 0) {
        commandParseClearX(dataStore);
    } else if (strcmp(command, "y") == 0) {
        commandParseClearY(dataStore);
    } else if (strcmp(command, "z") == 0) {
        commandParseClearZ(dataStore);
    } else if (strcmp(command, "d") == 0) {
        commandParseSetD(dataStore, argument);
    } else if (strcmp(command, "a") == 0) {
        commandParseSetA(dataStore, argument);
    } else if (strcmp(command, "e") == 0) {
        commandParseSetE(dataStore, argument);
    } else if (strcmp(command, "c") == 0) {
        int id = charToInt(argument[0]);
        commandParseCreateFileC(dataStore, id);
    } else if (strcmp(command, "o") == 0) {
        int id = charToInt(argument[0]);
        commandParseCreateFileO(dataStore, id);
    } else if (strcmp(command, "l") == 0) {
        int id = charToInt(argument[0]);
        commandParseCreateFileL(dataStore, id);
    } else if (strcmp(command, "w") == 0) {
        int id = charToInt(argument[0]);
        argument += 2; /* Avancar argument para nao incluir id e espaco */
        commandParseWriteToFile(dataStore, id, argument);
    } else if (strcmp(command, "r") == 0) {
        int id = charToInt(argument[0]);
        argument += 2; /* Avancar argument para nao incluir id e espaco */
        commandParseReadFromFile(dataStore, id, argument);
    } else if (strcmp(command, "f") == 0) {
        int id = charToInt(argument[0]);
        commandParseCloseFile(dataStore, id);
    } else {
        printf("Erro: Comando %s nao encontrado", command);
    }
}

int commandParseSetX(dataStoreT *dataStore, char *x);
int commandParseSetY(dataStoreT *dataStore, char *y);
int commandParseSetZ(dataStoreT *dataStore, char *z);

int commandParseClearX(dataStoreT *dataStore);
int commandParseClearY(dataStoreT *dataStore);
int commandParseClearZ(dataStoreT *dataStore);

int commandParseSetD(dataStoreT *dataStore, char *path);
int commandParseSetA(dataStoreT *dataStore, char *path);
int commandParseSetE(dataStoreT *dataStore, char *path);

int commandParseCreateFileC(dataStoreT *dataStore, int id);
int commandParseCreateFileO(dataStoreT *dataStore, int id);
int commandParseCreateFileL(dataStoreT *dataStore, int id);

int commandParseWriteToFile(dataStoreT *dataStore, int id, char *contents);
int commandParseReadFromFile(dataStoreT *dataStore, int id, char *store);
int commandParseCloseFile(dataStoreT *dataStore, int id);