#include "./listEfficiency.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./progrData.h"

#include "../list/list.h"

#include "../svg/svg.h"
#include "../svg/rect.h"
#include "../svg/line.h"
#include "../svg/circle.h"

#include "../helper/mathHelp.h"
#include "../helper/pathHelp.h"
#include "../helper/stringHelp.h"


int finishReportListEfficiency(progrDataT progrData, char* collectPath, char* collectTitle) {
    if (isEmpty(collectPath) || isEmpty(collectTitle)) {
        return -1;
    }

    char* outputPath = getOutputPathProgrData(progrData);
    char* svgName = concatFileSuffix(collectPath, "svg");
    char* fullPath = concatPathFile(outputPath, svgName);
    
    FILE* reportFile = fopen(fullPath, "w");
    free(svgName);
    free(fullPath);
    if (!reportFile) {
        return -1;
    }

    FILE* tempFile = fopen("./tempReport", "r"); 
    if (!tempFile) {
        fclose(reportFile);
        return -1;
    }
    
    listT entryList = createList(999);

    double xScale = 0, yScale = 0;

    char buffer[999];
    while (!isEmpty(fgetLine(tempFile, buffer, 99))) {
        char* qryName = buffer;
        char* coordinates = splitString(qryName, '|');
        circleT circle = createCircle("blue", "blue", coordinates);
        appendList(entryList, circle);

        double x = stringToDouble(getXCenterCircle(circle));
        double y = stringToDouble(getYCenterCircle(circle));

        xScale = dmax(x, xScale);
        yScale = dmax(y, yScale);        
    }
    strcpy(buffer, "");

    xScale *= 1.1;
    yScale *= 1.1;

    fprintf(reportFile, "<svg viewBox=\"0 0 1500 1500\">\n\n");
    fprintf(reportFile, "<rect width =\"100%%\" height=\"100%%\" fill=\"white\" />\n");
    fprintf(reportFile, "<text x=\"50%%\" y=\"70\" font-size=\"60\" text-anchor=\"middle\">%s</text>\n", collectTitle);
    
    fprintf(reportFile, "<line x1=\"50\" y1=\"1400\" x2=\"1400\" y2=\"1400\" stroke=\"black\" stroke-width=\"2\" />\n");
    fprintf(reportFile, "<line x1=\"100\" y1=\"100\" x2=\"100\" y2=\"1450\" stroke=\"black\" stroke-width=\"2\" />\n");

    fprintf(reportFile, "<line x1=\"1300\" y1=\"80\" x2=\"1400\" y2=\"80\" stroke=\"black\" stroke-width=\"2\" />\n");
    fprintf(reportFile, "<line x1=\"1300\" y1=\"60\" x2=\"1300\" y2=\"100\" stroke=\"black\" stroke-width=\"2\" />\n");
    fprintf(reportFile, "<line x1=\"1350\" y1=\"60\" x2=\"1350\" y2=\"100\" stroke=\"black\" stroke-width=\"1\" />\n");
    fprintf(reportFile, "<line x1=\"1400\" y1=\"60\" x2=\"1400\" y2=\"100\" stroke=\"black\" stroke-width=\"2\" />\n");
    fprintf(reportFile, "<text text-anchor=\"middle\" x=\"1300\" y=\"50\">0</text>\n");
    fprintf(reportFile, "<text text-anchor=\"middle\" x=\"1350\" y=\"50\">%.2lf</text>\n", xScale/24);
    fprintf(reportFile, "<text text-anchor=\"middle\" x=\"1400\" y=\"50\">%.2lf</text>\n", xScale/12);

    fprintf(reportFile, "<line x1=\"1350\" y1=\"140\" x2=\"1350\" y2=\"240\" stroke=\"black\" stroke-width=\"2\" />\n");
    fprintf(reportFile, "<line x1=\"1330\" y1=\"140\" x2=\"1370\" y2=\"140\" stroke=\"black\" stroke-width=\"2\" />\n");
    fprintf(reportFile, "<line x1=\"1330\" y1=\"190\" x2=\"1370\" y2=\"190\" stroke=\"black\" stroke-width=\"1\" />\n");
    fprintf(reportFile, "<line x1=\"1330\" y1=\"240\" x2=\"1370\" y2=\"240\" stroke=\"black\" stroke-width=\"2\" />\n");
    fprintf(reportFile, "<text text-anchor=\"start\" x=\"1380\" y=\"143\">0</text>\n");
    fprintf(reportFile, "<text text-anchor=\"start\" x=\"1380\" y=\"193\">%.2lf</text>\n", yScale/24);
    fprintf(reportFile, "<text text-anchor=\"start\" x=\"1380\" y=\"243\">%.2lf</text>\n", yScale/12);

    for (int i = 150; i < 1400; i+= 50) {
        fprintf(reportFile, "<line x1=\"80\" y1=\"%d\" x2=\"120\" y2=\"%d\" stroke=\"black\" stroke-width=\"%d\" />\n", i, i, 1 + (i/50 + 1)%2);
        fprintf(reportFile, "<line x1=\"%d\" y1=\"1380\" x2=\"%d\" y2=\"1420\" stroke=\"black\" stroke-width=\"%d\" />\n", i, i, 1 + (i/50 + 1)%2);    
    }

    while (!isEmptyList(entryList)) {
        circleT circle = removeList(entryList, getFirstElementList(entryList));
        char* xCenter = getXCenterCircle(circle);
        char* yCenter = getYCenterCircle(circle);

        double newXCenter = 100;
        newXCenter += 1300 * (stringToDouble(xCenter)/xScale);

        double newYCenter = 1400;
        newYCenter -= 1300 * (stringToDouble(yCenter)/yScale);
        
        sprintf(buffer, "%lf", newXCenter);
        setXCenterCircle(circle, buffer);

        sprintf(buffer, "%lf", newYCenter);
        setYCenterCircle(circle, buffer);

        xCenter = getXCenterCircle(circle);
        yCenter = getYCenterCircle(circle);

        char coordinates[300];
        sprintf(coordinates, "100 %s %s %s", yCenter, xCenter, yCenter);
        lineT dottedLine = createLine("black", coordinates);
        addDottedLineToSVG(reportFile, dottedLine);
        destroyLine(dottedLine);

        sprintf(coordinates, "%s 1400 %s %s", xCenter, xCenter, yCenter);
        dottedLine = createLine("black", coordinates);
        addDottedLineToSVG(reportFile, dottedLine);
        destroyLine(dottedLine);

        addCircleToSVG(reportFile, circle);
        destroyCircle(circle);        
    }

    destroyList(entryList);

    fclose(tempFile);
    remove("./tempReport");
    finishSVG(reportFile);

    return 0;
}

int reportListEfficiency(progrDataT progrData, int collect, char* collectPath, char* collectTitle) {
    if (!progrData || collect < 0 || collect > 3) {
        return -1;
    }
    
    if (collect == 0) {
        return 0;
    }

    char* mode[3] = {"w", "a", "a"};
    FILE* tempFile = fopen("./tempReport", mode[collect - 1]);
    if (!tempFile) {
        return -1;
    }

    listT rectList = getRectListProgrData(progrData);
    char* fileName = stripSuffix(getQryNameProgrData(progrData));
    fprintf(tempFile, "%s|%d %d 10\n", fileName, lengthList(rectList), getAccessCountList(rectList));
    if (fileName) free(fileName);
    fclose(tempFile);

    if (collect == 3) {
        return finishReportListEfficiency(progrData, collectPath, collectTitle);
    }

    return 0;
}