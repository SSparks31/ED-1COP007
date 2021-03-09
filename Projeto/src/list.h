#ifndef LIB_LIST_H
#define LIB_LIST_H


typedef void* listT;
typedef void* listPosT;
typedef void* listElemT;

listT createList(int maxElem);

int isEmptyList(listT list);

int lengthList(listT list);

int isFullList(listT list);

listPosT getFirstElementList(listT list);

listPosT getNextElementList(listT list, listPosT pos);

listPosT getLastElementList(listT list);

listPosT getPrevElementList(listT list, listPosT pos);

listPosT appendList(listT list, listElemT elem);

listPosT insertBeforeList(listT list, listPosT pos, listElemT elem);

listPosT insertAfterList(listT list, listPosT pos, listElemT elem);

listElemT removeList(listT list, listPosT pos);

listElemT getElementList(listT list, listPosT pos);

void destroyList(listT list);

/**/
#endif