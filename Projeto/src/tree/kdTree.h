#ifndef LIB_KDTREE_H
#define LIB_KDTREE_H

typedef struct kdTree* kdTree;
typedef struct kdNode* kdNode;
typedef void* kdTreeElem;

kdTree createKDTree(int (*compare)(const kdTreeElem a, const kdTreeElem b));
/* Dado um ponteiro para funcao de comparacao `compare`, cria e retorna arvore k-d */
/* Funcao de comparacao deve retornar -1 caso `a` seja menor que `b`; 0 caso sejam iguais; e 1 caso `a` seja maior que `b` */
/* Caso `compare` seja invalido, retorna NULL */
/* Caso haja falha na alocacao de memoria, retorna NULL */

int isEmptyKDTree(kdTree tree);
/* Dada uma arvore k-d valida `tree`, retorna 1 caso nao contenha elementos; 0 caso contrario */
/* Caso `tree` seja invalida, retorna -1 */

int getSizeKDTree(kdTree tree);
/* Dada uma arvore k-d valida `tree`, retorna numero de elementos nela armazenados */
/* Caso `tree` seja invalida, retorna -1 */

int getHeightKDTree(kdTree tree);
/* Dada uma arvore k-d valida `tree`, retorna sua altura */
/* Caso `tree` seja invalida, retorna -1 */

int getKDNodeHeight(kdTree tree, kdNode node);
/* Dados uma arvore k-d valida `tree` e um node `node`, retorna altura na qual `node` se encontra */
/* Caso `tree` ou `node` sejam invalidos, retorna -1 */
/* Caso `node` nao esteja em `tree`, retorna -1 */

int isLeafKDNode(kdTree tree, kdNode node);
/* Dados uma arvore k-d valida `tree` e um node `node`, retorna 0 caso `node` tenha galhos; 1 caso contrario */
/* Caso `tree` ou `node` sejam invalidos, retorna -1 */

kdNode getRootKDTree(kdTree tree);
/* Dada uma arvore k-d valida `tree`, retorna elemento em sua raiz */
/* Caso `tree` seja invalida, retorna NULL */

kdNode findKDNodeInTree(kdTree tree, kdTreeElem elem);
/* Dados uma arvore k-d valida `tree` e um elemento `elem`, encontra node onde `elem` esta armazenado em `tree`*/
/* Caso `tree` ou `elem` sejam invalidos, retorna NULL */
/* Caso `elem` nao exista em `tree`, retorna NULL */

kdNode findKDNodeCustomSearch(kdTree tree, void* elem, int (*compare) (const kdTreeElem a, const void* b));
/* Interface para criacao de funcoes que buscam encontrar um elemento da arvore que satisfaz uma certa condicao */

/* Dados uma arvore k-d valida `tree`, um elemento qualquer `elem`, e uma funcao de comparacao `compare`, encontra node de `tree` cujo elemento satisfaz igualdade com `elem` a partir de `compare` */
/* Cajo `tree`, `elem`, ou `compare` sejam invalidos, retorna NULL */
/* Caso nenhum elemento de `tree` satisfaca igualdade com `elem`, retorna NULL */

kdNode getKDNodeLeftChild(kdTree tree, kdNode node);
/* Dados uma arvore k-d `tree` e um node `node`, retorna galho a esquerda de `node` */
/* Caso `tree` ou `node` sejam invalidos, retorna NULL */
/* Caso `node` nao tenha galho a esquerda, retorna NULL */

kdNode getKDNodeRightChild(kdTree tree, kdNode node);
/* Dados uma arvore k-d `tree` e um node `node`, retorna galho a direita de `node` */
/* Caso `tree` ou `node` sejam invalidos, retorna NULL */
/* Caso `node` nao tenha galho a direita, retorna NULL */

kdNode getKDNodeParent(kdTree tree, kdNode node);
/* Dados uma arvore k-d `tree` e um node `node`, retorna galho acima de `node` */
/* Caso `tree` ou `node` sejam invalidos, retorna NULL */

kdNode appendKDTree(kdTree tree, kdTreeElem elem);
/* Dados uma arvore k-d `tree` e um elemento `elem`, insere `elem` em `tree` e retorna node criado */
/* Caso `tree` ou `elem` sejam invalidos, retorna NULL */
/* Caso `elem` ja exista em `tree`, retorna NULL */

kdTreeElem removeFromKDTree(kdTree tree, kdNode node);
/* Dados uma arvore k-d `tree` e um node `node`, remove `node` de `tree` e retorna elemento nele armazenado */
/* Caso `tree` ou `node` sejam invalidos, retorna NULL */
/* Caso `node` nao exista em `tree`, retorna NULL */

/* Caso `node` possua dois galhos, node a ser removido se torna node j-dimensional maximo da sub-arvore a esquerda, e apenas o valor de `node` e trocado */
/* Dessa forma, nao e recomendado utilizar nodes previamente salvos, uma vez que o ponteiro referente pode ja ter sido removido */

kdTreeElem getElemInKDNode(kdTree tree, kdNode node);
/* Dados uma arvore k-d `tree` e um node `node`, retorna elemento armazenado em `node` */
/* Caso `tree` ou `node` sejam invalidos, retorna NULL */

void destroyKDTree(kdTree tree);
/* Dada uma arvore k-d `tree`, libera toda a memoria por ela ocupada */
/* Caso `tree` seja invalida, nao realiza nenhuma acao */
/* ***NAO*** libera elementos armazenados automaticamente */


/**/
#endif