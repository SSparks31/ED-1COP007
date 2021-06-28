#include "./shadow.h"

#include "../helper/stringHelp.h"

struct shadow {
    lineT wall;
    Meteor meteor;
};

Shadow createShadow(char* wallCoordinates, Meteor meteor) {
    if (isEmpty(wallCoordinates) || !meteor) {
        return NULL;
    }

    Shadow shadow = malloc(sizeof(struct shadow));
    if (!shadow) {
        return NULL;
    }


    lineT wall = createLine("red", wallCoordinates);
    if (!wall) {
        return NULL;
    }

    shadow->meteor = meteor;
    shadow->wall = wall;
}

lineT shadowGetGeneratingWall(Shadow shadow) {
    if (!shadow) {
        return NULL;
    }

    return shadow->wall;
}

Meteor shadowGetMeteor(Shadow shadow) {
    if (!shadow) {
        return NULL;
    }

    return shadow->meteor;
}

void destroyShadow(Shadow shadow) {
    if (!shadow) {
        return;
    }

    destroyLine(shadow->wall);

    free(shadow);
}