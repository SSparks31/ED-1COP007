#include "./svg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/stringHelp.h"
#include "../helper/pathHelp.h"

int startSVG(char* path, char* fileName, char* width, char* height) {
    if (isEmpty(fileName) || isEmpty(width) || isEmpty(height)) {
        return -1;
    }

    char* fullPath = concatPathFile(path, fileName);
    FILE* svg = fopen(fullPath, "w");
    free(fullPath);
    if (!svg) {
        return -1;
    }

    fprintf(svg, "<svg viewBox = \"0 0 %s %s\">\n\n", width, height);
    fclose(svg);

    return 0;
}

int addRectToSVG(char* path, char* fileName, rectT rect) {
    if (isEmpty(fileName) || !rect) {
        return -1;
    }

    const char* rectFormat = "<rect x = \"%s\" y = \"%s\" width = \"%s\" height = \"%s\" fill=\"%s\" stroke = \"%s\" fill-opacity=\"%s\" stroke-opacity=\"100\" stroke-width=\"1\" />\n";

    char* fullPath = concatPathFile(path, fileName);
    FILE* svg = fopen(fullPath, "a");
    free(fullPath);
    if (!svg) {
        return -1;
    }

    char transparent[4] = "100";
    if (strcmp(getFillColorRect(rect), "@") == 0) {
        strcpy(transparent, "0");
    }

    fprintf(svg, rectFormat, getXRect(rect), getYRect(rect), getWidthRect(rect), getHeightRect(rect), getFillColorRect(rect), getBorderColorRect(rect), transparent);

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