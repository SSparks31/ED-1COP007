#include "./progrData.h"

#include <stdlib.h>

#include "../tree/kdTree.h"

#include "../svg/rect.h"
#include "../svg/circle.h"

#include "../helper/stringHelp.h"
#include <string.h>

#include "../helper/mathHelp.h"

#define SVG_COLOR_MAX_LEN 22

struct progrData {
    char* BSD;
    char* BED;

    char* geoName;
    char* qryName;

    char rectBorder[SVG_COLOR_MAX_LEN];
    char rectFill[SVG_COLOR_MAX_LEN];

    char circleBorder[SVG_COLOR_MAX_LEN];
    char circleFill[SVG_COLOR_MAX_LEN];

    kdTree rectTree;
    kdTree circleTree;
};

int kdRectCompare(const kdTreeElem a, const kdTreeElem b, int j) {
    char* (*getDimension)(rectT rect);
    if (j) {
        getDimension = getXRect;
    } else {
        getDimension = getYRect;
    }

    double aDimension = stringToDouble(getDimension(a));
    double bDimension = stringToDouble(getDimension(b));

    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }

    return 0;
}

int kdCircleCompare(const kdTreeElem a, const kdTreeElem b, int j) {
    char* (*getDimension)(circleT circle);
    if (j) {
        getDimension = getXCenterCircle;
    } else {
        getDimension = getYCenterCircle;
    }

    double aDimension = stringToDouble(getDimension(a));
    double bDimension = stringToDouble(getDimension(b));

    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }

    return 0;
}

progrData createData(char* BED, char* BSD, char* geoName, char* qryName) {
    if (isEmpty(BSD) != 0|| isEmpty(geoName) != 0) {
        return NULL;
    }

    progrData data = malloc(sizeof(struct progrData));
    if (!data) {
        return NULL;
    }

    data->rectTree = createKDTree(2, kdRectCompare);
    data->circleTree = createKDTree(2, kdCircleCompare);

    char* relPath = "./";
    char* empty = "";

    if (!data->rectTree || !data->circleTree) {
        destroyKDTree(data->rectTree);
        destroyKDTree(data->circleTree);
        free(data);
        
        return NULL;
    }

    if (isEmpty(BED) != 0) {
        data->BED = relPath;
    } else {
        data->BED = BED;
    }

    data->BSD = BSD;

    data->geoName = geoName;

    if (isEmpty(qryName) != 0) {
        data->qryName = empty;
    } else {
        data->qryName = qryName;
    }



    return data;
}

char* getBED(progrData data) {
    if (!data) {
        return NULL;
    }

    return data->BED;
}

char* getBSD(progrData data) {
    if (!data) {
        return NULL;
    }

    return data->BSD;
}

char* getGeoName(progrData data) {
    if (!data) {
        return NULL;
    }

    return data->geoName;
}

char* getQryName(progrData data) {
    if (!data) {
        return NULL;
    }

    return data->qryName;
}

char* getRectBorder(progrData data) {
    if (!data) {
        return NULL;
    }

    return data->rectBorder;
}

void  setRectBorder(progrData data, char* args) {
    if (!data) {
        return;
    }

    strcpy(data->rectBorder, args);
}

char* getRectFill(progrData data) {
    if (!data) {
        return NULL;
    }

    return data->rectFill;
}

void  setRectFill(progrData data, char* args) {
    if (!data) {
        return;
    }

    strcpy(data->rectFill, args);
}

char* getCircleBorder(progrData data) {
    if (!data) {
        return NULL;
    }

    return data->circleBorder;
}

void  setCircleBorder(progrData data, char* args) {
    if (!data) {
        return;
    }

    strcpy(data->circleBorder, args);
}

char* getCircleFill(progrData data) {
    if (!data) {
        return NULL;
    }

    return data->circleFill;
}

void  setCircleFill(progrData data, char* args) {
    if (!data) {
        return;
    }

    strcpy(data->circleFill, args);
}

kdTree getRectTree(progrData data) {
    if (!data) {
        return NULL;
    }

    return data->rectTree;
}

kdTree getCircleTree(progrData data) {
    if (!data) {
        return NULL;
    }

    return data->circleTree;
}

void destroyData(progrData data) {
    if (!data) {
        return;
    }

    kdTree rectTree = getRectTree(data);
    while (!isEmptyKDTree(rectTree)) {
        destroyRect(removeFromKDTree(rectTree, getRootKDTree(rectTree)));
    }
    destroyKDTree(rectTree);

    kdTree circleTree = getCircleTree(data);
    while (!isEmptyKDTree(circleTree)) {
        destroyCircle(removeFromKDTree(circleTree, getRootKDTree(circleTree)));
    }
    destroyKDTree(circleTree);

    free(data);
}