#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct sListPos {
    listElemT elem;
    int next;
};

struct sList {
    struct sListPos* list;

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

    struct sList* sList = malloc(sizeof(struct sList));
    if (!sList) {
        return NULL;
    }

    sList->list = malloc(sizeof(struct sListPos) * maxElem);
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

    struct sList* sList = list;
    return sList->curLength == 0;
}

int lengthList(listT list) {
    if (!list) {
        return -1;
    }

    struct sList* sList = list;
    return sList->curLength;
}

int isFullList(listT list) {
    if (!list) {
        return -1;
    }
    
    struct sList* sList = list;
    return sList->curLength == sList->maxLength;
}

listPosT getFirstElementList(listT list) {
    if (!list || isEmptyList(list)) {
        return NULL;
    }

    struct sList* sList = list;
    
    sList->accessCount++;

    return sList->list + sList->firstElem;
}

listPosT getNextElementList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    struct sList* sList = list;
    struct sListPos* sPos = pos;
    if (sPos->next == -1) {
        return NULL;
    }

    sList->accessCount++;

    return sList->list + sPos->next;
}

listPosT getLastElementList(listT list) {
    if (!list || isEmptyList(list)) {
        return NULL;
    }

    struct sList* sList = list;
    struct sListPos* aux = getFirstElementList(list);

    while (aux->next != -1) {
        aux = getNextElementList(list, aux);
    }

    return aux;
}

listPosT getPrevElementList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    struct sList* sList = list;
    struct sListPos* sPos = pos;
    struct sListPos* aux = getFirstElementList(list);
    struct sListPos* prev = NULL;

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
    
    struct sList* sList = list;
    struct sListPos* lastPos = getLastElementList(list);
    struct sListPos* nextPos = sList->list + sList->nextPos;

    if (lastPos) {
        lastPos->next = sList->nextPos;
    } else {
        sList->firstElem = sList->nextPos;
    }
    sList->nextPos = nextPos->next;

    nextPos->elem = elem;
    nextPos->next = -1;

    sList->curLength++;

    return nextPos;
}

listPosT insertBeforeList(listT list, listPosT pos, listElemT elem) {
    if (!list || isFullList(list) || !pos || !elem) {
        return NULL;
    }
    
    struct sList* sList = list;
    struct sListPos* sPos = pos;
    struct sListPos* prevPos = getPrevElementList(list, pos);
    struct sListPos* newPos = sList->list + sList->nextPos;

    if (!prevPos) {
        newPos->next = sList->firstElem;
        sList->firstElem = sList->nextPos;
    } else {
        newPos->next = prevPos->next;
        prevPos->next = sList->nextPos;
    }

    newPos->elem = elem;
    sList->curLength++;

    return newPos;
}

listPosT insertAfterList(listT list, listPosT pos, listElemT elem) {
    if (!list || isFullList(list) || !pos || !elem) {
        return NULL;
    }

    struct sList* sList = list;
    struct sListPos* sPos = pos;
    struct sListPos* nextPos = getNextElementList(list, pos);

    if (!nextPos) {
        return appendList(list, elem);
    }

    struct sListPos* newPos = sList->list + sList->nextPos;

    newPos->next = sPos->next;
    sPos->next = sList->nextPos;
    newPos->elem = elem;
    sList->curLength++;

    return newPos;
}

listElemT removeList(listT list, listPosT pos) {
    if (!list || isEmptyList(list) || !pos) {
        return NULL;
    }

    struct sList* sList = list;
    struct sListPos* sPos = pos;
    struct sListPos* aux = getFirstElementList(list);

    struct sListPos* prevPos = getPrevElementList(list, pos); 
    if (prevPos) {
        sList->nextPos = prevPos->next;
        prevPos->next = sPos->next;
    } else {
        sList->nextPos = sList->firstElem;
        sList->firstElem = sPos->next;
    }
    
    sList->curLength--;

    return sPos->elem;
}


listElemT getElementList(listT list, listPosT pos) {
    if (!list || !pos) {
        return NULL;
    }

    struct sListPos* sPos = pos;
    return sPos->elem;
}

void destroyList(listT list) {
    if (!list) {
        return;
    }

    if (!isEmptyList(list)) {
        printf("\n------------\n");
        printf("ATENCAO:\nO desalocamento de elementos da lista nao e realizado automaticamente; caso seja necessario, modifique seu programa para realizar a remocao e desalocamento.\n");
    }

    struct sList* sList = list;

    free(sList->list);
    free(sList);
}