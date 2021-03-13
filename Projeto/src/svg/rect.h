#ifndef LIB_RECT_H
#define LIB_RECT_H

typedef struct rect* rectT;

rectT createRect(char* borderColor, char* fillColor, char* ID, char* coordinates);

char* getIDRect(rectT rect);

char* getBorderColorRect(rectT rect);

char* getFillColorRect(rectT rect);

void setFillColorRect(rectT rect, char* fillColor);

char* getXRect(rectT rect);

char* getYRect(rectT rect);

char* getWidthRect(rectT rect);

char* getHeightRect(rectT rect);

void destroyRect(rectT rect);

/**/

#endif