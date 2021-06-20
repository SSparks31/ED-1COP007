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
    
    int dimensions;
    int numElements;

    int (*compare)(const kdTreeElem a, const kdTreeElem b, int j);
};

int findHeightKDTree(kdTree tree, kdNode node);

kdNode recursiveFindKDNode(kdTree tree, kdNode node, kdTreeElem elem);

kdNode recursiveKDCustomSearch(kdTree tree, kdNode candidate, void* elem, int (*compare) (const kdTreeElem a, const void* b));

kdNode recursiveFindKDNodeParent(kdTree tree, kdNode node, kdNode parentCandidate);

kdNode findMinimumDimensionInSubtree(kdTree tree, kdNode node, int j);

kdTree createKDTree(int k, int (*compare)(const kdTreeElem a, const kdTreeElem b, int j)) {
    if (k <= 0 || !compare) {
        return NULL;
    }
    
    kdTree tree = malloc(sizeof(struct kdTree));
    if (!tree) {
        return NULL;
    }

    tree->root = NULL;

    tree->dimensions = k;
    tree->numElements = 0;

    tree->compare = compare;

    return tree;
}

int getDimensionsKDTree(kdTree tree) {
    if (!tree) {
        return -1;
    }
    
    return tree->dimensions;
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

    return imax(1 + leftHeight, 1 + rightHeight);
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

kdNode findKDNodeInTree(kdTree tree, kdTreeElem elem) {
    if (!tree || !elem) {
        return NULL;
    }

    kdNode aux = getRootKDTree(tree);
    int height = 1;
    if (!aux) {
        return NULL;
    }

    while (aux) {
        kdTreeElem auxElem = getElemInKDNode(tree, aux);
        if (auxElem == elem) {
            return aux;
        }

        if (tree->compare(elem, auxElem, height) == -1) {
            aux = getKDNodeLeftChild(tree, aux);
        } else {
            aux = getKDNodeRightChild(tree, aux);
        }

        height = (height + 1) % getDimensionsKDTree(tree);
    }

    return NULL;
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
        
        tree->numElements++;
        return newNode;
    }

    kdNode next;

    for (int height = 1; aux; height = (height + 1) % getDimensionsKDTree(tree)) {
        kdTreeElem auxElem = getElemInKDNode(tree, aux);
        if (tree->compare(elem, auxElem, height) == -1) {
            next = getKDNodeLeftChild(tree, aux);
            
            if (!next) {
                aux->left = newNode;
                break;
            }
        } else {
            next = getKDNodeRightChild(tree, aux);

            if (!next) {
                aux->right = newNode;
                break;
            }
        }
        
        aux = next;
    }

    tree->numElements++;
    return newNode;
}

kdNode findMinimumDimensionInSubtree(kdTree tree, kdNode node, int j) {
    if (!node) {
        return NULL;
    }

    kdNode bestNode = node;
    kdTreeElem bestElem = getElemInKDNode(tree, bestNode);
    kdNode leftBestNode = findMinimumDimensionInSubtree(tree, getKDNodeLeftChild(tree, node), j);
    kdNode rightBestNode = findMinimumDimensionInSubtree(tree, getKDNodeRightChild(tree, node), j);

    if (leftBestNode) {
        kdTreeElem leftElem = getElemInKDNode(tree, leftBestNode);

        if (tree->compare(bestElem, leftElem, j) != -1) {
            bestNode = leftBestNode;
            bestElem = leftElem;
        }
    }

    if (rightBestNode) {
        kdTreeElem rightElem = getElemInKDNode(tree, rightBestNode);

        if (tree->compare(bestElem, rightElem, j) != -1) {
            bestNode = rightBestNode;
            bestElem = rightElem;
        }
    }

    return bestNode;
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
    
    int height = getKDNodeHeight(tree, node) % getDimensionsKDTree(tree);
    kdNode minDimension;
    
    if (right) {
        minDimension = findMinimumDimensionInSubtree(tree, right, height);
        node->elem = minDimension->elem;
        removeFromKDTree(tree, minDimension);
    } else {
        minDimension = findMinimumDimensionInSubtree(tree, left, height);
        node->elem = minDimension->elem;
        removeFromKDTree(tree, minDimension);
        node->right = node->left;
        node->left = NULL;
    }

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