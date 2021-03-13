#include "./svg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/stringHelp.h"
#include "../helper/pathHelp.h"

int startSVG(char* path, char* fileName) {
    if (isEmpty(fileName)) {
        return -1;
    }

    char* fullPath = concatPathFile(path, fileName);
    FILE* svg = fopen(fullPath, "w");
    free(fullPath);
    if (!svg) {
        return -1;
    }

    fprintf(svg, "<svg>\n\n");
    fclose(svg);

    return 0;
}

int addRectToSVG(char* path, char* fileName, rectT rect) {
    if (isEmpty(fileName) || !rect) {
        return -1;
    }

    const char* rectFormat = "<rect x = \"%s\" y = \"%s\" width = \"%s\" height = \"%s\" fill=\"%s\" stroke = \"%s\" fill-opacity=\"%s\" stroke-opacity=\"%s\" stroke-width=\"1\" />\n";

    char* fullPath = concatPathFile(path, fileName);
    FILE* svg = fopen(fullPath, "a");
    free(fullPath);
    if (!svg) {
        return -1;
    }

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

    fprintf(svg, rectFormat, xRect, yRect, widthRect, heightRect, fillColorRect, borderColorRect, fillOpacity, borderOpacity);

    fclose(svg);
    return 0;
}

int finishSVG(char* path, char* fileName) {
    if (isEmpty(path)) {
        return -1;
    }

    char* fullPath = concatPathFile(path, fileName);
    FILE* svg = fopen(fullPath, "a");
    free(fullPath);
    if (!svg) {
        return -1;
    }

    fprintf(svg, "\n</svg>");
    fclose(svg);

    return 0;
}