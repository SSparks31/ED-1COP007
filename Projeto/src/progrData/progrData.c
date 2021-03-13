#include "./progrData.h"

#include <stdlib.h>

#include "../helper/stringHelp.h"

struct progrData {
    char* inputPath;
    char* outputPath;

    char* geoName;
    char* qryName;

    listT rectList;

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
    progrData->rectList = NULL;
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

listT getRectListProgrData(progrDataT progrData) {
    if (!progrData) {
        return NULL;
    }

    return progrData->rectList;
}

void setRectListProgrData(progrDataT progrData, listT list) {
    if (!progrData) {
        return;
    }

    progrData->rectList = list;
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

    if (progrData->rectList) destroyList(progrData->rectList);

    free(progrData);
}