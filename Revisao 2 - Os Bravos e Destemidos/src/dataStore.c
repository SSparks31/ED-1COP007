#include "dataStore.h"

#include <stdlib.h>
#include <string.h>

#include "stringHelp.h"

dataStoreT *createDataStore(char *defaultDir, int numParams, char **params) {
    dataStoreT *dataStore = malloc(sizeof(dataStoreT));
    if (!dataStore) {
        return NULL;
    }

    dataStore->varX = NULL;
    dataStore->varY = NULL;
    dataStore->varZ = NULL;

    dataStore->numParameters = numParams;
    dataStore->parameters = params;
    
    dataStore->currentDir = NULL;
    dataStore->fileName = NULL;
    dataStore->fileSuffix = NULL;

    if (!isEmpty(defaultDir)) {
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

void setVarX(dataStoreT *dataStore, char *varX) {
    if (!dataStore) {
        return;
    }

    if (!varX) {
        free(dataStore->varX);
        dataStore->varX = NULL;
        return;
    }

    size_t newSize = strlen(varX) + 1;
    if (dataStore->varX) {
        dataStore->varX = realloc(dataStore->varX, sizeof(char) * newSize);    
    } else {
        dataStore->varX = malloc(sizeof(char) * newSize);
    }
    
    strcpy(dataStore->varX, varX);
}

char *getVarX(dataStoreT *dataStore) {
    return dataStore ? dataStore->varX : NULL;
}

void setVarY(dataStoreT *dataStore, char *varY) {
    if (!dataStore) {
        return;
    }

    if (!varY) {
        free(dataStore->varY);
        dataStore->varY = NULL;
        return;
    }

    size_t newSize = strlen(varY) + 1;
    if (dataStore->varY) {
        dataStore->varY = realloc(dataStore->varY, sizeof(char) * newSize);    
    } else {
        dataStore->varY = malloc(sizeof(char) * newSize);
    }
    
    strcpy(dataStore->varY, varY);
}

char *getVarY(dataStoreT *dataStore) {
    return dataStore ? dataStore->varY : NULL;
}

void setVarZ(dataStoreT *dataStore, char *varZ) {
    if (!dataStore) {
        return;
    }

    if (!varZ) {
        free(dataStore->varZ);
        dataStore->varZ = NULL;
        return;
    }

    size_t newSize = strlen(varZ) + 1;
    if (dataStore->varZ) {
        dataStore->varZ = realloc(dataStore->varZ, sizeof(char) * newSize);    
    } else {
        dataStore->varZ = malloc(sizeof(char) * newSize);
    }
    
    strcpy(dataStore->varZ, varZ);
}

char *getVarZ(dataStoreT *dataStore) {
    return dataStore ? dataStore->varZ : NULL;
}

char *getParam1(dataStoreT *dataStore) {
    return dataStore && dataStore->numParameters >= 1 ? dataStore->parameters[0] : NULL;
}

char *getParam2(dataStoreT *dataStore) {
    return dataStore && dataStore->numParameters >= 2 ? dataStore->parameters[1] : NULL;
}

char *getParam3(dataStoreT *dataStore) {
    return dataStore && dataStore->numParameters >= 3 ? dataStore->parameters[2] : NULL;
}

void setVarD(dataStoreT *dataStore, char *varD) {
    if (!dataStore) {
        return;
    }

    if (!varD) {
        free(dataStore->currentDir);
        dataStore->currentDir = NULL;
        return;
    }

    size_t newSize = strlen(varD) + 1;
    if (dataStore->currentDir) {
        dataStore->currentDir = realloc(dataStore->currentDir, sizeof(char) * newSize);    
    } else {
        dataStore->currentDir = malloc(sizeof(char) * newSize);
    }
    
    strcpy(dataStore->currentDir, varD);
}

char *getVarD(dataStoreT *dataStore) {
    return dataStore ? dataStore->currentDir : NULL;
}

void setVarA(dataStoreT *dataStore, char *varA) {
    if (!dataStore) {
        return;
    }

    if (!varA) {
        free(dataStore->fileName);
        dataStore->fileName = NULL;
        return;
    }

    size_t newSize = strlen(varA) + 1;
    if (dataStore->fileName) {
        dataStore->fileName = realloc(dataStore->fileName, sizeof(char) * newSize);    
    } else {
        dataStore->fileName = malloc(sizeof(char) * newSize);
    }
    
    strcpy(dataStore->fileName, varA);
}

char *getVarA(dataStoreT *dataStore) {
    return dataStore ? dataStore->fileName : NULL;
}

void setVarE(dataStoreT *dataStore, char *varE) {
    if (!dataStore) {
        return;
    }

    if (!varE) {
        free(dataStore->fileSuffix);
        dataStore->fileSuffix = NULL;
        return;
    }

    size_t newSize = strlen(varE) + 1;
    if (dataStore->fileSuffix) {
        dataStore->fileSuffix = realloc(dataStore->fileSuffix, sizeof(char) * newSize);    
    } else {
        dataStore->fileSuffix = malloc(sizeof(char) * newSize);
    }
    
    strcpy(dataStore->fileSuffix, varE);
}

char *getVarE(dataStoreT *dataStore) {
    return dataStore ? dataStore->fileSuffix : NULL;
}

void addFileToList(dataStoreT *dataStore, int id, char *path, char *mode);
dataFileT *getFileFromID(dataStoreT *dataStore, int id);