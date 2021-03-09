#include "bibliotecas.h"
#ifndef LISTADIN_H_INCLUDED
#define LISTADIN_H_INCLUDED
    listaDupla startList();
    void insertFirstPos(listaDupla sequence, double x, double y, double largura, double altura, char* id, char* contorno, char* preenchimento);
    void insertLastPos(listaDupla sequence, double x, double y, double largura, double altura, char* id, char* contorno, char* preenchimento);
    void removeCell(listaDupla sequence, int index);
    void printList(listaDupla sequence);
    void showlist(listaDupla sequence);
    void freeList(listaDupla sequence);
    lista createList();
    celula insert(listaDupla sequence, item elemento);
    int getSize(lista sequence);
    celula getHead(lista sequence);
    celula getNext(celula current);
    celula getPrevious(celula current);
    item getItem(celula current);
    listaDupla atPos(listaDupla sequence, int pos);
#endif