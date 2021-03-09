#include "geo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringHelp.h"
#include "mathHelp.h"

struct rect {
    char borderColor[SVG_COLOR_MAX_LEN];
    char fillColor[SVG_COLOR_MAX_LEN];
    char *rectID;

    char *xPos;
    char *yPos;
    char *width;
    char *height;

};

listT geoParser(char* geoPath) {
    FILE *geoFile = fopen(geoPath, "r");
    if (!geoFile) {
        printf("Arquivo .geo nao encontrado\n");
        return NULL;
    }

    char borderColor[SVG_COLOR_MAX_LEN];
    char fillColor[SVG_COLOR_MAX_LEN];
    listT rectList = NULL;

    char command[999];

    fgetLine(geoFile, command, 999);

    while (!isEmpty(command)) {
        switch (command[0]) {
            case 'n':;
                char *numPos = rfindCharacter(command, ' ') + 1;
                printf("%s\n", numPos);
                rectList = createList(stringToInt(numPos));
                
                break;
            
            case 'c':;
                if (command[1] == 'c') {
                    strcpy(borderColor, rfindCharacter(command, ' ') + 1);
                } else {
                    strcpy(fillColor, rfindCharacter(command, ' ') + 1);
                }
                break;
            
            case 'r':;               
                rectT newRect = createRect(borderColor, fillColor, command);
                appendList(rectList, newRect);
                
                break;

            default:
                break;
        }

        fgetLine(geoFile, command, 999);
    }

    fclose(geoFile);
    return rectList;
}

rectT createRect(char* borderColor, char* fillColor, char* command) {
    rectT newRect = malloc(sizeof(struct rect));
    char* id = findCharacter(command, ' ') + 1;
    char* x  = findCharacter(id, ' ') + 1;
    char* y  = findCharacter(x , ' ') + 1;
    char* w  = findCharacter(y , ' ') + 1;
    char* h  = findCharacter(w , ' ') + 1;

    x[-1] = '\0';
    y[-1] = '\0';
    w[-1] = '\0';
    h[-1] = '\0';

    strcpy(newRect->borderColor, borderColor);
    strcpy(newRect->fillColor, fillColor);

    newRect->rectID = malloc(strlen(id) + 1);
    newRect->xPos   = malloc(strlen(x)  + 1);
    newRect->yPos   = malloc(strlen(y)  + 1);
    newRect->width  = malloc(strlen(w)  + 1);
    newRect->height = malloc(strlen(h)  + 1);
    
    strcpy(newRect->rectID, id);
    strcpy(newRect->xPos  , x);
    strcpy(newRect->yPos  , y);
    strcpy(newRect->width , w);
    strcpy(newRect->height, h);

    return newRect;
}

char* getIDRect(rectT rect) {
    if (!rect) {
        return "";
    }

    return rect->rectID;
}

char* getBorderColorRect(rectT rect) {
    if (!rect) {
        return "";
    }

    return rect->borderColor;
}

char* getFillColorRect(rectT rect) {
    if (!rect) {
        return "";
    }

    return rect->fillColor;
}

char* getXRect(rectT rect) {
    if (!rect) {
        return "";
    }

    return rect->xPos;
}

char* getYRect(rectT rect) {
    if (!rect) {
        return "";
    }

    return rect->yPos;
}

char* getWidthRect(rectT rect) {
    if (!rect) {
        return "";
    }

    return rect->width;
}

char* getHeightRect(rectT rect) {
    if (!rect) {
        return "";
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