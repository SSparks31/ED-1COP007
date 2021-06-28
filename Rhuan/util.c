#include "util.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DataStructures/tree.h"
#include "GeometricForms/circle.h"
#include "GeometricForms/rectangle.h"
#include "controller.h"

int placebo2(void *a, const int b) {
    return 1;
}

int placebo1(void *a) {
    return 1;
}

String MY_strtok(String string, char flag) {
    String ret = calloc(1 + strlen(string), sizeof(char));
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == flag)
            break;
        ret[i] = string[i];
    }
    return ret;
}

void *print_and_return_null(String message) {
    printf("%s\n", message);
    return NULL;
}

char *separaArq(char *path) {
    if (!path) return print_and_return_null("separaArq:\t\tParametro vazio");

    char *output = calloc(strlen(path) + 10, 1);
    int letra_output = 0, last = 0, um = 1, contador;

    for (contador = 0; contador < strlen(path); contador++)
        if (path[contador] == '/')
            last = contador;

    if (!last) um = 0;

    for (contador = last + um; contador < strlen(path); contador++)
        output[letra_output++] = path[contador];

    return output;
}

Functions_Array compact_functions(int (*print_circle_tree_svg)(FILE *, double, void *), int (*print_rectangle_tree_svg)(FILE *, double, void *)) {
    Functions_Array compacted_function_tree_for_svg = calloc(3, sizeof(int *));
    compacted_function_tree_for_svg[0] = print_circle_tree_svg;
    compacted_function_tree_for_svg[1] = print_rectangle_tree_svg;
    return compacted_function_tree_for_svg;
}

void **compact_trees(void *rectangle, void *circle) {
    void **compacted_trees_for_svg = calloc(3, sizeof(void *));

    compacted_trees_for_svg[0] = rectangle;

    compacted_trees_for_svg[1] = circle;

    return compacted_trees_for_svg;
}
