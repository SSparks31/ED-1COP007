#ifndef LIB_PROGRDATA_H
#define LIB_PROGRDATA_H

/* Programa de analise de arquivos .geo, contendo informacoes de diversos retangulos, e .qry, contendo pesquisas sobre os retangulos */

#include "../tree/binaryTree.h"
#include "../tree/kdTree.h"

typedef struct progrData* progrData;

progrData createData(char* BED, char* BSD, char* geoName, char* qryName);

char* getBED(progrData data);

char* getBSD(progrData data);

char* getGeoName(progrData data);

char* getQryName(progrData data);

char* getRectBorder(progrData data);

void  setRectBorder(progrData data, char* args);

char* getRectFill(progrData data);

void  setRectFill(progrData data, char* args);

char* getCircleBorder(progrData data);

void  setCircleBorder(progrData data, char* args);

char* getCircleFill(progrData data);

void  setCircleFill(progrData data, char* args);

kdTree getRectTree(progrData data);

kdTree getCircleTree(progrData data);

#endif