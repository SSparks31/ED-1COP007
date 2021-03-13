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

    const char* rectFormat = "<rect x = \"%s\" y = \"%s\" width = \"%s\" height = \"%s\" fill=\"%s\" stroke = \"%s\" fill-opacity=\"%s\" stroke-opacity=\"%s\" />\n";

    char* x = getXRect(rect);
    char* y = getYRect(rect);
    char* width = getWidthRect(rect);
    char* height = getHeightRect(rect);
    char* fillColor = getFillColorRect(rect);
    char* borderColor = getBorderColorRect(rect);

    char borderOpacity[4] = "100";
    if (strcmp(borderColor, "@") == 0) {
        strcpy(borderOpacity, "0");
    }

    char fillOpacity[4] = "100";
    if (strcmp(fillColor, "@") == 0) {
        strcpy(fillOpacity, "0");
    }

    fprintf(svgFile, rectFormat, x, y, width, height, fillColor, borderColor, fillOpacity, borderOpacity);
    return 0;
}

int addDottedRectToSVG(FILE* svgFile, rectT rect) {
    if (!svgFile || !rect) {
        return -1;
    }

    const char* rectFormat = "<rect x = \"%s\" y = \"%s\" width = \"%s\" height = \"%s\" fill=\"%s\" stroke = \"%s\" fill-opacity=\"%s\" stroke-opacity=\"%s\" stroke-width=\"2\" stroke-dasharray=\"2\" />\n";

    char* x = getXRect(rect);
    char* y = getYRect(rect);
    char* width = getWidthRect(rect);
    char* height = getHeightRect(rect);
    char* fillColor = getFillColorRect(rect);
    char* borderColor = getBorderColorRect(rect);

    char borderOpacity[4] = "100";
    if (strcmp(borderColor, "@") == 0) {
        strcpy(borderOpacity, "0");
    }

    char fillOpacity[4] = "100";
    if (strcmp(fillColor, "@") == 0) {
        strcpy(fillOpacity, "0");
    }

    fprintf(svgFile, rectFormat, x, y, width, height, fillColor, borderColor, fillOpacity, borderOpacity);
    return 0;
}

int addLineToSVG(FILE* svgFile, lineT line) {
    if (!svgFile || !line) {
        return -1;
    }

    const char* lineFormat = "<line x1 = \"%s\" y1 = \"%s\" x2 = \"%s\" y2 = \"%s\" stroke = \"%s\" stroke-width=\"1\" />\n";

    char* color = getColorLine(line);
    char* x1 = getX1Line(line);
    char* y1 = getY1Line(line);
    char* x2 = getX2Line(line);
    char* y2 = getY2Line(line);

    fprintf(svgFile, lineFormat, x1, y1, x2, y2, color);
}

int addDottedLineToSVG(FILE* svgFile, lineT line) {
    if (!svgFile || !line) {
        return -1;
    }

    const char* lineFormat = "<line x1=\"%s\" y1=\"%s\" x2=\"%s\" y2=\"%s\" stroke=\"%s\"  stroke-width=\"1\" stroke-dasharray=\"1\" />\n";

    char* color = getColorLine(line);
    char* x1 = getX1Line(line);
    char* y1 = getY1Line(line);
    char* x2 = getX2Line(line);
    char* y2 = getY2Line(line);

    fprintf(svgFile, lineFormat, x1, y1, x2, y2, color);
    return 0;
}

int addCircleToSVG(FILE* svgFile, circleT circle) {
    if (!svgFile || !circle) {
        return -1;
    }

    const char* circleFormat = "<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" fill=\"%s\" stroke-width=\"1\" stroke-opacity=\"%s\" fill-opacity=\"%s\" />\n";

    char* borderColor = getBorderColorCircle(circle); 
    char* fillColor = getFillColorCircle(circle); 
    char* xCenter = getXCenterCircle(circle); 
    char* yCenter = getYCenterCircle(circle); 
    char* radius = getRadiusCircle(circle);

    char borderOpacity[4] = "100";
    if (strcmp(borderColor, "@") == 0) {
        strcpy(borderOpacity, "0");
    }

    char fillOpacity[4] = "100";
    if (strcmp(fillColor, "@") == 0) {
        strcpy(fillOpacity, "0");
    }

    fprintf(svgFile, circleFormat, xCenter, yCenter, radius, borderColor, fillColor, borderOpacity, fillOpacity);
    return 0;
}

int addDottedCircleToSVG(FILE* svgFile, circleT circle) {
    if (!svgFile || !circle) {
        return -1;
    }

    const char* circleFormat = "<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" fill=\"%s\" stroke-width=\"1\" stroke-opacity=\"%s\" fill-opacity=\"%s\" stroke-dasharray=\"1\" />\n";

    char* borderColor = getBorderColorCircle(circle); 
    char* fillColor = getFillColorCircle(circle); 
    char* xCenter = getXCenterCircle(circle); 
    char* yCenter = getYCenterCircle(circle); 
    char* radius = getRadiusCircle(circle); 

    char borderOpacity[4] = "100";
    if (strcmp(borderColor, "@") == 0) {
        strcpy(borderOpacity, "0");
    }

    char fillOpacity[4] = "100";
    if (strcmp(fillColor, "@") == 0) {
        strcpy(fillOpacity, "0");
    }

    fprintf(svgFile, circleFormat, xCenter, yCenter, radius, borderColor, fillColor, borderOpacity, fillOpacity);
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