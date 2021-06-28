#ifndef LIB_PROGRBUILDING_H
#define LIB_PROGRBUILDING_H

#include "../svg/rect.h"

typedef struct building* Building;

Building createBuilding(rectT rect);

rectT buildingGetRect(Building building);

int buildingGetPeopleInside(Building building);

void buildingAddPerson(Building building);

void demolishBuilding(Building building);

#endif