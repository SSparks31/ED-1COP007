#include "util.h"

#ifndef CONTROLLER_R
#define CONTROLLER_R

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DataStructures/list.h"
#include "GeometricForms/circle.h"
#include "GeometricForms/rectangle.h"

/*Retorno padrão de erro para ponteiros: NULL */
/*Retorno padrão de erro para numericos: -1   */

typedef void* Controlador;

/*
Retorna o contrlador que indica se será feita a leitura de um .qry
*/
int get_exist_input_qry(Controlador Scont);

/*
Atualiza o contrlador que indica se será feita a leitura de um .qry
*/
int set_exist_input_qry(Controlador Scont, int newI);

/*
Retorna um controlador
*/
Controlador controller_factory();

/*
Libera a memória de um controlador
*/
int destroy_controller(Controlador Scont);

/*
Retorna uma lista com todos os meteoros que cairam
*/
Lista get_meteor_impact(Controlador __obj);

/*
Retorna uma lista com todos os pontos nve
*/
Lista nve_points(Controlador __obj);
/**/
#endif