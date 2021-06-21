#ifndef LIB_SVGINTERSECT_H
#define LIB_SVGINTERSECT_H

#include "./rect.h"
#include "./line.h"

int llIntersect(lineT lineA, lineT lineB);
int lrIntersect(lineT lineA, rectT rectB);

int rrIntersect(rectT rectA, rectT rectB);
int rlIntersect(rectT rectA, lineT lineB);


/**/
#endif