#include "./qry.h"

#include "../helper/pathHelp.h"
#include "../helper/mathHelp.h"
#include "../helper/stringHelp.h"

#include "../svg/svg.h"
#include "../svg/line.h"
#include "../svg/intersect.h"
#include "../svg/inside.h"

#include "../tree/kdTree.h"

#include "../list/list.h"

#include "./person.h"
#include "./building.h"
#include "./meteor.h"
#include "./shadow.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMANDS 6

typedef struct txtOutput {
    void* elem;
    int num;
}* TxtOutput;


int rectIDCompare(const kdTreeElem a, const void* b) {
    char* idA = getIDRect(buildingGetRect(a));
    char* idB = (char*) b;

    return strcmp(idA, idB);
}

rectT findRectWithID(kdTree tree, char* id) {
    kdNode rectNode = findKDNodeCustomSearch(tree, id, rectIDCompare);
    return buildingGetRect(getElemInKDNode(tree, rectNode));
}

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

    rectT rectA = (rectT) a;
    rectT rectB = (rectT) b;

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
    char* (*getDimension)(rectT rect);
    char* (*getLength)(rectT rect);
    if (j) {
        getDimension = getXRect;
        getLength = getWidthRect;
    } else {
        getDimension = getYRect;
        getLength = getHeightRect;
    }

    rectT rectA = (rectT) a;
    rectT rectB = (rectT) b;

    double aDimension = stringToDouble(getDimension(rectA)) + stringToDouble(getLength(rectA));
    double bDimension = stringToDouble(getDimension(rectB)) + stringToDouble(getLength(rectB));

    if (aDimension < bDimension) {
        return -1;
    }
    if (aDimension > bDimension) {
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

    int compLeft = compareRectangleLeft(rect, buildingRect, height);
    int compRight = compareRectangleRight(rect, buildingRect, height);
    
    kdNode left = getKDNodeLeftChild(tree, node);
    kdNode right = getKDNodeRightChild(tree, node);

    int inside;
    if (isPoint) {
        inside = rrInside(rect, buildingRect);        
        if (compLeft == -1) {
            right = NULL;
        }
        if (compRight == 1) {
            left = NULL;
        }
    } else {
        inside = rrInside(buildingRect, rect); 
        if (compLeft == 1) {
            left = NULL;
        }
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

    qsort(output->elem, output->num, sizeof(Building*), compareBuildingID);

    Building* removedBuildings = output->elem;
    for (int i = 0; i < output->num; ++i) {
        fprintf(qryTXT, "\t%s\n", getIDRect(buildingGetRect(removedBuildings[i])));
        demolishBuilding(removedBuildings[i]);
    }

    destroyRect(point);
}

void qryDr(progrData data, char* args, FILE* qryTXT, TxtOutput output) {
    kdTree tree = getBuildingTree(data);
    rectT rect = findRectWithID(tree, args);
    
    qryDRecursive(tree, getRootKDTree(tree), rect, 1, 0, output);

    qsort(output->elem, output->num, sizeof(Building*), compareBuildingID);

    Building* removedBuildings = output->elem;
    for (int i = 0; i < output->num; ++i) {
        fprintf(qryTXT, "\t%s\n", getIDRect(buildingGetRect(removedBuildings[i])));
        demolishBuilding(removedBuildings[i]);
    }

}

void qryFg(progrData data, char* args, FILE* qryTXT, TxtOutput output) {}


const double radiationLevels[7] = { 25, 50, 100, 250, 500, 1000, 8000 };

char* colors[8] = { "cyan", "lime", "magenta", "blue", "darkmagenta", "darkblue", "red", "black" };

void createShadows(progrData data, Meteor meteor, kdTree tree, kdNode node) {
    if (!node) {
        return;
    }

    rectT buildingRect = buildingGetRect(getElemInKDNode(tree, node));
    double x1 = stringToDouble(getXRect(buildingRect));
    double x2 = x1 + stringToDouble(getWidthRect(buildingRect));
    double y1 = stringToDouble(getYRect(buildingRect));
    double y2 = y1 + stringToDouble(getHeightRect(buildingRect));

    listT shadowList = getShadowList(data);


    char coordinates[999];
    sprintf(coordinates, "%lf %lf %lf %lf", x1, y1, x1, y2);
    appendList(shadowList, createShadow(coordinates, meteor));

    sprintf(coordinates, "%lf %lf %lf %lf", x1, y1, x2, y1);
    appendList(shadowList, createShadow(coordinates, meteor));

    sprintf(coordinates, "%lf %lf %lf %lf", x1, y2, x2, y2);
    appendList(shadowList, createShadow(coordinates, meteor));

    sprintf(coordinates, "%lf %lf %lf %lf", x2, y1, x2, y2);
    appendList(shadowList, createShadow(coordinates, meteor));

}

double getAttenuation(Person person, Shadow shadow) {
    Meteor meteor = shadowGetMeteor(shadow);
    
    circleT personCircle = personGetCircle(person);
    circleT meteorCircle = meteorGetCircle(meteor);

    char* x1 = getXCenterCircle(personCircle);
    char* y1 = getYCenterCircle(personCircle);
    char* x2 = getXCenterCircle(meteorCircle);
    char* y2 = getYCenterCircle(meteorCircle);

    char coordinates[999];
    sprintf(coordinates, "%s %s %s %s", x1, y1, x2, y2);
    lineT sight = createLine("green", coordinates);
    lineT wall = shadowGetGeneratingWall(shadow);

    return llIntersect(sight, wall)? 0.8 : 1;
}

void chernobyl(progrData data, listT list, listPosT firstShadow, kdTree tree, kdNode node, TxtOutput output) {
    if (!node) {
        return;
    }
    
    listPosT aux = firstShadow;
    Shadow shadow = getElementList(list, firstShadow);

    Meteor meteor = shadowGetMeteor(shadow);
    double radiation = meteorGetRadiation(meteor);
    
    Person person = getElemInKDNode(tree, node);
    circleT personCircle = personGetCircle(person);

    while (aux) {
        shadow = getElementList(list, aux);
        radiation *= getAttenuation(person, shadow);
        aux = getNextElementList(list, aux);
    }
    
    personAddRadiation(person, radiation);
    
    double totalRadiation = personGetRadiation(person);
    int i;
    for (i = 0; i < 7; ++i) {
        if (radiationLevels[i] > totalRadiation) {
            break;
        }
    }

    if (i == 7) {
        killPerson(person);
    }
    
    if (i >= 6 && !personIsDead(person)) {
        output->elem = realloc(output->elem, (output->num + 1) * sizeof(Person*));
        memcpy(output->elem + (sizeof(Person*) * output->num), &person, sizeof(Person*));
        output->num++;
    }

    setFillColorCircle(personCircle, colors[i]);
    setBorderColorCircle(personCircle, colors[i]);
    
    kdNode left = getKDNodeLeftChild(tree, node);
    kdNode right = getKDNodeRightChild(tree, node);

    chernobyl(data, list, firstShadow, tree, left, output);
    chernobyl(data, list, firstShadow, tree, right, output);
}

void qryIm(progrData data, char* args, FILE* qryTXT, TxtOutput output) {
    double radiation = stringToDouble(rfindCharacter(args, ' ') + 1);
    
    circleT circle = createCircle("gray", "gray", ".8", "a", args);
    
    Meteor meteor = createMeteor(circle, radiation);
    
    listT meteorList = getMeteorList(data);
    appendList(meteorList, meteor);

    listT shadowList = getShadowList(data);
    listPosT aux = getLastElementList(shadowList);

    kdTree buildingTree = getBuildingTree(data);

    createShadows(data, meteor, buildingTree, getRootKDTree(buildingTree));

    kdTree personTree = getPersonTree(data);
    chernobyl(data, shadowList, aux, personTree, getRootKDTree(personTree), output);

    qsort(output->elem, output->num, sizeof(Person*), comparePersonID);

    Person* reportPeople = output->elem;
    for (int i = 0; i < output->num; ++i) {
        if (personGetRadiation(reportPeople[i]) > radiationLevels[6]) {
            fprintf(qryTXT, "\tMorte instantanea - ");    
        } else {
            fprintf(qryTXT, "\tMorte iminente - ");
        }
        
        fprintf(qryTXT, "%s (%lf)\n", getIDCircle(personGetCircle(reportPeople[i])), personGetRadiation(reportPeople[i]));
        
    }
}

void qryT30Recursion(kdTree tree, kdNode node, TxtOutput output) {
    if (!node) {
        return;
    }

    Person person = getElemInKDNode(tree, node);
    if (personGetRadiation(person) >= radiationLevels[5] && !personIsDead(person)) {
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

void qryNve(progrData data, char* args, FILE* qryTXT, TxtOutput output) {}


void printBuildings(FILE* svgFile, kdTree tree, kdNode node) {
    if (!node) {
        return;
    }

    rectT rect = buildingGetRect(getElemInKDNode(tree, node));
    addRectToSVG(svgFile, rect);

    kdNode left = getKDNodeLeftChild(tree, node);
    kdNode right = getKDNodeRightChild(tree, node);

    printBuildings(svgFile, tree, left);
    printBuildings(svgFile, tree, right);
}

void printPeople(FILE* svgFile, kdTree tree, kdNode node) {
    if (!node) {
        return;
    }

    circleT circle = personGetCircle(getElemInKDNode(tree, node));
    addCircleToSVG(svgFile, circle);

    kdNode left = getKDNodeLeftChild(tree, node);
    kdNode right = getKDNodeRightChild(tree, node);

    printPeople(svgFile, tree, left);
    printPeople(svgFile, tree, right);
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

    const char* commands[COMMANDS] = {"dpi", "dr", "fg", "im", "t30", "nve"};
    void (*functions[COMMANDS])(progrData data, char* args, FILE* qryTXT, TxtOutput output) = {qryDpi, qryDr, qryFg, qryIm, qryT30, qryNve};
    
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

        free(output->elem);
    }

    kdTree buildingTree = getBuildingTree(data);
    printBuildings(svgFile, buildingTree, getRootKDTree(buildingTree));

    kdTree personTree = getPersonTree(data);
    printPeople(svgFile, personTree, getRootKDTree(personTree));

    listT meteorList = getMeteorList(data);
    listPosT aux = getFirstElementList(meteorList);
    while (aux) {
        circleT circle = meteorGetCircle(getElementList(meteorList, aux));
        addCircleToSVG(svgFile, circle);

        aux = getNextElementList(meteorList, aux);
    }
   

    free(output);
    fclose(qryFile);
    fclose(qryTXT);
    finishSVG(svgFile);

}