#include "geo.h"

#include <stdlib.h>
#include <stdio.h>

#include "./progrData.h"

#include "../helper/stringHelp.h"
#include <string.h>

#include "../svg/svg.h"
#include "../svg/circle.h"
#include "../svg/rect.h"

#include "../helper/pathHelp.h"

#define MENU_ITEMS 7

void nx(progrData data, char* args, FILE* svgFile) {
   // Funcao sem uso; arvore nao tem limite de itens
}

void cc(progrData data, char* args, FILE* svgFile) {
    if (!isEmpty(args)) {
        setRectBorder(data, args);
    }
}   

void cp(progrData data, char* args, FILE* svgFile) {
    if (!isEmpty(args)) {
        setRectFill(data, args);
    }
}

void bc(progrData data, char* args, FILE* svgFile) {
    if (!isEmpty(args)) {
        setCircleBorder(data, args);
    }
}

void pc(progrData data, char* args, FILE* svgFile) {
    if (!isEmpty(args)) {
        setCircleFill(data, args);
    }
}

void r(progrData data, char* args, FILE* svgFile) {
    if (!svgFile) {
        return;
    }

    char* ID = args;
    char* coordinates = splitString(args, ' ');

    char* borderColor = getRectBorder(data);
    char* fillColor = getRectFill(data);

    rectT newRect = createRect(borderColor, fillColor, "0.5", ID, coordinates);

    kdTree tree = getRectTree(data);
    appendKDTree(tree, newRect);

    addRectToSVG(svgFile, newRect);
}

void c(progrData data, char* args, FILE* svgFile) {
    if (!svgFile) {
        return;
    }

    char* ID = args;
    char* coordinates = splitString(args, ' ');

    char* borderColor = getCircleBorder(data);
    char* fillColor = getCircleFill(data);

    circleT newCircle = createCircle(borderColor, fillColor, "0.5", ID, coordinates);

    kdTree tree = getCircleTree(data);
    appendKDTree(tree, newCircle);

    addCircleToSVG(svgFile, newCircle);
}

void geoParser(progrData data) {
    if (!data) {
        return;
    }
    
    void (*menu[MENU_ITEMS])(progrData data, char* args, FILE* svgFile) = { nx, cc, cp, bc, pc, r, c };
    const char* options[MENU_ITEMS] = { "nx", "cc", "cp", "bc", "pc", "r", "c" };

    char command[999];
    char* args;
    
    char* BED = getBED(data);
    char* geoName = getGeoName(data);

    char* fullPath = concatPathFile(BED, geoName);
    FILE* geoFile = fopen(fullPath, "r");
    free(fullPath);
    
    if (!geoFile) {
        return;
    }

    char* BSD = getBSD(data);
    geoName = stripSuffix(geoName);    
    char* svgName = concatFileSuffix(geoName, "svg");

    FILE* svgFile = startSVG(BSD, svgName);
    free(svgName);
    free(geoName);
    
    if (!svgFile) {
        fclose(geoFile);
        return;
    }

    while (!isEmpty(fgetLine(geoFile, command, 999))) {
        args = splitString(command, ' ');
        if (!args) {
            return;
        }
        

        for (int i = 0; i < MENU_ITEMS; ++i) {
            if (strcmp(command, options[i]) == 0) {
                menu[i](data, args, svgFile);
            }
        }
    }

    finishSVG(svgFile);
    fclose(geoFile);
    
}

int main() {
    progrData data = createData("./", "./", "a1.geo", "");
    geoParser(data);

    destroyData(data);

    return 0;
}