#include "./progrData.h"

#include <stdlib.h>

#include "../helper/stringHelp.h"

struct progrData {
    char* inputPath;
    char* outputPath;

    char* geoName;
    char* qryName;

    listT geoList;
    listT qryList;

    int collect;
};

progrDataT createProgrData(char* inputPath, char* outputPath, char* geoName, char* qryName, int collect) {
    if (!inputPath || isEmpty(outputPath) || isEmpty(geoName) || !qryName) {
        return NULL;
    }

    progrDataT progrData = malloc(sizeof(struct progrData));
    if (!progrData) {
        return NULL;
    }

    progrData->inputPath = inputPath;
    progrData->outputPath = outputPath;
    progrData->geoName = geoName;
    progrData->qryName = qryName;
    progrData->geoList = NULL;
    progrData->qryList = NULL;
    progrData->collect = collect;

    return progrData;
}

char* getInputPathProgrData(progrDataT progrData) {
    if (!progrData) {
        return NULL;
    }

    return progrData->inputPath;
}

char* getOutputPathProgrData(progrDataT progrData) {
    if (!progrData) {
        return NULL;
    }

    return progrData->outputPath;
}

char* getGeoNameProgrData(progrDataT progrData) {
    if (!progrData) {
        return NULL;
    }

    return progrData->geoName;
}

char* getQryNameProgrData(progrDataT progrData) {
    if (!progrData) {
        return NULL;
    }

    return progrData->qryName;
}

listT getGeoListProgrData(progrDataT progrData) {
    if (!progrData) {
        return NULL;
    }

    return progrData->geoList;
}

void setGeoListProgrData(progrDataT progrData, listT list) {
    if (!progrData) {
        return;
    }

    progrData->geoList = list;
}

listT getQryListProgrData(progrDataT progrData) {
    if (!progrData) {
        return NULL;
    }

    return progrData->qryList;
}

void setQryListProgrData(progrDataT progrData, listT list) {
    if (!progrData) {
        return;
    }

    progrData->qryList = list;
}

int getCollectProgrData(progrDataT progrData) {
    if (!progrData) {
        return -1;
    }

    return progrData->collect;
}

void destroyProgrData(progrDataT progrData) {
    if (!progrData) {
        return;
    }

    // destroyList(progrData->geoList);
    // destroyList(progrData->qryList);

    free(progrData);
}