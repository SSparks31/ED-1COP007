#ifndef LIB_SVG_H
#define LIB_SVG_H

#include <stdio.h>

#include "./rect.h"

FILE* startSVG(char* path, char* fileName);

int addRectToSVG(FILE* svgFile, rectT rect);

int finishSVG(FILE* svgFile);

/**/

#endif