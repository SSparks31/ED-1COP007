#include "./circle.h"

#include <stdlib.h>
#include <string.h>

#include "../helper/stringHelp.h"

struct circle {
    char* circleID;

    char* borderColor;
    char* fillColor;

    char* opacity;

    char* xCenter;
    char* yCenter;
    char* radius;
};

circleT createCircle(char* borderColor, char* fillColor, char* opacity, char* ID, char* coordinates) {
    if (isEmpty(borderColor) || isEmpty(ID) || isEmpty(opacity) || isEmpty(coordinates)) {
        return NULL;
    }

    circleT circle = malloc(sizeof(struct circle));
    if (!circle) {
        return NULL;
    }

    char* xCenter  = coordinates;
    char* yCenter  = splitString(xCenter , ' ');
    char* radius  = splitString(yCenter , ' ');

    circle->circleID = malloc(strlen(ID) + 1);
    circle->borderColor = malloc(strlen(borderColor) + 1);
    circle->fillColor = malloc(strlen(fillColor) + 1);
    circle->opacity = malloc(strlen(opacity) + 1);
    circle->xCenter = malloc(strlen(xCenter) + 1);
    circle->yCenter = malloc(strlen(yCenter) + 1);
    circle->radius = malloc(strlen(radius) + 1);

    if (!circle->circleID || !circle->borderColor || !circle->fillColor || !circle->opacity || !circle->xCenter || !circle->yCenter || !circle->radius) {
        destroyCircle(circle);
    }

    strcpy(circle->circleID, ID);
    strcpy(circle->borderColor, borderColor);
    strcpy(circle->fillColor, fillColor);
    strcpy(circle->opacity, opacity);
    strcpy(circle->xCenter, xCenter);
    strcpy(circle->yCenter, yCenter);
    strcpy(circle->radius, radius);

    return circle;
}

char* getIDCircle(circleT circle) {
    if (!circle) {
        return NULL;
    }

    return circle->circleID;
}

char* getBorderColorCircle(circleT circle) {
    if (!circle) {
        return NULL;
    }
    
    return circle->borderColor;
}

void  setBorderColorCircle(circleT circle, char* borderColor) {
    if (!circle || isEmpty(borderColor)) {
        return;
    }

    circle->borderColor = realloc(circle->borderColor, strlen(borderColor) + 1);
    strcpy(circle->borderColor, borderColor);
}

char* getFillColorCircle(circleT circle) {
    if (!circle) {
        return NULL;
    }
    
    return circle->fillColor;
}

void  setFillColorCircle(circleT circle, char* fillColor) {
    if (!circle || isEmpty(fillColor)) {
        return;
    }

    circle->fillColor = realloc(circle->fillColor, strlen(fillColor) + 1);
    strcpy(circle->fillColor, fillColor);
}

char* getOpacityCircle(circleT circle) {
    if (!circle) {
        return NULL;
    }

    return circle->opacity;
}

void  setOpacityCircle(circleT circle, char* opacity) {
    if (!circle || isEmpty(opacity)) {
        return;
    }

    circle->opacity = realloc(circle->opacity, strlen(opacity) + 1);
    strcpy(circle->opacity, opacity);
}

char* getXCenterCircle(circleT circle) {
    if (!circle) {
        return NULL;
    }
    
    return circle->xCenter;
}

void  setXCenterCircle(circleT circle, char* xCenter) {
    if (!circle || isEmpty(xCenter)) {
        return;
    }

    circle->xCenter = realloc(circle->xCenter, strlen(xCenter) + 1);
    strcpy(circle->xCenter, xCenter);
}

char* getYCenterCircle(circleT circle) {
    if (!circle) {
        return NULL;
    }
    
    return circle->yCenter;
}

void  setYCenterCircle(circleT circle, char* yCenter) {
    if (!circle || isEmpty(yCenter)) {
        return;
    }

    circle->yCenter = realloc(circle->yCenter, strlen(yCenter) + 1);
    strcpy(circle->yCenter, yCenter);
}

char* getRadiusCircle(circleT circle) {
    if (!circle) {
        return NULL;
    }
    
    return circle->radius;
}

void  setRadiusCircle(circleT circle, char* radius) {
    if (!circle || isEmpty(radius)) {
        return;
    }

    circle->radius = realloc(circle->radius, strlen(radius) + 1);
    strcpy(circle->radius, radius);
}

void  setCoordinatesCircle(circleT circle, char* coordinates) {
    if (!circle || isEmpty(coordinates)) {
        return;
    }

    char* xCenter = coordinates;
    char* yCenter = splitString(coordinates, ' ');
    char* radius =  splitString(yCenter, ' ');

    setXCenterCircle(circle, xCenter);
    setYCenterCircle(circle, yCenter);
    setRadiusCircle(circle, radius);
}

void  destroyCircle(circleT circle) {
    if (!circle) {
        return;
    }

    if (circle->circleID) free(circle->circleID);
    if (circle->borderColor) free(circle->borderColor);
    if (circle->fillColor) free(circle->fillColor);
    if (circle->opacity) free(circle->opacity);
    if (circle->xCenter) free(circle->xCenter);
    if (circle->yCenter) free(circle->yCenter);
    if (circle->radius) free(circle->radius);

    free(circle);
}