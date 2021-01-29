#include "dataStore.h"

#include <stdlib.h>
#include <string.h>

#include "stringManip.h"
#include "path.h"


dataFileT *createDataFile(char *path, char mode[2]) {
    if (!validString(path) || !validString(mode)) {
        return NULL;
    }

    dataFileT *dataFile = malloc(sizeof(dataFileT));
    if (!dataFile) {
        return NULL;
    }

    dataFile->file = fopen(path, mode);
    if (!dataFile->file) {
        free(dataFile);
        return NULL;
    }

    strcpy(dataFile->mode, mode);
    return dataFile;
}

void destroyDataFile(dataFileT **dataFile) {}

dataStoreT *createDataStore(char *defaultDir, char *p1, char *p2, char *p3) {
    dataStoreT *dataStore = malloc(sizeof(dataStoreT));
    if (!dataStore) {
        printf("Erro de alocacao de memoria\n");
        return NULL;
    }

    dataStore->x = calloc(1, sizeof(char)); /* Inicializar como string vazia */
    dataStore->y = calloc(1, sizeof(char)); /* Inicializar como string vazia */
    dataStore->z = calloc(1, sizeof(char)); /* Inicializar como string vazia */

    dataStore->p1 = calloc(1, sizeof(char)); /* Inicializar como string vazia */
    dataStore->p2 = calloc(1, sizeof(char)); /* Inicializar como string vazia */
    dataStore->p2 = calloc(1, sizeof(char)); /* Inicializar como string vazia */

    dataStore->d = calloc(1, sizeof(char)); /* Inicializar como string vazia */
    dataStore->a = calloc(1, sizeof(char)); /* Inicializar como string vazia */
    dataStore->e = calloc(1, sizeof(char)); /* Inicializar como string vazia */

    if (validString(defaultDir)) {
        // printf("-o recebido\n");
        dataStore->d = realloc(dataStore->d, sizeof(char) * strlen(defaultDir) + 1);
        strcpy(dataStore->d, defaultDir);
    }

    if (validString(p1)) {
        // printf("@1 recebido\n");
        dataStore->p1 = realloc(dataStore->p1, sizeof(char) * (strlen(p1) + 1));
        strcpy(dataStore->p1, p1);
    }

    if (validString(p2)) {
        // printf("@2 recebido\n");
        dataStore->p2 = realloc(dataStore->p2, sizeof(char) * (strlen(p2) + 1));
        strcpy(dataStore->p2, p2);
    }
    
    if (validString(p3)) {
        // printf("@3 recebido\n");
        dataStore->p3 = realloc(dataStore->p3, sizeof(char) * (strlen(p3) + 1));
        strcpy(dataStore->p3, p3);
    }

    return dataStore;

}
void destroyDataStore(dataStoreT **dataStore) {
    free((*dataStore)->x);
    free((*dataStore)->y);
    free((*dataStore)->z);

    free((*dataStore)->p1);
    free((*dataStore)->p2);
    free((*dataStore)->p3);

    free((*dataStore)->d);
    free((*dataStore)->a);
    free((*dataStore)->e);

    free(*dataStore);
    *dataStore = NULL;
}

int addFile(dataStoreT *dataStore, int id, char *mode) {
    if (!dataStore || id < 0 || id > 9 || dataStore->fileList[id]) {
        return -1;
    }

    char *fileName = concatFileSuffix(dataStore->a, dataStore->e);
    char *fullPath = concatPathFile(dataStore->d, fileName);
    free(fileName);
   
    dataStore->fileList[id] = createDataFile(fullPath, mode);    
    if (!dataStore->fileList[id]) {
        return -2;
    }

    return 0;
}

dataFileT getFile(dataStoreT *dataStore, int id) {}
int removeFile(dataStoreT *dataStoreT, int id) {}
