#include "rect.h"

#include <stdlib.h>
#include <string.h>

#include "../helper/stringHelp.h"

struct rect {
    char* borderColor;
    char* fillColor;
    char* rectID;

    char* xPos;
    char* yPos;
    char* width;
    char* height;

};

rectT createRect(char* borderColor, char* fillColor, char* ID, char* coordinates) {
    rectT newRect = malloc(sizeof(struct rect));
    if (!newRect) {
        return NULL;
    }

    char* x  = coordinates;
    char* y  = splitString(x , ' ');
    char* w  = splitString(y , ' ');
    char* h  = splitString(w , ' ');

    newRect->borderColor = malloc(sizeof(char) * (strlen(borderColor) +1));
    newRect->fillColor = malloc(sizeof(char) * (strlen(fillColor) +1));
    newRect->rectID = malloc(strlen(ID) + 1);
    newRect->xPos   = malloc(strlen(x)  + 1);
    newRect->yPos   = malloc(strlen(y)  + 1);
    newRect->width  = malloc(strlen(w)  + 1);
    newRect->height = malloc(strlen(h)  + 1); // TODO: Figure out a way to sanitize these without doing ten frees
                                              // Maybe sanitize destroyRect() and call it here?
    
    strcpy(newRect->borderColor, borderColor);
    strcpy(newRect->fillColor, fillColor);
    strcpy(newRect->rectID, ID);
    strcpy(newRect->xPos  , x);
    strcpy(newRect->yPos  , y);
    strcpy(newRect->width , w);
    strcpy(newRect->height, h);

    return newRect;
}

char* getIDRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->rectID;
}

char* getBorderColorRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->borderColor;
}

void setBorderColorRect(rectT rect, char* borderColor) {
    if (!rect) {
        return;
    }

    rect->borderColor = realloc(rect->borderColor, sizeof(char) * (strlen(borderColor) + 1));
    strcpy(rect->borderColor, borderColor);
}

char* getFillColorRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->fillColor;
}

void setFillColorRect(rectT rect, char* fillColor) {
    if (!rect) {
        return;
    }

    rect->fillColor = realloc(rect->fillColor, sizeof(char) * (strlen(fillColor) + 1));
    strcpy(rect->fillColor, fillColor);
}

char* getXRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->xPos;
}

void setXRect(rectT rect, char* x) {
    if (!rect || isEmpty(x)) {
        return;
    }

    rect->xPos = realloc(rect->xPos, sizeof(char) * (strlen(x) + 1));
    strcpy(rect->xPos, x);
}

char* getYRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->yPos;
}

void setYRect(rectT rect, char* y) {
    if (!rect || isEmpty(y)) {
        return;
    }

    rect->yPos = realloc(rect->yPos, sizeof(char) * (strlen(y) + 1));
    strcpy(rect->yPos, y);
}

char* getWidthRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->width;
}

void setWidthRect(rectT rect, char* w) {
    if (!rect || isEmpty(w)) {
        return;
    }

    rect->width = realloc(rect->width, sizeof(char) * (strlen(w) + 1));
    strcpy(rect->width, w);
}

char* getHeightRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->height;
}

void setHeightRect(rectT rect, char* h) {
    if (!rect || isEmpty(h)) {
        return;
    }

    rect->height = realloc(rect->height, sizeof(char) * (strlen(h) + 1));
    strcpy(rect->height, h);
}

void setCoordinatesRect(rectT rect, char* coordinates) {
    if (!rect || isEmpty(coordinates)) {
        return;
    }

    char* x = coordinates;
    char* y = splitString(x, ' ');
    char* w = splitString(y, ' ');
    char* h = splitString(w, ' '); 

    setXRect(rect, x);
    setYRect(rect, y);
    setWidthRect(rect, w);
    setHeightRect(rect, h);
}

void destroyRect(rectT rect) {
    if (!rect) {
        return;
    }

    free(rect->borderColor);
    free(rect->fillColor);
    free(rect->rectID);
    free(rect->xPos);
    free(rect->yPos);
    free(rect->width);
    free(rect->height);

    free(rect);
}