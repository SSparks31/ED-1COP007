#ifndef LIB_LIST_H
#define LIB_LIST_H

#include "staticList.h"
#include "dynamicList.h"

typedef struct list listT;
typedef void* listElemT;
typedef void* listItem;

ListT createList(int maxElem, char* type);
/* Dado um tamanho maximo `maxElem`, cria e retorna lista */
/* Caso `maxElem` seja zero, retorna NULL */
/* Caso nao seja possivel alocar memoria, retorna NULL */

int isEmptyList(ListT List, char* type); 
/* Dada uma lista valida `List`, retorna 1 caso `List` esteja vazia, 0 caso contrario */
/* Caso `List` seja invalida, retorna -1 */

int lengthList(ListT List, char* type);
/* Dada uma lista valida `List`, retorna seu comprimento, ou seja, o numero de elementos armazenados nela */
/* Caso `List` seja invalida, retorna -1 */

int isFullList(ListT List, char* type); 
/* Dada uma lista valida `List`, retorna 1 caso `List` esteja cheia, 0 caso contrario */
/* Caso `List` seja invalida, retorna -1 */

ListPosT getFirstElementList(ListT List, char* type); 
/* Dada uma lista `List` valida, retorna ponteiro para primeira posicao de `List` */
/* Caso `List` esteja vazia, retorna NULL */

ListPosT getNextElementList(ListT List, ListPosT pos, char* type);
/* Dados uma lista `List` valida e uma posicao `pos`, retorna ponteiro para posicao de `List` apos `pos`  */
/* Caso `List` esteja vazia, retorna NULL */

ListPosT getLastElementList(ListT List, char* type);
/* Dada uma lista `List` valida, retorna ponteiro para ultima posicao de `List` */
/* Caso `List` esteja vazia, retorna NULL */

ListPosT getPrevElementList(ListT List, ListPosT pos, char* type);
/* Dados uma lista `List` valida e uma posicao `pos`, retorna ponteiro para posicao de `List` antes de `pos`  */
/* Caso `List` esteja vazia, retorna NULL */

ListPosT appendList(ListT List, ListItem elem, char* type); 
/* Dados uma lista valida `List` e um elemento `elem`, insere `elem` no final de `List` */
/* Retorna ponteiro para posicao do elemento na lista */
/* Caso nao seja possivel inserir `elem` em `List`, retorna NULL */
/* Caso `List` ou `elem` sejam invalidos, retorna NULL */

ListPosT insertBeforeList(ListT List, ListPosT pos, ListItem elem, char* type);
/* Dados uma lista valida `List`, uma posicao `pos` e um elemento `elem`, insere `elem` antes de `pos` */
/* Retorna ponteiro para posicao do elemento na lista */
/* Caso nao seja possivel inserir `elem` em `List`, retorna NULL */
/* Caso `List` ou `elem` sejam invalidos, retorna NULL */

ListPosT insertAfterList(ListT List, ListPosT pos, ListItem elem, char* type);
/* Dados uma lista valida `List`, uma posicao `pos` e um elemento `elem`, insere `elem` apos `pos` */
/* Retorna ponteiro para posicao do elemento na lista */
/* Caso nao seja possivel inserir `elem` em `List`, retorna NULL */
/* Caso `List` ou `elem` sejam invalidos, retorna NULL */

ListItem removeList(ListT List, ListPosT pos, char* type);
/* Dados uma lista valida `List` e uma posicao `pos`, remove elemento `pos` de `List` */
/* Retorna ponteiro para elemento existente em `pos` para que usuario possa desalocar, caso necessario */

ListItem getItemList(ListT List, ListPosT pos, char* type);
/* Dados uma lista valida `List` e um ponteiro para posicao na lista `pos`, retorna item armazenado em `pos` */
/* Caso `List` ou `pos` sejam invalidos, retorna NULL */

void destroyList(ListT List, char* type);
/* Dado um ponteiro para lista valida `List`, destroi lista */
/* Caso `List` nao esteja vazia, avisa usuario que nao e feito o desalocamento automaticamente, */
/* devido a possibilidade de elementos nao serem dinamicamente alocados */

/**/
#endif