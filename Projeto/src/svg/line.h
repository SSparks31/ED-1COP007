#ifndef LIB_RECT_H
#define LIB_RECT_H

typedef struct line* lineT;

lineT createLine(char* color, char* coordinates);

char* getColorLine(lineT line);

void  setColorLine(lineT line, char* color);

char* getX1Line(lineT line);

void  setX1Line(lineT line, char* x1);

char* getY1Line(lineT line);

void  setY1Line(lineT line, char* y1);

char* getX2Line(lineT line);

void  setX2Line(lineT line, char* x2);

char* getY2Line(lineT line);

void  setY2Line(lineT line, char* h);

void  setCoordinatesLine(lineT line, char* coordinates);

void  destroyLine(lineT line);

/**/

#endif