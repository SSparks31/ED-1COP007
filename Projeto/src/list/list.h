#ifndef LIB_LIST_H
#define LIB_LIST_H

/* Modulo voltado a interacao com listas ligadas */
/* Contem duas implementacoes: Estatica em staticList.c; Dinamica em dynamicList.c */
/* Apenas uma implementacao pode ser usada por programa */

typedef struct list* listT;
typedef struct listPos* listPosT;
typedef void* listElemT;

listT createList();
/* Cria lista contendo no maximo `maxElem` elementos */
/* Caso haja problema na alocacao de memoria, retorna NULL */
/* Retorna ponteiro para lista criada */

int isEmptyList(listT list);
/* Dada uma lista ligada `list`, retorna verdadeiro caso `list` esteja vazia; falso, caso contrario */
/* Caso `list` seja invalida, retorna -1 */

int lengthList(listT list);
/* Dada uma lista ligada `list`, retorna numero de elementos armazenados em `list` */
/* Caso `list` seja invalida, retorna -1 */

listPosT getFirstElementList(listT list);
/* Dada uma lista ligada `list`, retorna primeira posicao de `list` */
/* Caso `list` seja invalida ou esteja vazia, retorna NULL */

listPosT getNextElementList(listT list, listPosT pos);
/* Dados uma lista ligada `list` e uma posicao `pos`, retorna posicao em seguida de `pos` */
/* Caso `list` ou `pos` sejam invalidos, retorna NULL */

listPosT getLastElementList(listT list);
/* Dada uma lista ligada `list`, retorna ultima posicao de `list` */
/* Caso `list` seja invalida ou esteja vazia, retorna -1 */

listPosT getPrevElementList(listT list, listPosT pos);
/* Dados uma lista ligada `list` e uma posicao `pos`, retorna posicao que antecede `pos` */
/* Caso `list` ou `pos` sejam invalidos, retorna NULL */

listPosT appendList(listT list, listElemT elem);
/* Dados uma lista ligada `list` e um elemento `elem`, insere `elem` no final de `list` */
/* Caso `list` ou `elem` sejam invalidos, retorna NULL */
/* Retorna posicao na qual `elem` foi inserido */

listPosT insertBeforeList(listT list, listPosT pos, listElemT elem);
/* Dados uma lista ligada `list`, uma posicao `pos` e um elemento `elem`, insere `elem` logo antes de `pos` */
/* Caso `list`, `pos` ou `elem` sejam invalidos, retorna NULL */
/* Retorna posicao na qual `elem` foi inserido */

listPosT insertAfterList(listT list, listPosT pos, listElemT elem);
/* Dados uma lista ligada `list`, uma posicao `pos` e um elemento `elem`, insere `elem` logo em seguida de `pos` */
/* Caso `list`, `pos` ou `elem` sejam invalidos, retorna NULL */
/* Retorna posicao na qual `elem` foi inserido */

listElemT removeList(listT list, listPosT pos);
/* Dados uma lista ligada `list` e uma posicao `pos`, remove `pos` de `list` */
/* Caso `list` ou `pos` sejam invalidos, retorna NULL */
/* Caso lista esteja vazia, retorna NULL */
/* Retorna elemento presente em `pos` antes da remocao */

listElemT getElementList(listT list, listPosT pos);
/* Dados uma lista ligada `list` e uma posicao `pos`, retorna elemento presente em `pos` */
/* Caso `list` ou `pos` sejam invalidos, retorna NULL */

int getAccessCountList(listT list);
/* Dada uma lista ligada `list`, retorna valor referente ao numero de acessos realizados */
/* Caso `list` seja invalida, retorna -1 */

void destroyList(listT list);
/* Dada uma lista ligada `list`, libera toda a memoria por ela ocupada */
/* Caso `list` seja invalida, nao realiza nenhuma acao */
/* ***NAO*** libera elementos armazenados automaticamente */

#endif