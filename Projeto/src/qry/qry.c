#include "qry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../svg/rect.h"
#include "../svg/svg.h"

#include "../helper/mathHelp.h"
#include "../helper/pathHelp.h"
#include "../helper/stringHelp.h"

int intersect(rectT rectA, rectT rectB) {
    if (!rectA || !rectB) {
        return -1;
    }

    double x1A = stringToDouble(getXRect(rectA));
    double x1B = stringToDouble(getXRect(rectB));
    double x1Max = dmax(x1A, x1B);
    double x2A = x1A + stringToDouble(getWidthRect(rectA));
    double x2B = x1B + stringToDouble(getWidthRect(rectB));
    double x2Min = dmin(x2A, x2B);

    if (x1Max > x2Min) {
        return 0;
    }
    
    double y1A = stringToDouble(getYRect(rectA));
    double y2A = y1A + stringToDouble(getHeightRect(rectA));
    double y1B = stringToDouble(getYRect(rectB));
    double y2B = y1B + stringToDouble(getHeightRect(rectB));
    double y1Max = dmax(y1A, y1B);
    double y2Min = dmin(y2A, y2B);

    return y1Max <= y2Min;    
}

int inside(rectT rectA, rectT rectB) {
    if (!rectA || !rectB) {
        return -1;
    }

    double x1A = stringToDouble(getXRect(rectA));
    double x1B = stringToDouble(getXRect(rectB));
    if (x1A < x1B) {
        return 0;
    }

    double y1A = stringToDouble(getYRect(rectA));
    double y1B = stringToDouble(getYRect(rectB));
    if (y1A < y1B) {
        return 0;
    }

    double x2A = x1A + stringToDouble(getWidthRect(rectA));
    double x2B = x1B + stringToDouble(getWidthRect(rectB));
    if (x2A > x2B) {
        return 0;
    }
    
    double y2A = y1A + stringToDouble(getHeightRect(rectA));    
    double y2B = y1B + stringToDouble(getHeightRect(rectB));
    
    return y2A <= y2B;
}

void printRectData(FILE* qryTXT, rectT rect) {
    if (!qryTXT || !rect) {
        return;
    }

    char* id = getIDRect(rect);
    char* xPos = getXRect(rect);
    char* yPos = getYRect(rect);
    char* width = getWidthRect(rect);
    char* height = getHeightRect(rect);
    char* fillColor = getFillColorRect(rect);
    char* borderColor = getBorderColorRect(rect);
    char* transparent = "transparente";

    if (strcmp(fillColor, "@") == 0) {
        fillColor = transparent;
    }
    if (strcmp(borderColor, "@") == 0) {
        borderColor = transparent;
    }

    fprintf(qryTXT, "ID: %s; Ancora: (%s, %s); Largura: %s; Altura: %s; Borda: %s; Preenchimento: %s\n", id, xPos, yPos, width, height, fillColor, borderColor);
}

listPosT findRectWithID(listT rectList, char* id) {
    listPosT aux = getFirstElementList(rectList);
    while (aux) {
        rectT rect = getElementList(rectList, aux);
        if (strcmp(getIDRect(rect), id) == 0) {
            return aux;
        }

        aux = getNextElementList(rectList, aux);
    }
    return NULL;
}

rectT getPointPseudoRect(char* coordinates) {
    if (isEmpty(coordinates)) {
        return NULL;
    }

    char newCoordinates[999];
    sprintf(newCoordinates, "%s 0 0", coordinates);

    rectT newRect = createRect("@", "@", "point", newCoordinates);
    return newRect;
}


char* tpColors[10] = {"red", "blue", "green", "yellow", "purple", "pink", "limegreen", "aqua", "orange", "darkorchid" };

void qryTP(FILE* qryTXT, progrDataT progrData, char* command) {
    if (!qryTXT || !progrData || isEmpty(command)) {
        return;
    }

    int tpIndex = 0;

    rectT bbox = NULL;

    char* spacePos = findCharacter(command, ' ');
    if (spacePos) {
        bbox = createRect("@", "@", "bbox", spacePos + 1);
    }


    listT rectList = getRectListProgrData(progrData);
    listPosT curPos = getFirstElementList(rectList);

    for (; curPos; curPos = getNextElementList(rectList, curPos)) {
        rectT curRect = getElementList(rectList, curPos);
        if (bbox && !inside(curRect, bbox)) {
            continue;
        }

        listPosT aux = getNextElementList(rectList, curPos);
        for (; aux; aux = getNextElementList(rectList, aux)) {
            rectT auxRect = getElementList(rectList, aux);
            if (bbox && !inside(auxRect, bbox)) {
                continue;
            }

            if (intersect(curRect, auxRect)) {
                fprintf(qryTXT, "%s %s\n", getIDRect(curRect), getIDRect(auxRect));
                setFillColorRect(curRect, tpColors[tpIndex]);
                setFillColorRect(auxRect, tpColors[tpIndex]);
                
                ++tpIndex;
                tpIndex %= 10;
            }
        }
    }

    if (bbox) destroyRect(bbox);

}



void qryD(FILE* qryTXT, progrDataT progrData, char* command) {
    if (!qryTXT || !progrData || isEmpty(command)) {
        return;
    }

    listT rectList = getRectListProgrData(progrData);
    rectT pointRect = NULL;
    rectT idRect = NULL;

    command = findCharacter(command, ' ') + 1;
    char* spacePos = findCharacter(command, ' ');
    if (spacePos) {
        pointRect = getPointPseudoRect(command);
    } else {
        idRect = getElementList(rectList, findRectWithID(rectList, command));
    }

    listPosT curPos = getFirstElementList(rectList);
    while (curPos) {
        rectT curRect = getElementList(rectList, curPos);

        int remove = 0;

        if (pointRect) {
            remove = inside(pointRect, curRect);
        } else {
            remove = curRect != idRect && inside(curRect, idRect);
        }

        listPosT aux = getNextElementList(rectList, curPos);
        if (remove) {
            fprintf(qryTXT, "%s\n", getIDRect(curRect));
            destroyRect(removeList(rectList, curPos));
        }
        curPos = aux;        
    }


    if (pointRect) destroyRect(pointRect);    
}



rectT getNewBoundingBox(rectT curBBox, rectT newRect) {
    if (!curBBox) {
        char coordinates[13] = "-1 -1 -1 -1";
        rectT newBBox = createRect("red", "@", "bbox", coordinates);
        return newBBox;
    }

    if (!newRect) {
        return curBBox;
    }

    double x1A = stringToDouble(getXRect(newRect));
    double x2A = x1A + stringToDouble(getWidthRect(newRect));
    double y1A = stringToDouble(getYRect(newRect));
    double y2A = y1A + stringToDouble(getHeightRect(newRect));

    double x1B = stringToDouble(getXRect(curBBox));
    double x2B = x1B + stringToDouble(getWidthRect(curBBox));
    double y1B = stringToDouble(getYRect(curBBox));
    double y2B = y1B + stringToDouble(getHeightRect(curBBox));

    double newX = x1B == -1 ? x1A : dmin(x1A, x1B);
    double newY = y1B == -1 ? y1A : dmin(y1A, y1B);
    double newX2 = dmax(x2A, x2B);
    double newY2 = dmax(y2A, y2B);

    char coordinates[999];
    sprintf(coordinates, "%lf %lf %lf %lf", newX, newY, newX2 - newX, newY2 - newY);

    setCoordinatesRect(curBBox, coordinates);

    return curBBox;
}

void qryBBI(FILE* qryTXT, progrDataT progrData, char* command) {
    if (!qryTXT || !progrData || isEmpty(command)) {
        return;
    }

    command = findCharacter(command, ' ') + 1;

    listT rectList = getRectListProgrData(progrData);
    rectT bbox = NULL;

    char *spacePos = findCharacter(command, ' ');
    if (!spacePos) {
        bbox = getElementList(rectList, findRectWithID(rectList, command));
        if (bbox == NULL) {
            fprintf(qryTXT, "Nao foi possivel encontrar o retangulo com o id selecionado\n");
        }
    } else {
        rectT pointRect = getPointPseudoRect(command);
        bbox = getNewBoundingBox(NULL, NULL);
        
        listPosT aux = getFirstElementList(rectList);
        while (aux) {
            rectT auxRect = getElementList(rectList, aux);
            if (inside(pointRect, auxRect)) {
                bbox = getNewBoundingBox(bbox, auxRect);
            }
            aux = getNextElementList(rectList, aux);
        }

        destroyRect(pointRect);
    }

    listPosT curPos = getFirstElementList(rectList);

    while (curPos) {
        rectT curRect = getElementList(rectList, curPos);
        if (bbox != curRect && inside(curRect, bbox) == 1) {
            printRectData(qryTXT, curRect);
            
            char temp[999];
            char* borderColor = getBorderColorRect(curRect);
            char* fillColor = getFillColorRect(curRect);

            strcpy(temp, borderColor);
            setBorderColorRect(curRect, fillColor);
            setFillColorRect(curRect, temp);
        }

        curPos = getNextElementList(rectList, curPos);
    }

    if (spacePos) destroyRect(bbox);
}



void qryIID(FILE* qryTXT, progrDataT progrData, char* command) {
    if (!qryTXT || !progrData || isEmpty(command)) {
        return;
    }

    int remove = command[0] == 'd';

    command = findCharacter(command, ' ') + 1;
    int k = 0;

    char* spacePos = findCharacter(command, ' ');
    if (spacePos) {
        *spacePos = '\0';
        k = stringToInt(spacePos + 1);
    }

    listT rectList = getRectListProgrData(progrData);
    listPosT curPos = findRectWithID(rectList, command);
    if (!curPos) {
        fprintf(qryTXT, "Nao foi possivel encontrar o retangulo com o id selecionado\n");
        return;
    }

    printRectData(qryTXT, getElementList(rectList, curPos));

    while (curPos && k-- > 0) {
        curPos = getNextElementList(rectList, curPos);
        printRectData(qryTXT, getElementList(rectList, curPos));

        if (remove) {
            listPosT aux = getNextElementList(rectList, curPos);
            destroyRect(removeList(rectList, curPos));
            curPos = aux;
        }
    }

    while (curPos && ++k < 0) {
        curPos = getPrevElementList(rectList, curPos);
        printRectData(qryTXT, getElementList(rectList, curPos));

        if (remove) {
            listPosT aux = getNextElementList(rectList, curPos);
            destroyRect(removeList(rectList, curPos));
            curPos = aux;
        }
    }

}

void qryParser(progrDataT progrData) {
    if (isEmpty(getQryNameProgrData(progrData))) {
        return;
    }

    char* outputPath = getOutputPathProgrData(progrData);
    
    char* qryPath = concatPathFile(getInputPathProgrData(progrData), getQryNameProgrData(progrData));
    FILE* qryFile = fopen(qryPath, "r");
    free(qryPath);
    
    if (!qryFile) {
        return;
    }

    char* geoName = stripSuffix(getGeoNameProgrData(progrData));
    char* qryName = stripSuffix(getQryNameProgrData(progrData));
    
    char* outName = malloc(sizeof(char) * (strlen(geoName) + strlen("-") + strlen(qryName) + 1));
    sprintf(outName, "%s-%s", geoName, qryName);
    
    char* txtName = concatFileSuffix(outName, "txt");
    char* txtPath = concatPathFile(outputPath, txtName);

    FILE* qryTXT = fopen(txtPath, "w");
    
    free(txtPath);
    free(txtName);
    free(qryName);
    free(geoName);
    
    if (!qryTXT) {
        return;
    }

    char command[999];

    while (!isEmpty(fgetLine(qryFile, command, 999))) {
        
        char* spacePos = findCharacter(command, ' ');
        if (spacePos) *spacePos = '\0';
        fprintf(qryTXT, "%s\n", command);
        if (spacePos) *spacePos = ' ';

        if (command[0] == 't') {
            qryTP(qryTXT, progrData, command);
        } else if (command[1] == 'i') {
            qryIID(qryTXT, progrData, command);
        } else if (command[0] == 'd') {
            qryD(qryTXT, progrData, command);
        } else if (command[0] == 'b') {
            qryBBI(qryTXT, progrData, command);
        }

        fprintf(qryTXT, "\n");
    }

    fclose(qryFile);

    char* svgName = concatFileSuffix(outName, "svg");
    FILE* svgFile = startSVG(outputPath, svgName);
    free(svgName);
    free(outName);
    if (!svgFile) {
        fclose(qryTXT);
        return;
    }


    listT rectList = getRectListProgrData(progrData);
    listPosT aux = getFirstElementList(rectList);
    while (aux) {
        rectT rect = getElementList(rectList, aux);
        addRectToSVG(svgFile, rect);
        aux = getNextElementList(rectList, aux);
    }

    // FILE* bboxTemp = fopen("./bbox-temp", "r");
    // char buffer[999];
    // while (fgetLine(bboxTemp, buffer, 999)) {
    //     // addBBoxToSVG()
    // }

    remove("./bbox-temp");

    finishSVG(svgFile);

    fclose(qryTXT);
}