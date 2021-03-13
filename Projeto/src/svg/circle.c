#include "./circle.h"

#include <stdlib.h>
#include <string.h>

#include "../helper/stringHelp.h"

struct circle {
    char* borderColor;
    char* fillColor;

    char* xCenter;
    char* yCenter;
    char* radius;
};

circleT createCircle(char* borderColor, char* fillColor, char* coordinates) {
    if (isEmpty(borderColor) || isEmpty(coordinates)) {
        return NULL;
    }

    circleT circle = malloc(sizeof(struct circle));
    if (!circle) {
        return NULL;
    }

    char* xCenter  = coordinates;
    char* yCenter  = splitString(xCenter , ' ');
    char* radius  = splitString(yCenter , ' ');

    circle->borderColor = malloc(sizeof(char) * (strlen(borderColor) + 1));
    circle->fillColor = malloc(sizeof(char) * (strlen(fillColor) + 1));
    circle->xCenter = malloc(sizeof(char) * (strlen(xCenter) + 1));
    circle->yCenter = malloc(sizeof(char) * (strlen(yCenter) + 1));
    circle->radius = malloc(sizeof(char) * (strlen(radius) + 1));

    if (!circle->borderColor || !circle->fillColor || !circle->xCenter || !circle->yCenter || !circle->radius) {
        destroyCircle(circle);
    }

    strcpy(circle->borderColor, borderColor);
    strcpy(circle->fillColor, fillColor);
    strcpy(circle->xCenter, xCenter);
    strcpy(circle->yCenter, yCenter);
    strcpy(circle->radius, radius);

    return circle;
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

    if (circle->borderColor) free(circle->borderColor);
    if (circle->fillColor) free(circle->fillColor);
    if (circle->xCenter) free(circle->xCenter);
    if (circle->yCenter) free(circle->yCenter);
    if (circle->radius) free(circle->radius);

    free(circle);
}