#ifndef MODULO_DATASTORE_H
#define MODULO_DATASTORE_H

#include <stdio.h>

typedef struct dataFile {
    FILE *file;
    char mode[2];
} dataFileT;

typedef struct dataStore {
    char *x; /* Variavel X */
    char *y; /* Variavel Y */
    char *z; /* Variavel Z */

    char *p1; /* Parametro @1 */
    char *p2; /* Parametro @2 */
    char *p3; /* Parametro @3 */

    char *d; /* Diretorio corrente */
    char *a; /* Nome do arquivo */
    char *e; /* Extensao do arquivo */

    dataFileT *fileList[10]; /* Lista para armazenar arquivos */
} dataStoreT;

dataFileT *createDataFile(char *path, char *mode);
void destroyDataFile(dataFileT **dataFile);

dataStoreT *createDataStore(char *defaultDir, char *p1, char *p2, char *p3);
void destroyDataStore(dataStoreT **dataStore);

int addFile(dataStoreT *dataStore, int id, char *mode);
dataFileT getFile(dataStoreT *dataStore, int id);
int removeFile(dataStoreT *dataStoreT, int id);

int commandParse(FILE *input, dataStoreT *dataStore);

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