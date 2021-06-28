
#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <stdio.h>
#include "GeometricForms/circle.h"
#include "GeometricForms/rectangle.h"

enum data_type1 { X,
                  Y,
                  W,
                  H };

enum data_type2 { FILL,
                  STROKE };



/*
Valor subtraido de algum puts de erro para que o retorno fique negativo.

OBS: puts retorna o tamanho da string
*/
#define ERROR 60

/*
Usado ao fim de uma função para informar que houve sucesso
*/
#define SUCCESS return(1)

#define DIREITA 1

#define ESQUERDA -1

#define IGUAL 0

#define distancia(x1, y1, x2, y2) sqrt(pow(fabs(x2 - x1), 2) + pow(fabs(y2 - y1), 2))

enum{
    CIRCULO,
    RETANGULO,
    SEGMENTO,
    TRIANGULO
};

enum {
    kd,
    busca
};

int placebo2(void* a, const int b);

int placebo1(void* a);

typedef void** Tree_Array;

typedef int (**Functions_Array)(FILE *, double,  void *);

typedef char* String;

/*
Printa message e pula uma linha

retorna NULL
*/
void* print_and_return_null(String message);


/*
Semelhante a funcao strtok da string.h, porem nao altera o endereço de 'string'
*/
String MY_strtok(String string, char flag);

/*
Separa o nome de um arquivo do path
*/
char *separaArq(char *path);


void **compact_trees(void* rectangle, void* circle);


Functions_Array compact_functions(int (*print_circle_tree_svg)(FILE *, double, void *),int (*print_rectangle_tree_svg)(FILE *, double, void *));
/**/
#endif