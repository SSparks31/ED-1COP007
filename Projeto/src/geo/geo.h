#ifndef LIB_GEO_H
#define LIB_GEO_H 

/* Modulo voltado a interacao com arquivos .geo */

#include "../list/list.h"

listT geoParser(char* geoPath);
/* Dado um caminho pra .geo valido `geoPath`, le comandos e executa as respectivas acoes */
/* Retorna lista contendo todos os retangulos */

#endif