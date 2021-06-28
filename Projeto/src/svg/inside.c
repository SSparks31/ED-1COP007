#include "./inside.h"

#include "../helper/mathHelp.h"

#include "./rect.h"
#include "./circle.h"

#include <math.h>

int rrInside(rectT rectA, rectT rectB) {
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

int ccInside(circleT circleA, circleT circleB) {
    if (!circleA || !circleB) {
        return 0;
    }

    double xDistance = stringToDouble(getXCenterCircle(circleA)) - stringToDouble(getXCenterCircle(circleB));
    double yDistance = stringToDouble(getYCenterCircle(circleA)) - stringToDouble(getYCenterCircle(circleB));
    
    double radius = stringToDouble(getRadiusCircle(circleA));

    return fabs(dpow(xDistance, 2) + dpow(yDistance, 2) - dpow(radius, 2)) <= 0.001;    
}