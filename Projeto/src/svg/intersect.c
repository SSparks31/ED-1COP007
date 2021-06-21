#include "./intersect.h"

#include "../helper/mathHelp.h"

#include <stdio.h>


int llIntersect(lineT lineA, lineT lineB) {
    if (!lineA || !lineB) {
        return -1;
    }

    double x1A = stringToDouble(getX1Line(lineA)); // x1
    double y1A = stringToDouble(getY1Line(lineA)); // y1
    double x2A = stringToDouble(getX2Line(lineA)); // x2
    double y2A = stringToDouble(getY2Line(lineA)); // y2

    double x1B = stringToDouble(getX1Line(lineB)); // x3
    double y1B = stringToDouble(getY1Line(lineB)); // y3
    double x2B = stringToDouble(getX2Line(lineB)); // x4
    double y2B = stringToDouble(getY2Line(lineB)); // y4

    double uA = ((x2B - x1B) * (y1A - y1B) - (y2B - y1B) * (x1A - x1B)) / ((y2B - y1B) * (x2A - x1A) - (x2B - x1B) * (y2A - y1A));

    if (uA < 0 || uA > 1) {
        return 0;
    }

    double uB = ((x2A - x1A) * (y1A - y1B) - (y2A - y1A) * (x1A - x1B)) / ((y2B - y1B) * (x2A - x1A) - (x2B - x1B) * (y2A - y1A));

    return uB >=0 && uB <= 1;

}

int lrIntersect(lineT lineA, rectT rectB) {
    return rlIntersect(rectB, lineA);
}

int rrIntersect(rectT rectA, rectT rectB) {
    if (!rectA || !rectB) {
        return -1;
    }

    double x1A = stringToDouble(getXRect(rectA));
    double x2A = x1A + stringToDouble(getWidthRect(rectA));
    double x1B = stringToDouble(getXRect(rectB));
    double x2B = x1B + stringToDouble(getWidthRect(rectB));

    double x1Max = dmax(x1A, x1B);
    double x2Min = dmin(x2A, x2B);

    if (x2Min > x1Max) {
        return 0;
    }

    double y1A = stringToDouble(getYRect(rectA));
    double y2A = y1A + stringToDouble(getHeightRect(rectA));
    double y1B = stringToDouble(getYRect(rectB));
    double y2B = y1B + stringToDouble(getHeightRect(rectB));

    double y1Max = dmax(y1A, y1B);
    double y2Min = dmin(y2A, y2B);

    return y2Min <= y1Max;
}

int rlIntersect(rectT rectA, lineT lineB) {
    double x1A = stringToDouble(getXRect(rectA));
    double x2A = x1A + stringToDouble(getWidthRect(rectA));
    double y1A = stringToDouble(getYRect(rectA));
    double y2A = y1A + stringToDouble(getHeightRect(rectA));
    
    char coordinates[999];
    sprintf(coordinates, "%lf %lf %lf %lf", x1A, y1A, x1A, y2A);
    lineT edgeA = createLine("red", coordinates);

    sprintf(coordinates, "%lf %lf %lf %lf", x2A, y1A, x2A, y2A);
    lineT edgeB = createLine("blue", coordinates);

    sprintf(coordinates, "%lf %lf %lf %lf", x1A, y1A, x2A, y1A);
    lineT edgeC = createLine("green", coordinates);

    sprintf(coordinates, "%lf %lf %lf %lf", x1A, y2A, x2A, y2A);
    lineT edgeD = createLine("yellow", coordinates);

    #include <stdio.h>
    #include "./svg.h"
    FILE* svg = startSVG("./", "edge.svg");
    addLineToSVG(svg, edgeA);
    addLineToSVG(svg, edgeB);
    addLineToSVG(svg, edgeC);
    addLineToSVG(svg, edgeD);
    finishSVG(svg);

    int intersections = 0;
    intersections += llIntersect(lineB, edgeA);
    intersections += llIntersect(lineB, edgeB);
    intersections += llIntersect(lineB, edgeC);
    intersections += llIntersect(lineB, edgeD);

    destroyLine(edgeA);
    destroyLine(edgeB);
    destroyLine(edgeC);
    destroyLine(edgeD);

    return intersections;
}
