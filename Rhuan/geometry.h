#include <stdio.h>

#include "GeometricForms/polygon.h"
#include "GeometricForms/segment.h"
#include "meteor.h"

#ifndef GEOMETRY_H
#define GEOMETRY_H


/*
Retorna 1 se point é interna ao retangulo st_data
*/
int inside_of(void* point, void* st_data, int visibility);

/*
Retorna 1 se o retangulo st_ret1 contém o retangulo st_ret2
*/
int rectangle_contain(void* st_ret1, void* st_ret2, int visibility);

/*
Retorna a equação da reta formada pelos pontos
*/
double* straight_equation(double point_1[2], double point_2[2]);

/*
Retorna o coeficiente angulas de point_1 em relação há point_2
*/
double slope(const double point_1[2], const double point_2[2]);

/*
Retorna o ponto de intersecção entre os dois segmentos
*/
double* intersec(Segmento __seg1, Segmento __seg2);

/*
Retorna o quadrante de point em relação há center
*/
int quadrant(double* center, const double point[2]);

/*
Estende q equação da reta x unidades e retorna o ponto 
*/
double* extend(double __equation[3], double x);

/*
Retorna 1 se __vtx está dentre de __plg
*/
int inside_of_polygon(Vertice __vtx, Poligono __plg, Meteoro __mtr);

/**/
#endif