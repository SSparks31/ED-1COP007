#include "bibliotecas.h"
#include "listaDIN.h"

/*===============================*/

/*LISTA DUPLAMENTE ENCADEADA*/

typedef struct dados {
    // double x, y, largura, altura;
    // char id[100], contorno[100], preenchimento[100];
    // bool marcadoTP;
    struct dados* next;
    struct dados* prev;
    void* elemento;
} dados;

typedef struct list {
    dados* head;
    dados* end;
    int size;
} list;

/*===============================*/

lista createList() {
    list* newList = malloc(sizeof(list));
    newList->head = NULL;
    newList->end = NULL;
    newList->size = 0;
    return newList;
}

celula insert(lista sequence, item elemento){
    list* listaAux = sequence;
    dados* pontAux = malloc(sizeof(dados));
    pontAux->elemento = elemento;
    if(listaAux->size == 0){
        pontAux->next = NULL;
        pontAux->prev = NULL;
        listaAux->head = pontAux;
        listaAux->end = pontAux;
        
    }else{
        pontAux->next = NULL;
        listaAux->end->next = pontAux;
        pontAux->prev= listaAux->end;
        listaAux->end = pontAux;
    }
    listaAux->size++;
}

int getSize(lista sequence){
    list* listAux = sequence;

    return listAux->size;
}

celula getHead(lista sequence){
    list* listAux = sequence;
    return listAux->head;
}

celula getNext(celula current){
    dados* aux = current; 
    return aux->next;
}

celula getPrevious(celula current){
    dados* aux = current;
    return aux->prev;
}

item getItem(celula current){
    dados* aux = current;
    return aux->elemento;
}

// void removeCell(listaDupla sequence, int index) {
//     list* listAux = sequence;
//     dados* aux1;
//     dados* aux2;

//     if (listAux->size == 1) {
//         aux1 = atPos(listAux, 0);
//         listAux->head = NULL;
//         listAux->end = NULL;
//         free(aux1);
//         listAux->size--;
//         tamanhoLista--;

//     } else if (index == listAux->size - 1) {
//         aux1 = atPos(listAux, index - 1);
//         aux2 = atPos(listAux, index);
//         free(aux2);
//         aux1->next = NULL;
//         listAux->size--;
//         tamanhoLista--;
//     } else if (index == 0) {
//         aux1 = atPos(listAux, 0);
//         listAux->head = listAux->head->next;
//         listAux->end = NULL;
//         free(aux1);
//         listAux->size--;
//         tamanhoLista--;
//     } else if (index > listAux->size) {
//         puts("Erro!");
//         return;
//     } else if (index < 0) {
//         puts("index invalido");
//         return;
//     } else {
//         aux1 = atPos(listAux, index - 1);
//         aux2 = atPos(listAux, index);
//         aux1->next = aux2->next;
//         aux2->next->prev = aux1;
//         free(aux2);
//         listAux->size--;
//         tamanhoLista--;
//     }
//     numOfRect--;
// }

// void printList(listaDupla sequence) {
//     list* listAux = sequence;
//     dados* aux = listAux->head;
//     if (!listAux->size) {
//         puts("Nao ha elementos na lista.");
//         return;
//     }
//     puts("---------------------------------");
//     for (int i = 0; i < listAux->size; i++) {
//         printf("Retangulo %d dados:\n", i + 1);
//         printf("x = %.3lf\ny = %.3lf\nlargura = %.3lf\naltura = %.3lf\nid = %s\ncontorno = %s\npreenchimento = %s\n", aux->x, aux->y, aux->largura, aux->altura, aux->id, aux->contorno, aux->preenchimento);
//         aux = aux->next;
//         visitas++;
//         puts("---------------------------------");
//     }
// }

// void freeList(listaDupla sequence) {
//     int a = 0;
//     list* listAux = sequence;
//     dados* aux = listAux->head;
//     while (listAux->head != NULL) {
//         aux = listAux->head;
//         listAux->head = listAux->head->next;
//         free(aux);
//         a++;
//     }
// #ifdef DEBUG
//     if (a == listAux->size) {
//         puts("Lista liberada com sucesso");
//     } else {
//         puts("Ocorreu algum erro.");
//     }
// #endif
//     free(sequence);
// }

// listaDupla atPos(listaDupla sequence, int pos) {
//     list* listAux = sequence;
//     dados* aux = listAux->head;
//     for (int i = 0; i < pos; i++) {
//         aux = aux->next;
//         visitas++;
//     }
//     return aux;
// }