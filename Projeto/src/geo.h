#ifndef LIB_GEO_H
#define LIB_GEO_H 

/* Modulo voltado a interacao com arquivos .geo */

#include "list.h"

#define SVG_COLOR_MAX_LEN 21
/* Numero maximo de caracteres em nomes de cores dentro do padrao SVG mais '\0' */

typedef struct rect* rectT;

listT geoParser(char* geoPath);
/* Dado um caminho pra .geo valido `geoPath`, le comandos e executa as respectivas acoes */
/* Retorna lista contendo todos os retangulos */

rectT createRect(char* borderColor, char* fillColor, char* command);

char* getIDRect(rectT rect);

char* getBorderColorRect(rectT rect);

char* getFillColorRect(rectT rect);

char* getXRect(rectT rect);

char* getYRect(rectT rect);

char* getWidthRect(rectT rect);

char* getHeightRect(rectT rect);

void destroyRect(rectT rect);

#endif