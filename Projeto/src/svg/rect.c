#include "rect.h"

#include <stdlib.h>
#include <string.h>

#include "../helper/stringHelp.h"

struct rect {
    char* rectID;

    char* borderColor;
    char* fillColor;

    char* opacity;

    char* xPos;
    char* yPos;
    char* width;
    char* height;

};

rectT createRect(char* borderColor, char* fillColor, char* opacity, char* ID, char* coordinates) {
    if (isEmpty(borderColor) || isEmpty(fillColor) || isEmpty(opacity) || isEmpty(ID) || isEmpty(coordinates));
    
    rectT newRect = malloc(sizeof(struct rect));
    if (!newRect) {
        return NULL;
    }

    char* x  = coordinates;
    char* y  = splitString(x , ' ');
    char* w  = splitString(y , ' ');
    char* h  = splitString(w , ' ');

    newRect->borderColor = malloc(strlen(borderColor) +1);
    newRect->fillColor = malloc(strlen(fillColor) +1);
    newRect->opacity = malloc(strlen(opacity) + 1);
    newRect->rectID = malloc(strlen(ID) + 1);
    newRect->xPos   = malloc(strlen(x)  + 1);
    newRect->yPos   = malloc(strlen(y)  + 1);
    newRect->width  = malloc(strlen(w)  + 1);
    newRect->height = malloc(strlen(h)  + 1);
    
    strcpy(newRect->borderColor, borderColor);
    strcpy(newRect->fillColor, fillColor);
    strcpy(newRect->opacity, opacity);
    strcpy(newRect->rectID, ID);
    strcpy(newRect->xPos  , x);
    strcpy(newRect->yPos  , y);
    strcpy(newRect->width , w);
    strcpy(newRect->height, h);

    if (!newRect->borderColor || !newRect->fillColor || !newRect->opacity || !newRect->rectID || !newRect->xPos || !newRect->yPos || !newRect->width || !newRect->height) {
        destroyRect(newRect);
        return NULL;
    }

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

    rect->borderColor = realloc(rect->borderColor, strlen(borderColor) + 1);
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

    rect->fillColor = realloc(rect->fillColor, strlen(fillColor) + 1);
    strcpy(rect->fillColor, fillColor);
}

char* getOpacityRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->opacity;
}

void setOpacityRect(rectT rect, char* opacity) {
    if (!rect) {
        return;
    }

    rect->opacity = realloc(rect->opacity, strlen(opacity) + 1);
    strcpy(rect->opacity, opacity);
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

    rect->xPos = realloc(rect->xPos, strlen(x) + 1);
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

    rect->yPos = realloc(rect->yPos, strlen(y) + 1);
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

    rect->width = realloc(rect->width, strlen(w) + 1);
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

    rect->height = realloc(rect->height, strlen(h) + 1);
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

    if (rect->rectID) free(rect->rectID);
    if (rect->borderColor) free(rect->borderColor);
    if (rect->fillColor) free(rect->fillColor);
    if (rect->opacity) free(rect->opacity);
    if (rect->xPos) free(rect->xPos);
    if (rect->yPos) free(rect->yPos);
    if (rect->width) free(rect->width);
    if (rect->height) free(rect->height);

    free(rect);
}