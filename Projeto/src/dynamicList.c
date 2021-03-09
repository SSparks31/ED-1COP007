#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct dListPos {
    listElemT elem;
    struct dListPos* next;
    struct dListPos* prev;
};

struct dList {
    struct dListPos* first;
    struct dListPos* last;

    int curLength;
    int maxLength;

    size_t accessCount;
};

listT createList(int maxElem) {
    if (maxElem <= 0) {
        return NULL;
    }

    struct dList* dList = malloc(sizeof(struct dList));
    if (!dList) {
        return NULL;
    }

    dList->first = NULL;
    dList->last = NULL;
    
    dList->curLength = 0;
    dList->maxLength = maxElem;

    dList->accessCount = 0;

    return dList;
}

int isEmptyList(listT list) {
    if (!list) {
        return -1;
    }

    struct dList* dList = list;
    return dList->curLength == 0;
}

int lengthList(listT list) {
    if (!list) {
        return -1;
    }

    struct dList* dList = list;
    return dList->curLength;
}

int isFullList(listT list) {
    if (!list) {
        return -1;
    }
    
    struct dList* dList = list;
    return dList->curLength == dList->maxLength;
}

listPosT getFirstElementList(listT list) {
    if (!list || isEmptyList(list)) {
        return NULL;
    }

    struct dList* dList = list;
    
    dList->accessCount++;

    return dList->first;
}

listPosT getNextElementList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    struct dList* dList = list;
    struct dListPos* dPos = pos;

    dList->accessCount++;

    return dPos->next;
}

listPosT getLastElementList(listT list) {
    if (!list || isEmptyList(list)) {
        return NULL;
    }

    struct dList* dList = list;

    return dList->last;
}

listPosT getPrevElementList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    struct dListPos* dPos = pos;

    return dPos->prev;
}

listPosT appendList(listT list, listElemT elem) {
    if (!list || isFullList(list) || !elem) {
        return NULL;
    }
    
    struct dList* dList = list;

    struct dListPos* newPos = malloc(sizeof(struct dListPos));
    if (!newPos) {
        return NULL;
    }

    struct dListPos* lastPos = getLastElementList(list);

    if (lastPos) {
        lastPos->next = newPos;
        newPos->prev = lastPos;
    } else {
        dList->first = newPos;
    }
    dList->last = newPos;

    newPos->elem = elem;
    newPos->next = NULL;

    dList->curLength++;

    return newPos;
}

listPosT insertBeforeList(listT list, listPosT pos, listElemT elem) {
    if (!list || isFullList(list) || !pos || !elem) {
        return NULL;
    }
    
    struct dList* dList = list;
    struct dListPos* dPos = pos;
    struct dListPos* firstPos = getFirstElementList(list);
    
    struct dListPos* newPos = malloc(sizeof(struct dListPos));
    if (!newPos) {
        return NULL;
    }

    if (dPos == firstPos) {
        dList->first = newPos;
    } else {
        dPos->prev->next = newPos;
    }
    
    newPos->prev = dPos->prev;
    newPos->next = dPos;
    dPos->prev = newPos;

    newPos->elem = elem;
    dList->curLength++;

    return newPos;
}

listPosT insertAfterList(listT list, listPosT pos, listElemT elem) {
    if (!list || isFullList(list) || !pos || !elem) {
        return NULL;
    }
    
    struct dList* dList = list;
    struct dListPos* dPos = pos;
    struct dListPos* lastPos = getLastElementList(list);
    
    struct dListPos* newPos = malloc(sizeof(struct dListPos));
    if (!newPos) {
        return NULL;
    }

    if (dPos == lastPos) {
        return appendList(list, elem);
    }
    
    newPos->prev = dPos;
    newPos->next = dPos->next;
    dPos->next->prev = newPos;
    dPos->next = newPos;

    newPos->elem = elem;
    dList->curLength++;

    return newPos;
}

listElemT removeList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    struct dList* dList = list;
    struct dListPos* dPos = pos;
    
    struct dListPos* prevPos = getPrevElementList(list, pos); 
    struct dListPos* nextPos = getNextElementList(list, pos);

    if (prevPos) {
        prevPos->next = nextPos;
    } else {
        dList->first = nextPos;
    }

    if (nextPos) {
        nextPos->prev = prevPos;
    } else {
        dList->last = prevPos;
    }
    
    listElemT elem = getElementList(list, pos);
    free(pos);

    dList->curLength--;

    return elem;
}


listElemT getElementList(listT list, listPosT pos) {
    if (!list || !pos) {
        return NULL;
    }

    struct dListPos* dPos = pos;
    return dPos->elem;
}

void destroyList(listT list) {
    if (!list) {
        return;
    }

    if (!isEmptyList(list)) {
        printf("\n------------\n");
        printf("ATENCAO:\nO desalocamento de elementos da lista nao e realizado automaticamente; caso seja necessario, modifique seu programa para realizar a remocao e desalocamento.\n");
    }

    struct dList* dList = list;
    
    while (!isEmptyList(list)) {
        removeList(list, getFirstElementList(list));
    }

    free(dList);
}