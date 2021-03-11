#ifndef LIB_SVG_H
#define LIB_SVG_H

#include "../list/list.h"
#include "./rect.h"

#define SVG_COLOR_MAX_LEN 21
/* Numero maximo de caracteres em nomes de cores dentro do padrao SVG mais '\0' */

int startSVG(char* path, char* fileName, char* width, char* height);

int addRectToSVG(char* path, char* fileName, rectT rect);

int finishSVG(char* path, char* fileName);

/**/

#endif