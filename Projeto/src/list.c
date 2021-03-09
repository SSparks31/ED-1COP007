#include "list.h"

struct list {
    char type;
    void* list;
}

ListT createList(int maxElem, char type) {
    
    listT list = malloc(sizeof(listT));
    if (!list) {
        return NULL;
    }

    list->type = type;

    if (type == 's') {
        list->list = createSList(maxElem);
    } else if (type == 'd'){
        list->l = NULL;
        list->l = createDList(maxElem);
    }

    if (!list->list) {
        free(list);
        return NULL;
    }

    return list;
}