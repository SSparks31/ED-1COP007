#include "./progrData.h"

#include <stdlib.h>

#include "../tree/kdTree.h"

#include "../helper/stringHelp.h"

#define SVG_COLOR_MAX_LEN 22

struct progrData {
    char* BSD;
    char* BED;

    char rectBorder[SVG_COLOR_MAX_LEN];
    char rectFill[SVG_COLOR_MAX_LEN];

    char circleBorder[SVG_COLOR_MAX_LEN];
    char circleFill[SVG_COLOR_MAX_LEN];

    kdTree rectTree;
    kdTree circleTree;
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