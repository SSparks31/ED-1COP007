#include "./listEfficiency.h"

#include <stdio.h>
#include <stdlib.h>

#include "../progrData/progrData.h"

#include "./list.h"

#include "../helper/pathHelp.h"
#include "../helper/stringHelp.h"


int finishReportListEfficiency(progrDataT progrData, char* collectPath, char* collectTitle) {
    if (isEmpty(collectPath) || isEmpty(collectTitle)) {
        return -1;
    }

    char* outputPath = getOutputPathProgrData(progrData);
    char* fullPath = concatPathFile(outputPath, collectPath);

    FILE* reportFile = fopen(fullPath, "w");
    free(fullPath);
    if (!reportFile) {
        return -1;
    }

    FILE* tempFile = fopen("./tempReport", "r"); 
    if (!tempFile) {
        fclose(reportFile);
        return -1;
    }

    char buffer[999];
    while (!isEmpty(fgetLine(tempFile, buffer, 999))) {
        printf("%s\n", buffer);
    }

    fclose(tempFile);
    fclose(reportFile);

}

int reportListEfficiency(progrDataT progrData, int collect, char* collectPath, char* collectTitle) {
    if (!progrData || collect < 0 || collect > 3) {
        return -1;
    }
    
    if (collect == 0) {
        return 0;
    }

    if (collect == 3) {
        return finishReportListEfficiency(progrData, collectPath, collectTitle);
    }

    char* mode[2] = {"w", "a"};
    FILE* tempFile = fopen("./tempReport", mode[collect - 1]);
    if (!tempFile) {
        return -1;
    }

    listT rectList = getRectListProgrData(progrData);
    char* fileName = stripSuffix(getQryNameProgrData(progrData));
    fprintf(tempFile, "%s||%d||%d\n", fileName, getAccessCountList(rectList), lengthList(rectList));
    if (fileName) free(fileName);
    fclose(tempFile);

}