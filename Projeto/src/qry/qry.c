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
    double y1A = stringToDouble(getYRect(rectA));
    double x2A = x1A + stringToDouble(getWidthRect(rectA));
    double y2A = y1A + stringToDouble(getHeightRect(rectA));
    
    double x1B = stringToDouble(getXRect(rectB));
    double y1B = stringToDouble(getYRect(rectB));
    double x2B = x1B + stringToDouble(getWidthRect(rectB));
    double y2B = y1B + stringToDouble(getHeightRect(rectB));

    double x1Max = max(x1A, x1B);
    double x2Min = min(x2A, x2B);
    double y1Max = max(y1A, y1B);
    double y2Min = min(y2A, y2B);

    return x1Max <= x2Min && y1Max <= y2Min;    
}

int inside(rectT rectA, rectT rectB) {
    if (!rectA || !rectB) {
        return -1;
    }

    double x1A = stringToDouble(getXRect(rectA));
    double y1A = stringToDouble(getYRect(rectA));
    double x2A = x1A + stringToDouble(getWidthRect(rectA));
    double y2A = y1A + stringToDouble(getHeightRect(rectA));
    
    double x1B = stringToDouble(getXRect(rectB));
    double y1B = stringToDouble(getYRect(rectB));
    double x2B = x1B + stringToDouble(getWidthRect(rectB));
    double y2B = y1B + stringToDouble(getHeightRect(rectB));

    int isInsideX = x1A >= x1B && x2A <= x2B;
    int isInsideY = y1A >= y1B && y2A <= y2B;

    return isInsideX && isInsideY;
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
    char* transparent = "transparent";

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



char* tpColors[10] = {"red", "blue", "green", "yellow", "purple", "pink", "limegreen", "aqua", "orange", "darkorchid" };

void qryTP(FILE* qryTXT, progrDataT progrData, char* command) {
    if (!qryTXT || !progrData || isEmpty(command)) {
        return;
    }
}



void qryD(FILE* qryTXT, progrDataT progrData, char* command) {
    
}



rectT getBoundingBoxBBI()

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
            printf("Nao foi possivel encontrar o retangulo com o id selecionado\n");
        }
    } else {
    }

    listPosT curPos = getFirstElementList(rectList);

    while (curPos) {
        rectT curRect = getElementList(rectList, curPos);
        if (bbox != curRect && inside(curRect, bbox) == 1) {
            printRectData(qryTXT, curRect);
            
            char temp[SVG_COLOR_MAX_LEN];
            char* borderColor = getBorderColorRect(curRect);
            char* fillColor = getFillColorRect(curRect);

            strcpy(temp, borderColor);
            strcpy(borderColor, fillColor);
            strcpy(fillColor, temp);
        }

        curPos = getNextElementList(rectList, curPos);
    }
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
        printf("%s\n%s\n", command, spacePos + 1);
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
        *spacePos = '\0';
        fprintf(qryTXT, "%s\n", command);
        *spacePos = ' ';

        if (command[0] == 't') {
            qryTP(qryTXT, progrData, command);
        } else if (command[1] == 'i') {
            qryIID(qryTXT, progrData, command);
        } else if (command[0] == 'd') {
            qryD(qryTXT, progrData, command);
        } else if (command[0] == 'b') {
            qryBBI(qryTXT, progrData, command);
        }
    }

    fclose(qryFile);

    char* svgName = concatFileSuffix(outName, "svg");
    startSVG(outputPath, svgName);

    listT rectList = getRectListProgrData(progrData);
    listPosT aux = getFirstElementList(rectList);
    while (aux) {
        rectT rect = getElementList(rectList, aux);
        addRectToSVG(outputPath, svgName, rect);
        aux = getNextElementList(rectList, aux);
    }

    // FILE* bboxTemp = fopen("./bbox-temp", "r");
    // char buffer[999];
    // while (fgetLine(bboxTemp, buffer, 999)) {
    //     // addBBoxToSVG()
    // }

    remove("./bbox-temp");

    finishSVG(outputPath, svgName);

    free(svgName);
    free(outName);
    fclose(qryTXT);
}