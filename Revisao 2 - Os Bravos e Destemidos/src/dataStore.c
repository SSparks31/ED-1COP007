#include "dataStore.h"

#include <stdio.h>
#include <string.h>

#include "stringHelp.h"

dataStoreT *createDataStore(char *defaultDir, char **params) {
    dataStoreT *dataStore = malloc(sizeof(dataStoreT));
    if (!dataStore) {
        return NULL;
    }

    dataStore->varX = NULL;
    dataStore->varY = NULL;
    dataStore->varZ = NULL;

    dataStore->parameters = params;
    
    dataStore->currentDir = NULL;
    dataStore->fileName = NULL;
    dataStore->fileSuffix = NULL;

    if (isEmpty(defaultDir) == 1) {
        dataStore->currentDir = malloc(sizeof(char) * (strlen(defaultDir) + 1));
        strcpy(dataStore->currentDir, defaultDir);
    }

    return dataStore;
}

void destroyDataStore(dataStoreT **dataStore) {
    if (!dataStore || !*dataStore) {
        return;
    }

    if ((*dataStore)->varX) free((*dataStore)->varX);
    if ((*dataStore)->varY) free((*dataStore)->varY);
    if ((*dataStore)->varZ) free((*dataStore)->varZ);

    if ((*dataStore)->currentDir) free((*dataStore)->currentDir);
    if ((*dataStore)->fileName) free((*dataStore)->fileName);
    if ((*dataStore)->fileSuffix) free((*dataStore)->fileSuffix);

    free(*dataStore);
    *dataStore = NULL;
}

dataFileT *createDataFile(char *path, char *mode) {
    FILE *file = fopen(path, mode);
    if (!file) {
        return NULL;
    }

    dataFileT *dataFile = malloc(sizeof(dataFileT));
    if (!dataFile) {
        return NULL;
    }

    dataFile->file = file;
    strcpy(dataFile->mode, mode);

    return dataFile;
}

void destroyDataFile(dataFileT **dataFile) {
    if (!dataFile || !*dataFile) {
        return;
    }

    fclose((*dataFile)->file);
    free(*dataFile);
    *dataFile = NULL;
}