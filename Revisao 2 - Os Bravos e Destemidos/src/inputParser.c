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
        setVarX(dataStore, getParam1(dataStore));
    } else if (strcmp(x, "@2") == 0) {
        setVarX(dataStore, getParam2(dataStore));
    } else if (strcmp(x, "@3") == 0) {
        setVarX(dataStore, getParam3(dataStore));
    } else {
        setVarX(dataStore, stripQuotes(x, x));
    }

    return 0;
}

int commandParseSetY(dataStoreT *dataStore, char *y) {
    if (!dataStore || isEmpty(y)) {
        return -1;
    }

    if (strcmp(y, "@1") == 0) {
        setVarY(dataStore, getParam1(dataStore));
    } else if (strcmp(y, "@2") == 0) {
        setVarY(dataStore, getParam2(dataStore));
    } else if (strcmp(y, "@3") == 0) {
        setVarY(dataStore, getParam3(dataStore));
    } else {
        setVarY(dataStore, stripQuotes(y, y));
    }

    return 0;
}
int commandParseSetZ(dataStoreT *dataStore, char *z) {
    if (!dataStore || isEmpty(z)) {
        return -1;
    }

    if (z[0] != '*') {
        setVarZ(dataStore, stripQuotes(z, z));
        return 0;
    int multiplier; 
    if (z[1] == '*') {
        multiplier = stringToNum(getParam1(dataStore));
    } else {
        multiplier = stringToNum(z + 1);
    }

    char *buf = malloc(sizeof(char) * (strlen(getVarZ(dataStore)) * (multiplier+1) +1));
    if (!buf) {
        return -1;
    }
    strcpy(buf, getVarZ(dataStore));
    for (int i = 0; i < multiplier; ++i) {
        strcat(buf, getVarZ(dataStore));
    }
    
    setVarZ(dataStore, buf);
    free(buf);

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