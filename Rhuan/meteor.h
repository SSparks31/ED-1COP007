#include "GeometricForms/polygon.h"
#include "GeometricForms/segment.h"

#ifndef METEOR_H
#define METEOR_H

typedef void* Meteoro;

/*
Retorna uma estrutura de meteora vazia
*/
Meteoro meteor_factory(double __rad);

/*
Retorna um vertice com as coordenadas da queda de OBJ
*/
Vertice fall_point(Meteoro __obj);

/*
Insere o vertice NEW com as coordenadas de queda de OBJ 
*/
void set_fall_point(Meteoro __obj, Vertice __new);

/*
Retorna o poligono da região de visibilidade de OBJ
*/
Poligono visibility_polygon(Meteoro __obj);

/*
Insere o poligono da região de visibilidade NEW em OBJ
*/
void set_visibility_polygon(Meteoro __obj, Poligono __new);

/*
Retorna uma lista com os poligonos de sombra de OBJ
*/
Lista shadow_polygons(Meteoro __obj);

/*
Insere o poligono de sombra NEW em OBJ
*/
void insert_shadow_polygon(Meteoro __obj, Poligono __new);


/*
Destrói os poligonos de um meteoro
*/
void destroy_meteor_polygons(Meteoro __obj);

/*
Retorna a radiação de um meteoro
*/
double meteor_radiation(Meteoro __meteor);


/*
Retorna uma cor de acordo com a radiação de __obj
*/
char* color_by_rad(Meteoro __obj);


/*
Destrói o meteoro
*/
void destroy_meteor(Meteoro __obj);

/**/
#endif