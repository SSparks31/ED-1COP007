#include "util.h"

#ifndef RETFUNC_H
#define RETFUNC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DataStructures/tree.h"
#include "GeometricForms/circle.h"
#include "GeometricForms/rectangle.h"
#include "controller.h"
/*Retorno padrão de erro para ponteiros: NULL */
/*Retorno padrão de erro para numericos: -1   */

/*Retorna 1 se ret1 se sobrepoe a ret2, 0 caso não sobreponha*/
int RET_sobreposto(double x1, double y1, double l1, double w1, double x2, double y2, double l2, double w2);
/*Retorna 1 se p(px,py) está contido ret(x,y,w,h), 0 caso não esteja*/
int RET_ponto_interno(double px, double py, double x, double y, double l, double w);
/*Retorna 1 se ret2(x2,y2,w2,h2) está contido em ret1(x1,y1,w2,h1), 0 caso não esteja*/
int RET_esta_contido(double x1, double y1, double l1, double w1, double x2, double y2, double l2, double w2);
/*Escreve text no arquivo __file com formatação de .svg*/
void print_text_svg(FILE *__file, int size, char* color, char *text, double x, double y);
/*Escreve as cores no arquivo __file com formatação de .svg*/
void print_colors_svg(FILE *file, char *fill_color, char *stroke_color);
/*Escreve o .svg*/
int svg_maker(FILE* full_path, Controlador controller, Arvore __ct, Arvore __rt);


/**/
#endif