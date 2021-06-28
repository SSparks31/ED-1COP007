#include "util.h"
#ifndef QRYFUNC_H
#define QRYFUNC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DataStructures/list.h"
#include "DataStructures/tree.h"
#include "GeometricForms/circle.h"
#include "GeometricForms/rectangle.h"
#include "controller.h"
/*Retorno padrão de erro para ponteiros: NULL */
/*Retorno padrão de erro para numericos: -1   */

/*Faz a leitura do arquivo qry e gerencia as funções*/
int qry_processor(Lista Stlist, void *Paths, Controlador controller, Arvore st_circle_tree, Arvore st_rectangle_tree);

/**/
#endif