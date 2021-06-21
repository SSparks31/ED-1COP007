#include "qry.h"

#include "../helper/pathHelp.h"
#include "../helper/mathHelp.h"
#include "../helper/stringHelp.h"

#include "../svg/svg.h"
#include "../svg/line.h"
#include "../svg/intersect.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct meteor {
    circleT circle;
    double intensity;
}* Meteor;

Meteor createMeteor(circleT circle, double intensity) {
    if (!circle || intensity <= 0) {
        return NULL;
    }

    Meteor meteor = malloc(sizeof(struct meteor));
    if (!meteor) {
        return NULL;
    }

    meteor->circle = circle;
    meteor->intensity = intensity;
    
    return meteor;
}

circleT meteorGetCircle(Meteor meteor) {
    if (!meteor) {
        return NULL;
    }

    return meteor->circle;
}

double meteorGetIntensity(Meteor meteor) {
    if (!meteor) {
        return -1;
    }

    return meteor->intensity;
}

void destroyMeteor(Meteor meteor) {
    if (!meteor) {
        return;
    }

    circleT circle = meteorGetCircle(meteor);
    destroyCircle(circle);

    free(meteor);
}

double getTotalExposition(kdTree buildingTree, kdNode buildingNode, lineT line) {
    if (!buildingNode) {
        return 0;
    }

    building build = getElemInKDNode(buildingTree, buildingNode);
    rectT rect = buildingGetRect(build);
    int intersections = rlIntersect(rect, line);


    kdNode left = getKDNodeLeftChild(buildingTree, buildingNode);
    kdNode right = getKDNodeRightChild(buildingTree, buildingNode);

    return dpow(0.8, intersections) * getTotalExposition(buildingTree, left, line) * getTotalExposition(buildingTree, right, line);
}

void exposePeople(kdTree buildingTree, kdTree personTree, kdNode personNode, Meteor meteor, FILE* qryTXT) {
    if (!personNode) {
        return;
    }

    person guy = getElemInKDNode(personTree, personNode);
    circleT personCircle = personGetCircle(guy);

    char* personX = getXCenterCircle(personCircle);
    char* personY = getYCenterCircle(personCircle);

    circleT meteorCircle = meteorGetCircle(meteor);

    char* meteorX = getXCenterCircle(meteorCircle);
    char* meteorY = getYCenterCircle(meteorCircle);

    char coordinates[90];
    sprintf(coordinates, "%s %s %s %s", personX, personY, meteorX, meteorY);
    lineT line = createLine("red", coordinates);

    personAddRadiation(guy, getTotalExposition(buildingTree, getRootKDTree(buildingTree), line) * meteorGetIntensity(meteor));
    printf("%lf\n", personGetRadiation(guy));


    double radiation = personGetRadiation(guy);

    if (radiation < 25) {
        setFillColorCircle(personCircle, "cyan");        
    } else if (radiation < 50) {
        setFillColorCircle(personCircle, "limegreen");
    } else if (radiation < 150) {
        setFillColorCircle(personCircle, "magenta");
    } else if (radiation < 250) {
        setFillColorCircle(personCircle, "blue");
    } else if (radiation < 600) {
        setFillColorCircle(personCircle, "purple");
    } else if (radiation < 1000) {
        if (!personIsDead(guy)) {
            printf("%s - Morte iminente\n", getIDCircle(personCircle));
        }
        setFillColorCircle(personCircle, "darkblue");
    } else {
        if (!personIsDead(guy)) {
            printf("%s - Morte imediata\n", getIDCircle(personCircle));
        }
        setFillColorCircle(personCircle, "black");
        killPerson(guy);
    }

    kdNode left = getKDNodeLeftChild(personTree, personNode);
    kdNode right = getKDNodeRightChild(personTree, personNode);

    exposePeople(buildingTree, personTree, left, meteor, qryTXT);
    exposePeople(buildingTree, personTree, right, meteor, qryTXT);
}

void qryIm(progrData data, char* args, FILE* svgFile, FILE* qryTXT) {
    char* x = args;
    char* y = splitString(x, ' ');
    
    double intensity = stringToDouble(splitString(y, ' '));

    char coordinates[50];
    sprintf(coordinates, "%s %s %lf", x, y, intensity);

    circleT circle = createCircle("grey", "grey", "0.8", "meteor", coordinates);

    Meteor meteor = createMeteor(circle, intensity);

    kdTree buildingTree = getBuildingTree(data);
    kdTree personTree = getPersonTree(data);

    exposePeople(buildingTree, personTree, getRootKDTree(personTree), meteor, qryTXT);

    addCircleToSVG(svgFile, circle);

    destroyMeteor(meteor);
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
        return;
    }

    char* svgName = concatFileSuffix(outName, "svg");
    FILE* svgFile = startSVG(outputPath, svgName);
    free(svgName);
    free(outName);
    if (!svgFile) {
        fclose(qryTXT);
        return;
    }

    fprintf(qryTXT, "Gregorio Rodrigues Favero\n\t202000560114\n===\n");

    char command[999];

    while (!isEmpty(fgetLine(qryFile, command, 999))) {
        
        char* args = splitString(command, ' ');
        fprintf(qryTXT, "%s\n", command);
        
        if (command[0] == 'i') {
            qryIm(data, args, svgFile, qryTXT);
        } 

        fprintf(qryTXT, "===\n");
    }

    fclose(qryFile);

}