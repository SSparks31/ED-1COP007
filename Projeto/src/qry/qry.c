#include "qry.h"

#include <stdio.h>
#include <stdlib.h>

#include "../svg/rect.h"

#include "../helper/pathHelp.h"
#include "../helper/mathHelp.h"

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

void qryTP(progrDataT progrData, char* command);

void qryTPR(progrDataT progrData, char* command);

void qryDPI(progrDataT progrData, char* command);

void qryDR(progrDataT progrData, char* command);

void qryBBI(progrDataT progrData, char* command);

void qryBBID(progrDataT progrData, char* command);

void qryIID(progrDataT progrData, char* command);

void qryDIID(progrDataT progrData, char* command);

listT qryParser(progrDataT progrData) {

}