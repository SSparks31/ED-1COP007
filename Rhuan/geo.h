#include "util.h"

#ifndef GEOFUNC_H
#define GEOFUNC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DataStructures/list.h"
#include "DataStructures/tree.h"
#include "GeometricForms/circle.h"
#include "controller.h"
#include "GeometricForms/rectangle.h"
#include "argvFunc.h"
/*Retorno padrão de erro para ponteiros: NULL */
/*Retorno padrão de erro para numericos: -1   */

/*
Le o arquivo .geo informado no terminal e executa as funcoes correspondentes.

Adiciona os retangulos lidos em 'rectangle_tree' e os círculos em 'circle_tree'

*/
Lista geo_processor(Endereco Paths, Controlador Controller, Arvore rectangle_tree, Arvore circle_tree);

/**/
#endif