#ifndef LIB_CIRCLE_H
#define LIB_CIRCLE_H

typedef struct circle* circleT;

circleT createCircle(char* borderColor, char* fillColor, char* coordinates);

char* getBorderColorCircle(circleT circle);

void  setBorderColorCircle(circleT circle, char* borderColor);

char* getFillColorCircle(circleT circle);

void  setFillColorCircle(circleT circle, char* fillColor);

char* getXCenterCircle(circleT circle);

void  setXCenterCircle(circleT circle, char* xCenter);

char* getYCenterCircle(circleT circle);

void  setYCenterCircle(circleT circle, char* yCenter);

char* getRadiusCircle(circleT circle);

void  setRadiusCircle(circleT circle, char* radius);

void  setCoordinatesCircle(circleT circle, char* coordinates);

void  destroyCircle(circleT circle);

#endif