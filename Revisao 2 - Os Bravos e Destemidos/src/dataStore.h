#include <stdio.h>

typedef struct dataFile {
    FILE *file;
    char *mode;

    int id;
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

dataFileT *createDataFile(int id, char *path, char *mode);
void destroyDataFile(dataFileT **dataFile);

dataStoreT *createDataStore(char *defaultDir, char *p1, char *p2, char *p3);
void destroyDataStore(dataStoreT **dataStore);

void addFile(dataStoreT *dataStore, int id);
dataFileT getFile(dataStoreT *dataStore, int id);
void removeFile(dataStoreT *dataStoreT, int id);
