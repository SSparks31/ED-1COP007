#ifndef LIB_SVG_H
#define LIB_SVG_H

#include <stdio.h>

#include "./rect.h"
#include "./line.h"
#include "./circle.h"

FILE* startSVG(char* path, char* fileName);

int addRectToSVG(FILE* svgFile, rectT rect);

int addDottedRectToSVG(FILE* svgFile, rectT rect);

int addLineToSVG(FILE* svgFile, lineT line);

int addDottedLineToSVG(FILE* svgFile, lineT line);

int addCircleToSVG(FILE* svgFile, circleT circle);

int addDottedCircleToSVG(FILE* svgFile, circleT circle);

int finishSVG(FILE* svgFile);

/**/

#endif