#include "./svg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/stringHelp.h"
#include "../helper/pathHelp.h"


FILE* startSVG(char* path, char* fileName) {
    char* fullPath = concatPathFile(path, fileName);
    if (isEmpty(fullPath)) {
        return NULL;
    }

    FILE* svgFile = fopen(fullPath, "w");
    free(fullPath);
    if (!svgFile) {
        return NULL;
    }

    fprintf(svgFile, "<svg>\n\n");
    return svgFile;
}

int addRectToSVG(FILE* svgFile, rectT rect) {
    if (!svgFile || !rect) {
        return -1;
    }

    const char* rectFormat = "<rect x = \"%s\" y = \"%s\" width = \"%s\" height = \"%s\" fill=\"%s\" stroke = \"%s\" fill-opacity=\"%s\" stroke-opacity=\"%s\" stroke-width=\"1\" />\n";

    char borderOpacity[4] = "100";
    if (strcmp(getBorderColorRect(rect), "@") == 0) {
        strcpy(borderOpacity, "0");
    }

    char fillOpacity[4] = "100";
    if (strcmp(getFillColorRect(rect), "@") == 0) {
        strcpy(fillOpacity, "0");
    }

    char* xRect = getXRect(rect);
    char* yRect = getYRect(rect);
    char* widthRect = getWidthRect(rect);
    char* heightRect = getHeightRect(rect);
    char* fillColorRect = getFillColorRect(rect);
    char* borderColorRect = getBorderColorRect(rect);

    fprintf(svgFile, rectFormat, xRect, yRect, widthRect, heightRect, fillColorRect, borderColorRect, fillOpacity, borderOpacity);
    return 0;
}

int finishSVG(FILE* svgFile) {
    if (!svgFile) {
        return -1;
    }

    fprintf(svgFile, "\n</svg>");
    fclose(svgFile);

    return 0;
}