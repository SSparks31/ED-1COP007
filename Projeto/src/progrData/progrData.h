#ifndef LIB_PROGRDATA_H
#define LIB_PROGRDATA_H

#include "../list/list.h"

typedef struct progrData* progrDataT;

progrDataT createProgrData(char* inputPath, char* outputPath, char* geoName, char* qryName, int collect);

char* getInputPathProgrData(progrDataT progrData);

char* getOutputPathProgrData(progrDataT progrData);

char* getGeoNameProgrData(progrDataT progrData);

char* getQryNameProgrData(progrDataT progrData);

listT getGeoListProgrData(progrDataT progrData);

void setGeoListProgrData(progrDataT progrData, listT list);

listT getQryListProgrData(progrDataT progrData);

void setQryListProgrData(progrDataT progrData, listT list);

int getCollectProgrData(progrDataT progrData);

void destroyProgrData(progrDataT progrData);

/**/

#endif