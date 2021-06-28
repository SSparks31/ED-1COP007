#include "list.h"

#include "../GeometricForms/segment.h"
#include "../argvFunc.h"
#include "../controller.h"
#include "../geo.h"
#include "../qry.h"
#include "../svg.h"
#include "../util.h"

typedef struct Cell {
    void *data;
    struct Cell *next;
    struct Cell *prev;
} Cell;

typedef struct List {
    size_t size;
    Cell *head;
    Cell *tail;
} List;

size_t length(Lista Stlist) {
    List *list = Stlist;

    return list ? list->size : puts("length: A lista não existe") - ERROR;
}

void *get(Celula cell) {
    Cell *aux = cell;

    return aux ? aux->data : NULL;
}

void *getFirst(Lista Stlist) {
    List *list = Stlist;

    return list->head;
}

void *getLast(Lista Stlist) {
    List *list = Stlist;

    return list->tail;
}

void *getNext(Lista Stlist, Celula celula) {
    Cell *cell = celula;

    return cell ? cell->next : NULL;
}

void *getPrevious(Lista Stlist, Celula celula) {
    Cell *cell = celula;

    return cell->prev;
}

int find_per_cell_recursive(Cell *current_cell, Cell *cell, int index) {
    if (!current_cell) return -1;

    if (remov_segment(get(current_cell), (cell))) return index;

    if (!remov_segment(get(current_cell), (cell))) return find_per_cell_recursive(current_cell->next, cell, index + 1);
}

int findPerCell(Lista StLista, void *data) {
    List *lista = StLista;

    if (!lista->head || !StLista || !data) return -1;

    if (remov_segment((lista->head->data), data)) return 0;

    return find_per_cell_recursive(lista->head->next, data, 1);
}

void remov(Lista Stlist, Celula cell) {
    if (!cell || !Stlist) return;

    int index = findPerCell(Stlist, cell);
    List *list = Stlist;
    Cell *aux, *aux2;

    if (!list->head || index > list->size) {
        puts("Nao existe celula neste index");
        return;
    }

    if (list->size == 1) {
        aux = list->head;
        list->head = NULL;
        list->tail = NULL;

    }

    else if (index == 0) {
        aux = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;

    }

    else if (index == list->size - 1) {
        aux = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;

    }

    else {
        aux = atPos(list, index);
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }

    //free(aux->data);
    free(aux);

    list->size--;
}

Lista createLista(int size) {
    List *list = calloc(1, sizeof(List));

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

Celula insert(Lista Stlist, void *data) {
    List *list = Stlist;
    Cell *aux = calloc(1, sizeof(Cell));

    if (!Stlist || !data || !aux) {
        return NULL;
    }

    aux->data = data;
    aux->next = NULL;
    aux->prev = NULL;

    if (!list->head) {
        list->head = aux;
        list->tail = aux;

    }

    else {
        list->tail->next = aux;
        aux->prev = list->tail;
        list->tail = aux;
    }

    list->size++;
}

Celula atPos(Lista Stlist, int index) {
    if (index >= length(Stlist))
        return NULL;

    List *list = Stlist;

    Cell *aux = list->head;

    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }

    return aux;
}

void freeList(Lista Stlist, int remove_data, void (*free_data)(void *data)) {
    List *list = Stlist;
    Cell *aux1 = getFirst(list), *aux2;

    for (int i = 0; i < list->size; i++) {
        aux2 = aux1;
        aux1 = getNext(list, aux1);
        if (remove_data)
            free_data(aux2->data);
        free(aux2);
    }

    free(list);
}
