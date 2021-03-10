#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct listPos {
    listElemT elem;
    int next;
};

struct list {
    listPosT list;

    int curLength;
    int maxLength;

    int firstElem;
    int nextPos;

    size_t accessCount;
};

listT createList(int maxElem) {
    if (maxElem <= 0) {
        return NULL;
    }

    listT sList = malloc(sizeof(struct list));
    if (!sList) {
        return NULL;
    }

    sList->list = malloc(sizeof(struct listPos) * maxElem);
    if (!sList->list) {
        free(sList);
        return NULL;
    }
    
    int i;
    for (i = 0; i < maxElem; ++i) {
        sList->list[i].elem = NULL;
        sList->list[i].next = i + 1;
    }
    sList->list[i - 1].next = -1;

    sList->curLength = 0;
    sList->maxLength = maxElem;

    sList->firstElem = -1;
    sList->nextPos = 0;

    sList->accessCount = maxElem;

    return sList;
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

    return list->list + list->firstElem;
}

listPosT getNextElementList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    if (pos->next == -1) {
        return NULL;
    }

    list->accessCount++;

    return list->list + pos->next;
}

listPosT getLastElementList(listT list) {
    if (!list || isEmptyList(list)) {
        return NULL;
    }

    listPosT aux = getFirstElementList(list);

    while (aux->next != -1) {
        aux = getNextElementList(list, aux);
    }

    return aux;
}

listPosT getPrevElementList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    listPosT aux = getFirstElementList(list);
    listPosT prev = NULL;

    while (aux != pos) {
        prev = aux;
        aux = getNextElementList(list, aux);
    }

    return prev;
}

listPosT appendList(listT list, listElemT elem) {
    if (!list || isFullList(list) || !elem) {
        return NULL;
    }
    
    listPosT lastPos = getLastElementList(list);
    listPosT nextPos = list->list + list->nextPos;

    if (lastPos) {
        lastPos->next = list->nextPos;
    } else {
        list->firstElem = list->nextPos;
    }
    list->nextPos = nextPos->next;

    nextPos->elem = elem;
    nextPos->next = -1;

    list->curLength++;

    return nextPos;
}

listPosT insertBeforeList(listT list, listPosT pos, listElemT elem) {
    if (!list || isFullList(list) || !pos || !elem) {
        return NULL;
    }
    
    listPosT prevPos = getPrevElementList(list, pos);
    listPosT newPos = list->list + list->nextPos;

    if (!prevPos) {
        newPos->next = list->firstElem;
        list->firstElem = list->nextPos;
    } else {
        newPos->next = prevPos->next;
        prevPos->next = list->nextPos;
    }

    newPos->elem = elem;
    list->curLength++;

    return newPos;
}

listPosT insertAfterList(listT list, listPosT pos, listElemT elem) {
    if (!list || isFullList(list) || !pos || !elem) {
        return NULL;
    }

    listPosT nextPos = getNextElementList(list, pos);

    if (!nextPos) {
        return appendList(list, elem);
    }

    listPosT newPos = list->list + list->nextPos;

    newPos->next = pos->next;
    pos->next = list->nextPos;
    newPos->elem = elem;
    list->curLength++;

    return newPos;
}

listElemT removeList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    listPosT aux = getFirstElementList(list);

    listPosT prevPos = getPrevElementList(list, pos); 
    if (prevPos) {
        list->nextPos = prevPos->next;
        prevPos->next = pos->next;
    } else {
        list->nextPos = list->firstElem;
        list->firstElem = pos->next;
    }
    
    list->curLength--;

    return pos->elem;
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

    free(list->list);
    free(list);
}