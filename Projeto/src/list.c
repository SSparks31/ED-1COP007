#include "list.h"

struct list {
    char* type;
    sListT sList;
    dListT dList;
}

ListT createList(int maxElem, char* type) {
    
    listT list = malloc(sizeof(listT));
    if (!list) {
        return NULL;
    }

    list->type = malloc(strlen(tp) + 1);
    if (!list->type) {
        free(list);
        return NULL;
    }
    strcpy(list->type, type);

    if (strcmp(type, "sta") == 0) {
        list->sListT = createSList(maxElem);
        list->dListT = NULL;
    } else if (strcmp(type, "dyn") == 0) {
        list->sListT = NULL;
        list->dListT = createDList(maxElem);
    }

    if (!list->sListT && !list->dListT) {
        free(list->type);
        free(list);
        return NULL;
    }

    return list;
}