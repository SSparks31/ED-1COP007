#include "binaryTree.h"

#include "../helper/mathHelp.h"

#include <stdio.h>
#include <stdlib.h>

struct binaryNode {
    binaryTreeElem elem;

    binaryNode left;
    binaryNode right;
};

struct binaryTree {
    binaryNode root;
    
    int numElements;

    int (*compare)(const binaryTreeElem a, const binaryTreeElem b);
};

binaryNode recursiveFindBinaryNode(binaryTree tree, binaryNode node, binaryTreeElem elem);

int findHeightBinaryTree(binaryTree tree, binaryNode node);

int findBinaryNodeHeight(binaryTree tree, binaryNode node, binaryNode aux);

binaryNode recursiveFindBinaryNode(binaryTree tree, binaryNode node, binaryTreeElem elem);

binaryNode recursiveBinaryCustomSearch(binaryTree tree, void* elem, int (*compare) (const binaryTreeElem a, const void* b), binaryNode candidate);

binaryNode recursiveFindBinaryNodeParent(binaryTree tree, binaryNode node, binaryNode parentCandidate);

binaryTree createBinaryTree(int (*compare)(const binaryTreeElem a, const binaryTreeElem b)) {
    if (!compare) {
        return NULL;
    }
    
    binaryTree tree = malloc(sizeof(struct binaryTree));
    if (!tree) {
        return NULL;
    }

    tree->root = NULL;

    tree->numElements = 0;

    tree->compare = compare;

    return tree;
}

int isEmptyBinaryTree(binaryTree tree) {
    if (!tree) {
        return -1;
    }

    return tree->root == NULL;
}

int getSizeBinaryTree(binaryTree tree) {
    if (!tree) {
        return -1;
    }

    return tree->numElements;
}

int findHeightBinaryTree(binaryTree tree, binaryNode node) {
    if (!node) {
        return 0;
    }

    binaryNode left = getBinaryNodeLeftChild(tree, node);
    binaryNode right = getBinaryNodeRightChild(tree, node);

    int leftHeight = findHeightBinaryTree(tree, left);
    int rightHeight = findHeightBinaryTree(tree, right);

    return imax(1 + leftHeight, 1 + rightHeight);
}

int getHeightBinaryTree(binaryTree tree) {
    if (!tree) {
        return -1;
    }

    return findHeightBinaryTree(tree, tree->root);
}

int findBinaryNodeHeight(binaryTree tree, binaryNode node, binaryNode aux) {
    if (!aux) {
        return -1;
    }
    
    if (aux == node) {
        return 1;
    }

    int heightLeftSubtree = findBinaryNodeHeight(tree, node, getBinaryNodeLeftChild(tree, aux));
    if (heightLeftSubtree > 0) {
        return 1 + heightLeftSubtree;
    }
    
    int heightRightSubtree = findBinaryNodeHeight(tree, node, getBinaryNodeRightChild(tree, aux));
    if (heightRightSubtree > 0) {
        return 1 + heightRightSubtree;
    }

    return -1;
}

int getBinaryNodeHeight(binaryTree tree, binaryNode node) {
    return findBinaryNodeHeight(tree, node, getRootBinaryTree(tree));
}

int isLeafBinaryNode(binaryTree tree, binaryNode node) {
    if (!tree || !node) {
        return -1;
    }

    binaryNode left = getBinaryNodeLeftChild(tree, node);
    binaryNode right = getBinaryNodeRightChild(tree, node);

    return (left || right);
}

binaryNode getRootBinaryTree(binaryTree tree) {
    if (!tree) {
        return NULL;
    }

    return tree->root;
}

binaryNode recursiveFindBinaryNode(binaryTree tree, binaryNode node, binaryTreeElem elem) {
    if (!node) {
        return NULL;
    }

    binaryTreeElem nodeElem = getElemInBinaryNode(tree, node);
    if (tree->compare(nodeElem, elem) == 0) {
        return node;
    }

    binaryNode leftSubtree = recursiveFindBinaryNode(tree, getBinaryNodeLeftChild(tree, node), elem);
    if (leftSubtree) {
        return leftSubtree;
    }

    binaryNode rightSubtree = recursiveFindBinaryNode(tree, getBinaryNodeRightChild(tree, node), elem);
    if (rightSubtree) {
        return rightSubtree;
    }

    return NULL;
}

binaryNode findBinaryNodeInTree(binaryTree tree, binaryTreeElem elem) {
    return recursiveFindBinaryNode(tree, getRootBinaryTree(tree), elem);
}

binaryNode recursiveBinaryCustomSearch(binaryTree tree, void* elem, int (*compare) (const binaryTreeElem a, const void* b), binaryNode candidate) {
    if (!candidate) {
        return NULL;
    }

    binaryTreeElem auxElem = getElemInBinaryNode(tree, candidate);
    if (compare(auxElem, elem) == 0) {
        return candidate;
    }

    binaryNode leftCandidate = recursiveBinaryCustomSearch(tree, elem, compare, getBinaryNodeLeftChild(tree, candidate));
    if (leftCandidate) {
        return leftCandidate;
    }
    
    binaryNode rightCandidate = recursiveBinaryCustomSearch(tree, elem, compare, getBinaryNodeRightChild(tree, candidate));
    if (rightCandidate) {
        return rightCandidate;
    }

    return NULL;
}

binaryNode findBinaryNodeCustomSearch(binaryTree tree, void* elem, int (*compare) (const binaryTreeElem a, const void* b)) {
    return recursiveBinaryCustomSearch(tree, elem, compare, getRootBinaryTree(tree));
}

binaryNode getBinaryNodeLeftChild(binaryTree tree, binaryNode node) {
    if (!tree || !node) {
        return NULL;
    }

    return node->left;
}

binaryNode getBinaryNodeRightChild(binaryTree tree, binaryNode node) {
    if (!tree || !node) {
        return NULL;
    }

    return node->right;
}

binaryNode recursiveFindBinaryNodeParent(binaryTree tree, binaryNode node, binaryNode parentCandidate) {
    if (!parentCandidate) {
        return NULL;
    }

    binaryNode left = getBinaryNodeLeftChild(tree, parentCandidate);
    binaryNode right = getBinaryNodeRightChild(tree, parentCandidate);

    if (node == left || node == right) {
        return parentCandidate;
    }

    binaryNode leftCandidate = recursiveFindBinaryNodeParent(tree, node, left);
    if (leftCandidate) {
        return leftCandidate;
    }

    binaryNode rightCandidate = recursiveFindBinaryNodeParent(tree, node, right);
    if (rightCandidate) {
        return rightCandidate;
    }

    return NULL;
}

binaryNode getBinaryNodeParent(binaryTree tree, binaryNode node) {
    return recursiveFindBinaryNodeParent(tree, node, getRootBinaryTree(tree));
}

binaryNode appendBinaryTree(binaryTree tree, binaryTreeElem elem) {
    if (!tree || !elem) {
        return NULL;
    }

    binaryNode newNode = malloc(sizeof(struct binaryNode));
    if (!newNode) {
        return NULL;
    }

    newNode->elem = elem;

    newNode->left = NULL;
    newNode->right = NULL;

    binaryNode aux = getRootBinaryTree(tree);
    if (!aux) {
        tree->root = newNode;

        tree->numElements++;
        return newNode;
    }

    while (aux) {
        binaryTreeElem auxElem = getElemInBinaryNode(tree, aux);
        binaryTreeElem next;
        int comp = tree->compare(elem, auxElem);

        if (comp == -1) {
            next = getBinaryNodeLeftChild(tree, aux);
            
            if (!next) {
                aux->left = newNode;
                break;
            }

        } else if (comp == 1) {
            next = getBinaryNodeRightChild(tree, aux);

            if (!next) {
                aux->right = newNode;
                break;
            }

        } else {
            return NULL;
        }

        aux = next;
    }

    tree->numElements++;
    return newNode;
}

binaryTreeElem removeFromBinaryTree(binaryTree tree, binaryNode node) {
    if (!tree || !node) {
        return NULL;
    }

    binaryTreeElem nodeElem = node->elem;

    binaryNode left = getBinaryNodeLeftChild(tree, node);
    binaryNode right = getBinaryNodeRightChild(tree, node);

    binaryNode parent = getBinaryNodeParent(tree, node);
    binaryNode parentLeftChild = getBinaryNodeLeftChild(tree, parent);

    if (!(left || right)) {
        if (!parent) {
            tree->root = NULL;
        } else if (node == parentLeftChild) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }

        free(node);
        tree->numElements--;
        return nodeElem;
    }

    if (left && right) {
        binaryNode rightmostNode = left;
        binaryNode next;
        while ((next = getBinaryNodeRightChild(tree, rightmostNode))) {
            rightmostNode = next;
        }

        binaryTreeElem newElem = removeFromBinaryTree(tree, rightmostNode);
        node->elem = newElem;

        return nodeElem;
    }

    binaryNode aux;
    if (left) {
        aux = left;
    } else {
        aux = right;
    }

    if (!parent) {
        tree->root = aux;
    } else if (node == parentLeftChild) {
        parent->left = aux;
    } else {
        parent->right = aux;
    }

    free(node);
    tree->numElements--;
    return nodeElem;
}

binaryTreeElem getElemInBinaryNode(binaryTree tree, binaryNode node) {
    if (!tree || !node) {
        return NULL;
    }
    
    return node->elem;
}

void destroyBinaryTree(binaryTree tree) {
    if (!tree) {
        return;
    }

    if (!isEmptyBinaryTree(tree)) {
        printf("\n------------\n");
        printf("ATENCAO:\nO desalocamento de elementos da arvore nao e realizado automaticamente; caso seja necessario, modifique seu programa para realizar a remocao e desalocamento.\n");
    }

    while (!isEmptyBinaryTree(tree)) {
        removeFromBinaryTree(tree, getRootBinaryTree(tree));
    }

    free(tree);
}