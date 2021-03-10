#include "rect.h"

#include <stdlib.h>
#include <string.h>

#include "../helper/stringHelp.h"
#include "./svg.h"

struct rect {
    char borderColor[SVG_COLOR_MAX_LEN];
    char fillColor[SVG_COLOR_MAX_LEN];
    char *rectID;

    char *xPos;
    char *yPos;
    char *width;
    char *height;

};

rectT createRect(char* borderColor, char* fillColor, char* ID, char* coordinates) {
    rectT newRect = malloc(sizeof(struct rect));
    if (!newRect) {
        return NULL;
    }

    char* x  = coordinates;
    char* y  = findCharacter(x , ' ') + 1;
    char* w  = findCharacter(y , ' ') + 1;
    char* h  = findCharacter(w , ' ') + 1;

    x[-1] = '\0';
    y[-1] = '\0';
    w[-1] = '\0';
    h[-1] = '\0';

    strcpy(newRect->borderColor, borderColor);
    strcpy(newRect->fillColor, fillColor);

    newRect->rectID = malloc(strlen(ID) + 1);
    newRect->xPos   = malloc(strlen(x)  + 1);
    newRect->yPos   = malloc(strlen(y)  + 1);
    newRect->width  = malloc(strlen(w)  + 1);
    newRect->height = malloc(strlen(h)  + 1); // TODO: Figure out a way to sanitize these without doing ten frees
                                              // Maybe sanitize destroyRect() and call it here?
    
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

char* getFillColorRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->fillColor;
}

char* getXRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->xPos;
}

char* getYRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->yPos;
}

char* getWidthRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->width;
}

char* getHeightRect(rectT rect) {
    if (!rect) {
        return NULL;
    }

    return rect->height;
}

void destroyRect(rectT rect) {
    if (!rect) {
        return;
    }

    free(rect->rectID);
    free(rect->xPos);
    free(rect->yPos);
    free(rect->width);
    free(rect->height);

    free(rect);
}