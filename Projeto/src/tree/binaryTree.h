#ifndef LIB_BINARYTREE_H
#define LIB_BINARYTREE_H

/* Modulo voltado a interacao com arvores binarias */

typedef struct binaryTree* binaryTree;
typedef struct binaryNode* binaryNode;
typedef void* binaryTreeElem;

binaryTree createBinaryTree(int (*compare)(const binaryTreeElem a, const binaryTreeElem b));
/* Dado um ponteiro para funcao de comparacao `compare`, cria e retorna arvore binaria */
/* Funcao de comparacao deve retornar -1 caso `a` seja menor que `b`; 0 caso sejam iguais; e 1 caso `a` seja maior que `b` */
/* Caso `compare` seja invalido, retorna NULL */
/* Caso haja falha na alocacao de memoria, retorna NULL */

int isEmptyBinaryTree(binaryTree tree);
/* Dada uma arvore binaria valida `tree`, retorna 1 caso nao contenha elementos; 0 caso contrario */
/* Caso `tree` seja invalida, retorna -1 */

int getSizeBinaryTree(binaryTree tree);
/* Dada uma arvore binaria valida `tree`, retorna numero de elementos nela armazenados */
/* Caso `tree` seja invalida, retorna -1 */

int getHeightBinaryTree(binaryTree tree);
/* Dada uma arvore binaria valida `tree`, retorna sua altura */
/* Caso `tree` seja invalida, retorna -1 */

int getBinaryNodeHeight(binaryTree tree, binaryNode node);
/* Dados uma arvore binaria valida `tree` e um node `node`, retorna altura na qual `node` se encontra */
/* Caso `tree` ou `node` sejam invalidos, retorna -1 */
/* Caso `node` nao esteja em `tree`, retorna -1 */

int isLeafBinaryNode(binaryTree tree, binaryNode node);
/* Dados uma arvore binaria valida `tree` e um node `node`, retorna 0 caso `node` tenha galhos; 1 caso contrario */
/* Caso `tree` ou `node` sejam invalidos, retorna -1 */

binaryNode getRootBinaryTree(binaryTree tree);
/* Dada uma arvore binaria valida `tree`, retorna elemento em sua raiz */
/* Caso `tree` seja invalida, retorna NULL */

binaryNode findBinaryNodeInTree(binaryTree tree, binaryTreeElem elem);
/* Dados uma arvore binaria valida `tree` e um elemento `elem`, encontra node onde `elem` esta armazenado em `tree`*/
/* Caso `tree` ou `elem` sejam invalidos, retorna NULL */
/* Caso `elem` nao exista em `tree`, retorna NULL */

binaryNode findBinaryNodeCustomSearch(binaryTree tree, void* elem, int (*compare) (const binaryTreeElem a, const void* b));
/* Interface para criacao de funcoes que buscam encontrar um elemento da arvore que satisfaz uma certa condicao */

/* Dados uma arvore binaria valida `tree`, um elemento qualquer `elem`, e uma funcao de comparacao `compare`, encontra node de `tree` cujo elemento satisfaz igualdade com `elem` a partir de `compare` */
/* Cajo `tree`, `elem`, ou `compare` sejam invalidos, retorna NULL */
/* Caso nenhum elemento de `tree` satisfaca igualdade com `elem`, retorna NULL */

binaryNode getBinaryNodeLeftChild(binaryTree tree, binaryNode node);
/* Dados uma arvore binaria `tree` e um node `node`, retorna galho a esquerda de `node` */
/* Caso `tree` ou `node` sejam invalidos, retorna NULL */
/* Caso `node` nao tenha galho a esquerda, retorna NULL */

binaryNode getBinaryNodeRightChild(binaryTree tree, binaryNode node);
/* Dados uma arvore binaria `tree` e um node `node`, retorna galho a direita de `node` */
/* Caso `tree` ou `node` sejam invalidos, retorna NULL */
/* Caso `node` nao tenha galho a direita, retorna NULL */

binaryNode getBinaryNodeParent(binaryTree tree, binaryNode node);
/* Dados uma arvore binaria `tree` e um node `node`, retorna galho acima de `node` */
/* Caso `tree` ou `node` sejam invalidos, retorna NULL */

binaryNode appendBinaryTree(binaryTree tree, binaryTreeElem elem);
/* Dados uma arvore binaria `tree` e um elemento `elem`, insere `elem` em `tree` e retorna node criado */
/* Caso `tree` ou `elem` sejam invalidos, retorna NULL */
/* Caso `elem` ja exista em `tree`, retorna NULL */

binaryTreeElem removeFromBinaryTree(binaryTree tree, binaryNode node);
/* Dados uma arvore binaria `tree` e um node `node`, remove `node` de `tree` e retorna elemento nele armazenado */
/* Caso `tree` ou `node` sejam invalidos, retorna NULL */
/* Caso `node` nao exista em `tree`, retorna NULL */

/* Caso `node` possua dois galhos, node a ser removido se torna node mais a direita da sub-arvore a esquerda, e apenas o valor de `node` e trocado */
/* Dessa forma, nao e recomendado utilizar nodes previamente salvos, uma vez que o ponteiro referente pode ja ter sido removido */

binaryTreeElem getElemInBinaryNode(binaryTree tree, binaryNode node);
/* Dados uma arvore binaria `tree` e um node `node`, retorna elemento armazenado em `node` */
/* Caso `tree` ou `node` sejam invalidos, retorna NULL */

void destroyBinaryTree(binaryTree tree);
/* Dada uma arvore binaria `tree`, libera toda a memoria por ela ocupada */
/* Caso `tree` seja invalida, nao realiza nenhuma acao */
/* ***NAO*** libera elementos armazenados automaticamente */

/**/
#endif
