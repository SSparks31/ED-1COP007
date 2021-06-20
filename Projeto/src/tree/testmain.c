#include "binarytree.h"

#include <stdio.h>

int compare(const binaryTreeElem a, const binaryTreeElem b) {
    int valA = *(int*) a;
    int valB = *(int*) b;

    if (valA < valB) {
        return -1;
    }
    if (valA > valB) {
        return 1;
    }

    return 0;
}

void printTree(binaryTree tree, binaryNode node) {
    if (!node) return;
    printf("At node containing %i;", *(int*) getElemInBinaryNode(tree, node));
    binaryNode left = getBinaryNodeLeftChild(tree, node);
    binaryNode right = getBinaryNodeRightChild(tree, node);
    if (left) {
        printf(" Left child contains %i;", *(int*) getElemInBinaryNode(tree, left));
    }
    if (right) {
        printf(" Right child contains %i;", *(int*) getElemInBinaryNode(tree, right));
    }

    printf("\n");
    printTree(tree, left);
    printTree(tree, right);
}


int main() {
    int a[16] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 16};

    binaryTree tree = createBinaryTree(compare);

    binaryNode b[16];

    for (int i = 0; i < 16; i++) {
        b[i] = appendBinaryTree(tree, a + i);
        printf("Node with %i is at %i height\n", a[i], getBinaryNodeHeight(tree, b[i]));
    }
    
    printTree(tree, getRootBinaryTree(tree));
    
    
    while (!isEmptyBinaryTree(tree)) {
        printf("Removing %i\n", *(int*) removeFromBinaryTree(tree, getRootBinaryTree(tree)));
    }

    destroyBinaryTree(tree);

    return 0;    
}