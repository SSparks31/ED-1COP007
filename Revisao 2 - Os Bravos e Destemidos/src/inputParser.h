#ifndef LIB_INPUTPARSER_H
#define LIB_INPUTPARSER_H

#include <stdio.h>
#include "dataStore.h"

void commandParse(FILE *input, dataStoreT *dataStore);

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

#endif