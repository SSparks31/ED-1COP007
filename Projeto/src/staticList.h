#ifndef LIB_STATICLIST_H
#define LIB_STATICLIST_H

/* Implementacao de lista estatica e operacoes relacionadas */

typedef struct sList* sListT;
typedef struct sListPos* sListPosT;
/* Definicao de tipo, implementacao no .c */

typedef void* sListItem;


sListT createSList(int maxElem);
/* Dado um tamanho maximo `maxElem`, cria e retorna lista estatica */
/* Caso `maxElem` seja zero, retorna NULL */
/* Caso nao seja possivel alocar memoria, retorna NULL */

int isEmptySList(sListT sList); 
/* Dada uma lista valida `sList`, retorna 1 caso `sList` esteja vazia, 0 caso contrario */
/* Caso `sList` seja invalida, retorna -1 */

int lengthSList(sListT sList);
/* Dada uma lista valida `sList`, retorna seu comprimento, ou seja, o numero de elementos armazenados nela */
/* Caso `sList` seja invalida, retorna -1 */

int isFullSList(sListT sList); 
/* Dada uma lista valida `slist`, retorna 1 caso `sList` esteja cheia, 0 caso contrario */
/* Caso `sList` seja invalida, retorna -1 */

sListPosT getFirstElementSList(sListT sList); 
/* Dada uma lista `sList` valida, retorna ponteiro para primeira posicao de `sList` */
/* Caso `sList` esteja vazia, retorna NULL */

sListPosT getNextElementSList(sListT sList, sListPosT pos);
/* Dados uma lista `sList` valida e uma posicao `pos`, retorna ponteiro para posicao de `sList` apos `pos`  */
/* Caso `sList` esteja vazia, retorna NULL */

sListPosT getLastElementSList(sListT sList);
/* Dada uma lista `sList` valida, retorna ponteiro para ultima posicao de `sList` */
/* Caso `sList` esteja vazia, retorna NULL */

sListPosT getPrevElementSList(sListT sList, sListPosT pos);
/* Dados uma lista `sList` valida e uma posicao `pos`, retorna ponteiro para posicao de `sList` antes de `pos`  */
/* Caso `sList` esteja vazia, retorna NULL */

sListPosT appendSList(sListT sList, sListItem elem); 
/* Dados uma lista valida `sList` e um elemento `elem`, insere `elem` no final de `sList` */
/* Retorna ponteiro para posicao do elemento na lista */
/* Caso nao seja possivel inserir `elem` em `sList`, retorna NULL */
/* Caso `sList` ou `elem` sejam invalidos, retorna NULL */

sListPosT insertBeforeSList(sListT sList, sListPosT pos, sListItem elem);
/* Dados uma lista valida `sList`, uma posicao `pos` e um elemento `elem`, insere `elem` antes de `pos` */
/* Retorna ponteiro para posicao do elemento na lista */
/* Caso nao seja possivel inserir `elem` em `sList`, retorna NULL */
/* Caso `sList` ou `elem` sejam invalidos, retorna NULL */

sListPosT insertAfterSList(sListT sList, sListPosT pos, sListItem elem);
/* Dados uma lista valida `sList`, uma posicao `pos` e um elemento `elem`, insere `elem` apos `pos` */
/* Retorna ponteiro para posicao do elemento na lista */
/* Caso nao seja possivel inserir `elem` em `sList`, retorna NULL */
/* Caso `sList` ou `elem` sejam invalidos, retorna NULL */

sListItem removeSList(sListT sList, sListPosT pos);
/* Dados uma lista valida `sList` e uma posicao `pos`, remove elemento `pos` de `sList` */
/* Retorna ponteiro para elemento existente em `pos` para que usuario possa desalocar, caso necessario */

sListItem getItemSList(sListT sList, sListPosT pos);
/* Dados uma lista valida `sList` e um ponteiro para posicao na lista `pos`, retorna item armazenado em `pos` */
/* Caso `sList` ou `pos` sejam invalidos, retorna NULL */

void destroySList(sListT sList);
/* Dado um ponteiro para lista valida `sList`, destroi lista */
/* Caso `sList` nao esteja vazia, avisa usuario que nao e feito o desalocamento automaticamente, */
/* devido a possibilidade de elementos nao serem dinamicamente alocados */

#endif