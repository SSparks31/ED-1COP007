#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct listPos {
    listElemT elem;
    listPosT next;
    listPosT prev;
};

struct list {
    listPosT first;
    listPosT last;

    int curLength;
    int maxLength;

    size_t accessCount;
};

listT createList(int maxElem) {
    if (maxElem <= 0) {
        return NULL;
    }

    listT list = malloc(sizeof(struct list));
    if (!list) {
        return NULL;
    }

    list->first = NULL;
    list->last = NULL;
    
    list->curLength = 0;
    list->maxLength = maxElem;

    list->accessCount = 0;

    return list;
}

int isEmptyList(listT list) {
    if (!list) {
        return -1;
    }

    return list->curLength == 0;
}

int lengthList(listT list) {
    if (!list) {
        return -1;
    }

    return list->curLength;
}

int isFullList(listT list) {
    if (!list) {
        return -1;
    }
    
    return list->curLength == list->maxLength;
}

listPosT getFirstElementList(listT list) {
    if (!list || isEmptyList(list)) {
        return NULL;
    }

    list->accessCount++;

    return list->first;
}

listPosT getNextElementList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    list->accessCount++;

    return pos->next;
}

listPosT getLastElementList(listT list) {
    if (!list || isEmptyList(list)) {
        return NULL;
    }

    list->accessCount++;

    return list->last;
}

listPosT getPrevElementList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    list->accessCount++;

    return pos->prev;
}

listPosT appendList(listT list, listElemT elem) {
    if (!list || isFullList(list) || !elem) {
        return NULL;
    }
    
    listPosT newPos = malloc(sizeof(struct listPos));
    if (!newPos) {
        return NULL;
    }

    listPosT lastPos = getLastElementList(list);

    if (lastPos) {
        lastPos->next = newPos;
        newPos->prev = lastPos;
    } else {
        list->first = newPos;
        newPos->prev = NULL;
    }
    list->last = newPos;

    newPos->elem = elem;
    newPos->next = NULL;

    list->curLength++;

    return newPos;
}

listPosT insertBeforeList(listT list, listPosT pos, listElemT elem) {
    if (!list || isFullList(list) || !pos || !elem) {
        return NULL;
    }
    
    listPosT newPos = malloc(sizeof(struct listPos));
    if (!newPos) {
        return NULL;
    }

    listPosT firstPos = getFirstElementList(list);    
    if (pos == firstPos) {
        list->first = newPos;
    } else {
        pos->prev->next = newPos;
    }
    
    newPos->prev = pos->prev;
    newPos->next = pos;
    pos->prev = newPos;

    newPos->elem = elem;
    list->curLength++;

    return newPos;
}

listPosT insertAfterList(listT list, listPosT pos, listElemT elem) {
    if (!list || isFullList(list) || !pos || !elem) {
        return NULL;
    }
    
    
    listPosT lastPos = getLastElementList(list);
    if (pos == lastPos) {
        return appendList(list, elem);
    }
    
    listPosT newPos = malloc(sizeof(struct listPos));
    if (!newPos) {
        return NULL;
    }

    newPos->prev = pos;
    newPos->next = pos->next;
    pos->next->prev = newPos;
    pos->next = newPos;

    newPos->elem = elem;
    list->curLength++;

    return newPos;
}

listElemT removeList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }
   
    listPosT prevPos = getPrevElementList(list, pos); 
    listPosT nextPos = getNextElementList(list, pos);

    if (prevPos) {
        prevPos->next = nextPos;
    } else {
        list->first = nextPos;
    }

    if (nextPos) {
        nextPos->prev = prevPos;
    } else {
        list->last = prevPos;
    }
    
    listElemT elem = getElementList(list, pos);
    free(pos);

    list->curLength--;

    return elem;
}


listElemT getElementList(listT list, listPosT pos) {
    if (!list || !pos) {
        return NULL;
    }

    return pos->elem;
}

void destroyList(listT list) {
    if (!list) {
        return;
    }

    if (!isEmptyList(list)) {
        printf("\n------------\n");
        printf("ATENCAO:\nO desalocamento de elementos da lista nao e realizado automaticamente; caso seja necessario, modifique seu programa para realizar a remocao e desalocamento.\n");
    }

    while (!isEmptyList(list)) {
        removeList(list, getFirstElementList(list));
    }

    free(list);
}