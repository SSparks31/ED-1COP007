#include <stdio.h>
#include <stdlib.h>

#include "../DataStructures/list.h"

#ifndef POLYGON_H
#define POLYGON_H

typedef void* Poligono;

/*
Constrói um poligono do tipo TYPE
*/
Poligono polygon_factory(const int __type);

/*
Retorna o número de segmentos em OBJ
*/
size_t n_segments(void* __obj);

/*
Adiciona uma cópia de SRC em OBJ
*/
void* add_segment(void* __obj, void* __src);

/*
Exclui um poligono
*/
int destroy_polygon(Poligono __obj);

/*
Exclui uma lista de poligonos
*/
void destroy_polygon_list(Lista __obj);

/*
Retorna o __index segmendo adicionado no poligono
*/
void* segment_index(Poligono __obj, int __index);

/*
Função compare para inserção em árvore 
*/
int compare_xy_polygon(void* __obj1, void* __obj2);

/*
Insere __dp como novo sentido de comparação kd
*/
int set_kd_poly(void* __obj, int __dp);

/*
Retorna o sentido de comparação kd
*/
int get_kd_poly(void* __obj); 

/*
Retorna o X do minimo retangulo envolvente
*/
double get_x_rect_poly(void* __poly);

/*
Retorna o Y do minimo retangulo envolvente
*/
double get_y_rect_poly(void* __poly);

/**/
#endif