#include "./listEfficiency.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../progrData/progrData.h"

#include "./list.h"

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

    char buffer[99];
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

    xScale *= 1.05;
    yScale *= 1.05;

    fprintf(reportFile, "<svg viewBox=\"0 0 500 500\">\n\n");
    fprintf(reportFile, "<rect width =\"100%%\" height=\"100%%\" fill=\"white\" />\n");
    fprintf(reportFile, "<text x=\"50%%\" y=\"30\" font-size=\"25\" text-anchor=\"middle\">%s</text>\n", collectTitle);
    fprintf(reportFile, "<line x1=\"30\" y1=\"450\" x2=\"450\" y2=\"450\" stroke=\"black\" stroke-width=\"2\" />\n");
    fprintf(reportFile, "<line x1=\"50\" y1=\"50\" x2=\"50\" y2=\"470\" stroke=\"black\" stroke-width=\"2\" />\n");

    fprintf(reportFile, "<line x1=\"425\" y1=\"30\" x2=\"475\" y2=\"30\" stroke=\"black\" stroke-width=\"2\" />\n");
    fprintf(reportFile, "<line x1=\"425\" y1=\"20\" x2=\"425\" y2=\"40\" stroke=\"black\" stroke-width=\"1\" />\n");
    fprintf(reportFile, "<line x1=\"475\" y1=\"20\" x2=\"475\" y2=\"40\" stroke=\"black\" stroke-width=\"1\" />\n");
    fprintf(reportFile, "<text text-anchor=\"middle\" x=\"425\" y=\"18\">0</text>\n");
    fprintf(reportFile, "<text text-anchor=\"middle\" x=\"475\" y=\"18\">%.1lf</text>\n", xScale/8);

    fprintf(reportFile, "<line x1=\"460\" y1=\"55\" x2=\"460\" y2=\"105\" stroke=\"black\" stroke-width=\"2\" />\n");
    fprintf(reportFile, "<line x1=\"450\" y1=\"55\" x2=\"470\" y2=\"55\" stroke=\"black\" stroke-width=\"1\" />\n");
    fprintf(reportFile, "<line x1=\"450\" y1=\"105\" x2=\"470\" y2=\"105\" stroke=\"black\" stroke-width=\"1\" />\n");
    fprintf(reportFile, "<text text-anchor=\"middle\" x=\"460\" y=\"50\">0</text>\n");
    fprintf(reportFile, "<text text-anchor=\"middle\" x=\"460\" y=\"118\">%.1lf</text>\n", yScale/8);

    for (int i = 1; i < 10; i++) {
        fprintf(reportFile, "<line x1=\"60\" y1=\"%d\" x2=\"40\" y2=\"%d\" stroke=\"black\" stroke-width=\"1\" />\n", 50*i, 50*i);    
        fprintf(reportFile, "<text x=\"30\" y=\"%d\" font-size=\"10\"></text>\n", 50*i);    
        fprintf(reportFile, "<line x1=\"%d\" y1=\"440\" x2=\"%d\" y2=\"460\" stroke=\"black\" stroke-width=\"1\" />\n", 50*i, 50*i);    
        fprintf(reportFile, "<text x=\"%d\" y=\"470\" font-size=\"10\"></text>\n", 50*i);    
    }

    while (!isEmptyList(entryList)) {
        circleT circle = removeList(entryList, getFirstElementList(entryList));
        char* xCenter = getXCenterCircle(circle);
        char* yCenter = getYCenterCircle(circle);

        double newXCenter = 50;
        newXCenter += 400 * (stringToDouble(xCenter)/xScale);

        double newYCenter = 450;
        newYCenter -= 400 * (stringToDouble(yCenter)/yScale);

        
        char coordinates[300];
        sprintf(buffer, "%lf", newXCenter);
        setXCenterCircle(circle, buffer);

        sprintf(buffer, "%lf", newYCenter);
        setYCenterCircle(circle, buffer);

        addCircleToSVG(reportFile, circle);
        
        xCenter = getXCenterCircle(circle);
        yCenter = getYCenterCircle(circle);

        sprintf(coordinates, "50 %s %s %s", yCenter, xCenter, yCenter);
        lineT dottedLine = createLine("black", coordinates);
        addDottedLineToSVG(reportFile, dottedLine);
        destroyLine(dottedLine);

        sprintf(coordinates, "%s 450 %s %s", xCenter, xCenter, yCenter);
        dottedLine = createLine("black", coordinates);
        addDottedLineToSVG(reportFile, dottedLine);
        destroyLine(dottedLine);

    }

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
    fprintf(tempFile, "%s|%d %d 3\n", fileName, lengthList(rectList), getAccessCountList(rectList));
    if (fileName) free(fileName);
    fclose(tempFile);

    if (collect == 3) {
        return finishReportListEfficiency(progrData, collectPath, collectTitle);
    }

    return 0;
}