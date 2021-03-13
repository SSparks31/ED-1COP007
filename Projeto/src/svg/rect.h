#ifndef LIB_RECT_H
#define LIB_RECT_H

typedef struct rect* rectT;

rectT createRect(char* borderColor, char* fillColor, char* ID, char* coordinates);

char* getIDRect(rectT rect);

char* getBorderColorRect(rectT rect);

void  setBorderColorRect(rectT rect, char* borderColor);

char* getFillColorRect(rectT rect);

void  setFillColorRect(rectT rect, char* fillColor);

char* getXRect(rectT rect);

void  setXRect(rectT rect, char* x);

char* getYRect(rectT rect);

void  setYRect(rectT rect, char* y);

char* getWidthRect(rectT rect);

void  setWidthRect(rectT rect, char* w);

char* getHeightRect(rectT rect);

void  setHeightRect(rectT rect, char* h);

void  setCoordinatesRect(rectT rect, char* coordinates);

void  destroyRect(rectT rect);

/**/

#endif