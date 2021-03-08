#include "staticList.h"

#include <stdio.h>
#include <stdlib.h>

struct sListPos {
    sListItem elem;
    int next;
};

struct sList {
    sListPosT list;

    int maxLength;
    int curLength;

    int firstElem;
    int nextPos;

    size_t accessCount;
};

sListT createSList(int maxElem) {
    if (maxElem <= 0) {
        return NULL;
    }

    sListT sList = malloc(sizeof(struct sList));
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

    sList->accessCount = 0;

    return sList;
}

int isEmptySList(sListT sList) {
    if (!sList) {
        return -1;
    }

    return sList->curLength == 0;
}

int lengthSList(sListT sList) {
    if (!sList) {
        return -1;
    }

    return sList->curLength;
}

int isFullSList(sListT sList) {
    if (!sList) {
        return -1;
    }
    
    return sList->curLength == sList->maxLength;
}

sListPosT getFirstElementSList(sListT sList) {
    if (!sList || isEmptySList(sList)) {
        return NULL;
    }

    return sList->list + sList->firstElem;
}

sListPosT getNextElementSList(sListT sList, sListPosT pos) {
    if (!sList || isEmptySList(sList) || !pos) {
        return NULL;
    }
    if (pos->next == -1) {
        return NULL;
    }

    return sList->list + pos->next;
}

sListPosT getLastElementSList(sListT sList) {
    if (!sList || isEmptySList(sList)) {
        return NULL;
    }

    sListPosT aux = getFirstElementSList(sList);
    sList->accessCount++;

    while (aux->next != -1) {
        aux = getNextElementSList(sList, aux);
        sList->accessCount++;
    }

    return aux;
}

sListPosT getPrevElementSList(sListT sList, sListPosT pos) {
    if (!sList || isEmptySList(sList) || !pos) {
        return NULL;
    }

    sListPosT aux = getFirstElementSList(sList);
    sList->accessCount++;

    if (pos == aux) {
        return NULL;
    }

    while (aux && getNextElementSList(sList, aux) != pos) {
        aux = getNextElementSList(sList, aux);
        sList->accessCount++;
    }

    return aux;
}

sListPosT appendSList(sListT sList, sListItem elem) {
    if (!sList || isFullSList(sList) || !elem) {
        return NULL;
    }
    
    sListPosT lastPos = getLastElementSList(sList), nextPos = sList->list + sList->nextPos;

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

sListPosT insertBeforeSList(sListT sList, sListPosT pos, sListItem elem) {
    if (!sList || isFullSList(sList) || !pos || !elem) {
        return NULL;
    }
    
    sListPosT prevPos = getPrevElementSList(sList, pos), newPos = sList->list + sList->nextPos;
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

sListPosT insertAfterSList(sListT sList, sListPosT pos, sListItem elem) {
    if (!sList || isFullSList(sList) || !pos || !elem) {
        return NULL;
    }

    sListPosT nextPos = getNextElementSList(sList, pos);
    if (!nextPos) {
        return appendSList(sList, elem);
    }

    sListPosT newPos = sList->list + sList->nextPos;

    newPos->next = pos->next;
    pos->next = sList->nextPos;
    newPos->elem = elem;
    sList->curLength++;

    return newPos;
}

sListItem removeSList(sListT sList, sListPosT pos) {
    if (!sList || isEmptySList(sList) || !pos) {
        return NULL;
    }

    int posIndex;
    for (posIndex = 0; posIndex < lengthSList(sList); ++posIndex) {
        sList->accessCount++;
        if (sList->list + posIndex == pos) {
            break;
        }
    }

    sListPosT prevPos = getPrevElementSList(sList, pos); 
    if (prevPos) {
        prevPos->next = pos->next;
    } else {
        sList->firstElem = pos->next;
    }

    sList->nextPos = posIndex;
    
    sList->curLength--;

    return pos->elem;
}


sListItem getItemSList(sListT sList, sListPosT pos) {
    if (!sList || !pos) {
        return NULL;
    }

    return pos->elem;
}

void destroySList(sListT sList) {
    if (!sList) {
        return;
    }

    if (!isEmptySList(sList)) {
        printf("\n------------\n");
        printf("ATENCAO:\nO desalocamento de elementos da lista nao e realizado automaticamente; caso seja necessario, modifique seu programa para realizar a remocao e desalocamento.\n");
    }

    free(sList->list);
    free(sList);
}