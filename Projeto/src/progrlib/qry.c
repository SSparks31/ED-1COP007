#include "./qry.h"

#include "../helper/pathHelp.h"
#include "../helper/mathHelp.h"
#include "../helper/stringHelp.h"

#include "../svg/svg.h"
#include "../svg/line.h"
#include "../svg/intersect.h"
#include "../svg/inside.h"

#include "../tree/kdTree.h"

#include "./person.h"
#include "./building.h"
#include "./meteor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMANDS 5

const double radiationLevels[7] = {25, 50, 100, 250, 500, 1000, 8000};

typedef struct txtOutput {
    void* elem;
    int num;
}* TxtOutput;

int comparePersonID(const void* a, const void* b) {
    Person personA = *(Person*) a;
    Person personB = *(Person*) b;

    char* idA = getIDCircle(personGetCircle(personA));
    char* idB = getIDCircle(personGetCircle(personB));

    if (isEmpty(idA) || isEmpty(idB)) {
        return -2;
    }

    return strcmp(idB, idA);
}

int compareBuildingID(const void* a, const void* b) {
    Building buildingA = *(Building*) a;
    Building buildingB = *(Building*) b;

    char* idA = getIDRect(buildingGetRect(buildingA));
    char* idB = getIDRect(buildingGetRect(buildingB));

    if (isEmpty(idA) || isEmpty(idB)) {
        return -2;
    }

    return strcmp(idB, idA);
}

int compareRectangleLeft(const void* a, const void* b, int j) {
    char* (*getDimension)(rectT rect);
    if (j) {
        getDimension = getXRect;
    } else {
        getDimension = getYRect;
    }

    rectT rectA = a;
    rectT rectB = b;

    double aDimension = stringToDouble(getDimension(rectA));
    double bDimension = stringToDouble(getDimension(rectB));

    if (aDimension < bDimension) {
        return -1;
    }
    if (aDimension > bDimension) {
        return 1;
    }

    return 0;
}

int compareRectangleRight(const void* a, const void* b, int j) {
    rectT rectA = (rectT) a;
    rectT rectB = (rectT) b;

    char* (*getDimension)(rectT rect);
    char* (*getLength)(rectT rect);
    if (j) {
        getDimension = getXRect;
        getLength = getWidthRect;
    } else {
        getDimension = getYRect;
        getLength = getHeightRect;
    }

    double dimA = stringToDouble(getDimension(rectA)) + stringToDouble(getLength(rectA));
    double dimB = stringToDouble(getDimension(rectB)) + stringToDouble(getLength(rectB));

    if (dimA < dimB) {
        return -1;
    }
    if (dimA > dimB) {
        return 1;
    }
    return 0;
}

void qryDRecursive(kdTree tree, kdNode node, rectT rect, int height, int isPoint, TxtOutput output) {    
    if (!node) {
        return;
    }
    
    Building building = getElemInKDNode(tree, node);
    rectT buildingRect = buildingGetRect(building);

    int compLeft;
    int compRight;
    
    int inside;
    char* width = getWidthRect(rect);  
    if (isPoint) {
        inside = rrInside(rect, buildingRect);        
        compLeft = compareRectangleLeft(rect, buildingRect, height);
        compRight = compareRectangleRight(rect, buildingRect, height);
    } else {
        inside = rrInside(buildingRect, rect);        
        compLeft = compareRectangleLeft(buildingRect, rect, height);
        compRight = compareRectangleRight(buildingRect, rect, height);
    }

    kdNode left = getKDNodeLeftChild(tree, node);
    kdNode right = getKDNodeRightChild(tree, node);
    
    if (compLeft == -1) {
        right = NULL;
    }

    if (compRight == 1) {
        left = NULL;
    }

    qryDRecursive(tree, left, rect, (height + 1) % 2, isPoint, output);
    qryDRecursive(tree, right, rect, (height + 1) % 2, isPoint, output);

    
    if (inside) {
        removeFromKDTree(tree, node);
        
        output->elem = realloc(output->elem, (output->num + 1) * sizeof(Building*));
        memcpy(output->elem + (sizeof(Building*) * output->num), &building, sizeof(Building*));
        output->num++;
    }

}

void qryDpi(progrData data, char* args, FILE* qryTXT, TxtOutput output) {
    char coordinates[999];
    sprintf(coordinates, "%s 0 0", args);
    rectT point = createRect("red", "red", "0", "pseudo", coordinates);

    kdTree tree = getBuildingTree(data);

    qryDRecursive(tree, getRootKDTree(tree), point, 1, 1, output);

    qsort(output->elem, output->num, sizeof(Person*), compareBuildingID);

    Building* removedBuildings = output->elem;
    for (int i = 0; i < output->num; ++i) {
        fprintf(qryTXT, "\t%s\n", getIDRect(buildingGetRect(removedBuildings[i])));
        demolishBuilding(removedBuildings[i]);
    }

    destroyRect(point);
}

void qryDr(progrData data, char* args, FILE* qryTXT, TxtOutput output) {}

void qryFg(progrData data, char* args, FILE* qryTXT, TxtOutput output) {}

void qryIm(progrData data, char* args, FILE* qryTXT, TxtOutput output) {}

void qryT30Recursion(kdTree tree, kdNode node, TxtOutput output) {
    if (!node) {
        return;
    }

    Person person = getElemInKDNode(tree, node);
    if (personGetRadiation(person) >= radiationLevels[5]) {
        killPerson(person);
        
        output->elem = realloc(output->elem, (output->num + 1) * sizeof(Person*));
        memcpy(output->elem + (sizeof(Person*) * output->num), &person, sizeof(Person*));
        output->num++;
    }

    qryT30Recursion(tree, getKDNodeLeftChild(tree, node), output);
    qryT30Recursion(tree, getKDNodeRightChild(tree, node), output);
}

void qryT30(progrData data, char* args, FILE* qryTXT, TxtOutput output) {
    kdTree tree = getPersonTree(data);
    qryT30Recursion(tree, getRootKDTree(tree), output);

    qsort(output->elem, output->num, sizeof(Person*), comparePersonID);

    Person* deadPeople = output->elem;
    for (int i = 0; i < output->num; ++i) {
        fprintf(qryTXT, "\t%s\n", getIDCircle(personGetCircle(deadPeople[i])));
    }
}



void qryParser(progrData data) {
    if (isEmpty(getQryName(data))) {
        return;
    }

    char* outputPath = getBSD(data);
    
    char* qryPath = concatPathFile(getBED(data), getQryName(data));
    FILE* qryFile = fopen(qryPath, "r");
    free(qryPath);
    
    if (!qryFile) {
        return;
    }

    char* geoName = stripSuffix(getGeoName(data));
    char* qryName = stripSuffix(getQryName(data));
    
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
        fclose(qryFile);
        return;
    }

    char* svgName = concatFileSuffix(outName, "svg");
    FILE* svgFile = startSVG(outputPath, svgName);
    free(svgName);
    free(outName);
    if (!svgFile) {
        fclose(qryFile);
        fclose(qryTXT);
        return;
    }

    fprintf(qryTXT, "Gregorio Rodrigues Favero\n\t202000560114\n");

    char command[999];

    const char* commands[COMMANDS] = {"dpi", "dr", "fg", "im", "t30"};
    void (*functions[COMMANDS])(progrData data, char* args, FILE* qryTXT, TxtOutput output) = {qryDpi, qryDr, qryFg, qryIm, qryT30};
    
    TxtOutput output = malloc(sizeof(struct txtOutput));
    if (!output) {
        fclose(qryFile);
        fclose(qryTXT);
        finishSVG(svgFile);
        return;
    }

    while (!isEmpty(fgetLine(qryFile, command, 999)) && fprintf(qryTXT, "===\n")) {
        output->elem = malloc(1);
        output->num = 0;

        char* args = splitString(command, ' ');
        fprintf(qryTXT, "%s\n", command);

        for (int i = 0; i < 5; ++i) {
            if (strcmp(commands[i], command) == 0) {
                functions[i](data, args, qryTXT, output);
                break;
            }
        }
        //printf("%d\n", output->num);

        free(output->elem);
    }

    free(output);
    fclose(qryFile);
    fclose(qryTXT);
    finishSVG(svgFile);

}