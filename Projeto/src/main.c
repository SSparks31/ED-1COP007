#include <stdio.h>
#include <stdlib.h>

#include "./geo/geo.h"
#include "./list/list.h"
#include "./svg/rect.h"

void printList(listT list) {
    listPosT aux = getFirstElementList(list);

    while (aux) {
        printf("[%d] ", *((int*) getElementList(list, aux)));
        aux = getNextElementList(list, aux);
    }
    printf("\n");
}

int main() {

    char* geoPath = "./a1.geo";

    listT geo = geoParser(geoPath);

    listPosT aux = getFirstElementList(geo);

    rectT rect = getElementList(geo, aux);

    while (aux) {
        printf("%s\n", getIDRect(rect));
        aux = getNextElementList(geo, aux);
        rect = getElementList(geo, aux);
    }

    while (!isEmptyList(geo)) {
        destroyRect(removeList(geo, getFirstElementList(geo)));
    }

    destroyList(geo);

    return 0;
}