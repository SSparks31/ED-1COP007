#include "inputParser.h"

#include "stringHelp.h"
#include "mathHelp.h"

#include <string.h>

void commandParse(FILE *input, dataStoreT *dataStore) {
    if (!input || feof(input) || !dataStore) {
        return;
    }

    char command[1024], *argument = "";
    int id = -1;
    char *idOptions = "colwrf";
    while (!isEmpty(fgetLine(input, command, 1024))) {
        argument = findCharacter(command, ' ');
        *argument++ = '\0';

        if (findCharacter(idOptions, command[0])) {
            id = charToNum(argument[0]);
            argument = findCharacter(argument, ' ');
            if (argument) argument++;
        }

        if (strcmp(command, "+x") == 0) {
            commandParseSetX(dataStore, argument);
            for (char *x = dataStore->varX; *x; ++x) {
                printf("[%d]->", *x);
            }
            printf("%s\n", dataStore->varX);
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
            commandParseCreateFileC(dataStore, id);
        } else if (strcmp(command, "o") == 0) {
            commandParseCreateFileO(dataStore, id);
        } else if (strcmp(command, "l") == 0) {
            commandParseCreateFileL(dataStore, id);
        } else if (strcmp(command, "w") == 0) {
            commandParseWriteToFile(dataStore, id, argument);
        } else if (strcmp(command, "r") == 0) {
            commandParseReadFromFile(dataStore, id, argument);
        } else if (strcmp(command, "f") == 0) {
            commandParseCloseFile(dataStore, id);
        } else {
            printf("Erro: Comando %s nao encontrado", command);
            return;
        }
    }
}

int commandParseSetX(dataStoreT *dataStore, char *x) {
    if (!dataStore || isEmpty(x)) {
        return -1;
    }

    if (strcmp(x, "@1") == 0) {
        if (dataStore->numParameters >= 1) {
            setVarX(dataStore, getParam1(dataStore));
        } else {
            printf("Parametro @1 nao encontrado\n");
            return -1;
        }
    } else if (strcmp(x, "@2") == 0) {
        if (dataStore->numParameters >= 2) {
            setVarX(dataStore, getParam2(dataStore));
        } else {
            printf("Parametro @2 nao encontrado\n");
            return -1;
        }
    } else if (strcmp(x, "@3") == 0) {
        if (dataStore->numParameters >= 3) {
            setVarX(dataStore, getParam3(dataStore));
        } else {
            printf("Parametro @3 nao encontrado\n");
            return -1;
        }
    } else {
        setVarX(dataStore, stringStrip());
    }

    return 0;
}

int commandParseSetY(dataStoreT *dataStore, char *y) {
    if (!dataStore || isEmpty(y)) {
        return -1;
    }

    if (strcmp(y, "@1") == 0) {
        if (dataStore->numParameters >= 1) {
            setVarY(dataStore, getParam1(dataStore));
        } else {
            printf("Parametro @1 nao encontrado\n");
            return -1;
        }
    } else if (strcmp(y, "@2") == 0) {
        if (dataStore->numParameters >= 2) {
            setVarY(dataStore, getParam2(dataStore));
        } else {
            printf("Parametro @2 nao encontrado\n");
            return -1;
        }
    } else if (strcmp(y, "@3") == 0) {
        if (dataStore->numParameters >= 3) {
            setVarY(dataStore, getParam3(dataStore));
        } else {
            printf("Parametro @3 nao encontrado\n");
            return -1;
        }
    } else {
        setVarY(dataStore, stripQuotes(y, y));
    }

    return 0;
}

int commandParseSetZ(dataStoreT *dataStore, char *z) {
    if (!dataStore || isEmpty(z)) {
        return -1;
    }

    if (strcmp(z, "@1") == 0) {
        if (dataStore->numParameters >= 1) {
            setVarZ(dataStore, getParam1(dataStore));
        } else {
            printf("Parametro @1 nao encontrado\n");
            return -1;
        }
    } else if (strcmp(z, "@2") == 0) {
        if (dataStore->numParameters >= 2) {
            setVarZ(dataStore, getParam2(dataStore));
        } else {
            printf("Parametro @2 nao encontrado\n");
            return -1;
        }
    } else if (strcmp(z, "@3") == 0) {
        if (dataStore->numParameters >= 3) {
            setVarZ(dataStore, getParam3(dataStore));
        } else {
            printf("Parametro @3 nao encontrado\n");
            return -1;
        }
    } else {
        setVarZ(dataStore, stripQuotes(z, z));
    }

    return 0;
}

int commandParseClearX(dataStoreT *dataStore) {}
int commandParseClearY(dataStoreT *dataStore) {}
int commandParseClearZ(dataStoreT *dataStore) {}

int commandParseSetD(dataStoreT *dataStore, char *path) {}
int commandParseSetA(dataStoreT *dataStore, char *path) {}
int commandParseSetE(dataStoreT *dataStore, char *path) {}

int commandParseCreateFileC(dataStoreT *dataStore, int id) {}
int commandParseCreateFileO(dataStoreT *dataStore, int id) {}
int commandParseCreateFileL(dataStoreT *dataStore, int id) {}

int commandParseWriteToFile(dataStoreT *dataStore, int id, char *contents) {}
int commandParseReadFromFile(dataStoreT *dataStore, int id, char *store) {}
int commandParseCloseFile(dataStoreT *dataStore, int id) {}