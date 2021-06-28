#include "./building.h"

#include <stdlib.h>

struct building {
    rectT rect;
    int peopleInside;
};

Building createBuilding(rectT rect) {
    if (!rect) {
        return NULL;
    }

    Building building = malloc(sizeof(struct building));
    if (!building) {
        return NULL;
    }

    building->rect = rect;
    building->peopleInside = 0;

    return building;
}

rectT buildingGetRect(Building building) {
    if (!building) {
        return NULL;
    }

    return building->rect;
}

int buildingGetPeopleInside(Building building) {
    if (!building) {
        return -1;
    }

    return building->peopleInside;
}

void buildingAddPerson(Building building) {
    if (!building) {
        return;
    }

    building->peopleInside++;
}

void demolishBuilding(Building building) {
    if (!building) {
        return;
    }

    rectT rect = buildingGetRect(building);
    destroyRect(rect);

    free(building);
}