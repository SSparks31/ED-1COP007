#include "../util.h"

#ifndef LIST_H
#define LIST_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef void* Lista;

typedef void* Celula;


//TAD LISTA

/*Return: uma lista vazia, caso seja estatica ela terá 'size' células                                            */
Lista createLista(int size);

/*Retorno Padrao:  numeto de elementos da 'Stlidt'                                                               */
/*Retorno Erro: 0, caso a lista não exista                                                                       */
size_t length(Lista Stlist);

/*Pre Condicao: 'Stlist' e 'data' existem                                                                        */
/*Funcao: Cria uma celula com o conteudo de 'data' e a insere no fim de 'Stlist'                                 */
/*Retorno: Posicao de memoria da celula criada                                                                   */
Celula insert(Lista Stlist, void* data);

/*Pre Condicao: 'Stlist' e 'data' existem  & 'data' é elemento de 'Stlist'                                       */
/*Funcao: Remove a celula 'data' de Stlist                                                                       */
void remov(Lista Stlist, Celula data);

/*Pre Condicao: 'cell' existe & 'cell' possui um elemento                                                        */
/*Retorno: Posicao de memoria do elemento de 'cell'                                                              */
void* get(Celula cell);

/*Pre Condicao: 'cell' pertence a 'Stlist                                     */
/*Funcao: Cria uma celula com o conteudo de 'data' e a insere na posicao imediatamente anterior a 'cell'         */
/*Retorno: Posicao de memoria da celula criada                                                                   */
void *insertBefore(Lista Stlist, Celula cell, void* data);

/*Pre Condicao: 'cell' pertence a 'Stlist                                                                        */
/*Funcao: Cria uma celula com o conteudo de 'data' e a insere na posicao imediatamente posterior a 'cell'        */
/*Retorno: Posicao de memoria da celula criada                                                                   */
void *insertAfter(Lista Stlist, Celula Scell, void* iten);

/*Pre condicao: 'list' existe                                                                                    */
/*Retorno: primeiro elemento de 'list' OU NULL, caso a lista seja vazia                                          */
void *getFirst(Lista list);

/*Pre condicao: 'cell' pertence a 'list'                                                                          */
/*Retorno: Posicao de memoria da celula imediatamente posterior a 'cell' OU NULL, caso 'cell' seja a ultima celula*/
void *getNext(Lista list, Celula cell);

/*Pre condicao: 'list' existe                                                                                    */
/*Retorno: ultimo elemento de 'list' OU NULL, caso a lista seja vazia                                            */
void *getLast(Lista list);

/*Pre condicao: 'cell' pertence a 'list'                                                                          */
/*Retorno: Posicao de memoria da celula imediatamente anterior a 'cell' OU NULL, caso 'cell' seja a primeira celula*/
void *getPrevious(Lista Stlist, Celula cell);

//FUNÇÕES ADICIONAIS

// Retorna quantas vezes as celulas de 'list' foram visitadas
int getVisits(Lista list);
// Incrementa o contador de visita de 'list' em n
void visits(Lista list, int n);
// Retorna a celula na posicao 'index' de 'list'
void *atPos(Lista list, int index);
//Libera toda a memoria alocada na criacao da lista
void freeList(Lista Stlist, int remove_data, void (*free_data)(void *data));

/**/
#endif