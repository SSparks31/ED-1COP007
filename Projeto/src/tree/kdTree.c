#include "./kdTree.h"

#include "../helper/mathHelp.h"

#include <stdio.h>
#include <stdlib.h>

struct kdNode {
    kdTreeElem elem;

    kdNode left;
    kdNode right;
};

struct kdTree {
    kdNode root;
    
    int numElements;

    int (*compare)(const kdTreeElem a, const kdTreeElem b);
};

kdNode recursiveFindKDNode(kdTree tree, kdNode node, kdTreeElem elem);

int findHeightKDTree(kdTree tree, kdNode node);

kdNode recursiveFindKDNode(kdTree tree, kdNode node, kdTreeElem elem);

kdNode recursiveKDCustomSearch(kdTree tree, kdNode candidate, void* elem, int (*compare) (const kdTreeElem a, const void* b));

kdNode recursiveFindKDNodeParent(kdTree tree, kdNode node, kdNode parentCandidate);

kdTree createKDTree(int (*compare)(const kdTreeElem a, const kdTreeElem b)) {
    if (!compare) {
        return NULL;
    }
    
    kdTree tree = malloc(sizeof(struct kdTree));
    if (!tree) {
        return NULL;
    }

    tree->root = NULL;

    tree->numElements = 0;

    tree->compare = compare;

    return tree;
}

int isEmptyKDTree(kdTree tree) {
    if (!tree) {
        return -1;
    }

    return tree->root == NULL;
}

int getSizeKDTree(kdTree tree) {
    if (!tree) {
        return -1;
    }

    return tree->numElements;
}

int findHeightKDTree(kdTree tree, kdNode node) {
    if (!node) {
        return 0;
    }

    kdNode left = getKDNodeLeftChild(tree, node);
    kdNode right = getKDNodeRightChild(tree, node);

    int leftHeight = findHeightKDTree(tree, left);
    int rightHeight = findHeightKDTree(tree, right);

    return max(1 + leftHeight, 1 + rightHeight);
}

int getHeightKDTree(kdTree tree) {
    if (!tree) {
        return -1;
    }

    return findHeightKDTree(tree, tree->root);
}

int findKDNodeHeight(kdTree tree, kdNode node, kdNode aux) {
    if (!aux) {
        return -1;
    }
    
    if (aux == node) {
        return 1;
    }

    int heightLeftSubtree = findKDNodeHeight(tree, node, getKDNodeLeftChild(tree, aux));
    if (heightLeftSubtree > 0) {
        return 1 + heightLeftSubtree;
    }
    
    int heightRightSubtree = findKDNodeHeight(tree, node, getKDNodeRightChild(tree, aux));
    if (heightRightSubtree > 0) {
        return 1 + heightRightSubtree;
    }

    return -1;
}

int getKDNodeHeight(kdTree tree, kdNode node) {
    return findKDNodeHeight(tree, node, getRootKDTree(tree));
}

int isLeafKDNode(kdTree tree, kdNode node) {
    if (!tree || !node) {
        return -1;
    }

    kdNode left = getKDNodeLeftChild(tree, node);
    kdNode right = getKDNodeRightChild(tree, node);

    return (left || right);
}

kdNode getRootKDTree(kdTree tree) {
    if (!tree) {
        return NULL;
    }

    return tree->root;
}

kdNode recursiveFindKDNode(kdTree tree, kdNode node, kdTreeElem elem) {
    if (!node) {
        return NULL;
    }

    kdTreeElem nodeElem = getElemInKDNode(tree, node);
    if (tree->compare(nodeElem, elem) == 0) {
        return node;
    }

    kdNode leftSubtree = recursiveFindKDNode(tree, getKDNodeLeftChild(tree, node), elem);
    if (leftSubtree) {
        return leftSubtree;
    }

    kdNode rightSubtree = recursiveFindKDNode(tree, getKDNodeRightChild(tree, node), elem);
    if (rightSubtree) {
        return rightSubtree;
    }

    return NULL;
}

kdNode findKDNodeInTree(kdTree tree, kdTreeElem elem) {
    return recursiveFindKDNode(tree, getRootKDTree(tree), elem);
}

kdNode recursiveKDCustomSearch(kdTree tree, kdNode candidate, void* elem, int (*compare) (const kdTreeElem a, const void* b)) {
    if (!candidate) {
        return NULL;
    }

    kdTreeElem auxElem = getElemInKDNode(tree, candidate);
    if (compare(auxElem, elem) == 0) {
        return candidate;
    }

    kdNode leftCandidate = recursiveKDCustomSearch(tree, getKDNodeLeftChild(tree, candidate), elem, compare);
    if (leftCandidate) {
        return leftCandidate;
    }
    
    kdNode rightCandidate = recursiveKDCustomSearch(tree, getKDNodeRightChild(tree, candidate), elem, compare);
    if (rightCandidate) {
        return rightCandidate;
    }

    return NULL;
}

kdNode findKDNodeCustomSearch(kdTree tree, void* elem, int (*compare) (const kdTreeElem a, const void* b)) {
    return recursiveKDCustomSearch(tree, getRootKDTree(tree), elem, compare);
}

kdNode getKDNodeLeftChild(kdTree tree, kdNode node) {
    if (!tree || !node) {
        return NULL;
    }

    return node->left;
}

kdNode getKDNodeRightChild(kdTree tree, kdNode node) {
    if (!tree || !node) {
        return NULL;
    }

    return node->right;
}

kdNode recursiveFindKDNodeParent(kdTree tree, kdNode node, kdNode parentCandidate) {
    if (!parentCandidate) {
        return NULL;
    }

    kdNode left = getKDNodeLeftChild(tree, parentCandidate);
    kdNode right = getKDNodeRightChild(tree, parentCandidate);

    if (node == left || node == right) {
        return parentCandidate;
    }

    kdNode leftCandidate = recursiveFindKDNodeParent(tree, node, left);
    if (leftCandidate) {
        return leftCandidate;
    }

    kdNode rightCandidate = recursiveFindKDNodeParent(tree, node, right);
    if (rightCandidate) {
        return rightCandidate;
    }

    return NULL;
}

kdNode getKDNodeParent(kdTree tree, kdNode node) {
    return recursiveFindKDNodeParent(tree, node, getRootKDTree(tree));
}

kdNode appendKDTree(kdTree tree, kdTreeElem elem) {
    if (!tree || !elem) {
        return NULL;
    }

    kdNode newNode = malloc(sizeof(struct kdNode));
    if (!newNode) {
        return NULL;
    }

    newNode->elem = elem;

    newNode->left = NULL;
    newNode->right = NULL;

    kdNode aux = getRootKDTree(tree);
    if (!aux) {
        tree->root = newNode;

        return newNode;
    }

    while (aux) {
        kdTreeElem auxElem = getElemInKDNode(tree, aux);
        kdTreeElem next;
        int comp = tree->compare(elem, auxElem);

        if (comp == -1) {
            next = getKDNodeLeftChild(tree, aux);
            
            if (!next) {
                aux->left = newNode;
                break;
            }

        } else if (comp == 1) {
            next = getKDNodeRightChild(tree, aux);

            if (!next) {
                aux->right = newNode;
                break;
            }

        } else {
            return NULL;
        }

        aux = next;
    }

    return newNode;
}

kdTreeElem removeFromKDTree(kdTree tree, kdNode node) {
    if (!tree || !node) {
        return NULL;
    }

    kdTreeElem nodeElem = node->elem;

    kdNode left = getKDNodeLeftChild(tree, node);
    kdNode right = getKDNodeRightChild(tree, node);

    kdNode parent = getKDNodeParent(tree, node);
    kdNode parentLeftChild = getKDNodeLeftChild(tree, parent);

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
        kdNode rightmostNode = left;
        kdNode next;
        while ((next = getKDNodeRightChild(tree, rightmostNode))) {
            rightmostNode = next;
        }

        kdTreeElem newElem = removeFromKDTree(tree, rightmostNode);
        node->elem = newElem;

        return nodeElem;
    }

    kdNode aux;
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

kdTreeElem getElemInKDNode(kdTree tree, kdNode node) {
    if (!tree || !node) {
        return NULL;
    }
    
    return node->elem;
}

void destroyKDTree(kdTree tree) {
    if (!tree) {
        return;
    }

    if (!isEmptyKDTree(tree)) {
        printf("\n------------\n");
        printf("ATENCAO:\nO desalocamento de elementos da arvore nao e realizado automaticamente; caso seja necessario, modifique seu programa para realizar a remocao e desalocamento.\n");
    }

    while (!isEmptyKDTree(tree)) {
        removeFromKDTree(tree, getRootKDTree(tree));
    }

    free(tree);
}