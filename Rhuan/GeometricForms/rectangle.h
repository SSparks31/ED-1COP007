#include "../util.h"
#include "../DataStructures/list.h"


#ifndef RECTANGLE_H
#define RECTANGLE_H

#define sizeofRectangle 208

typedef void* Retangulo;


/*
Cria um retangulo
*/
Retangulo create_rect(char* __id, double __prop[], char __center[2][50]);

/*
Insere um circulo no retangulo
*/
int insert_data_sheltered_in(Retangulo __obj, void* __n);

/*
Libera a memoria de um retangulo
*/
int free_rect(Retangulo __obj);

/*
Retorna o x de centro do retangulo
*/
double get_center_x(Retangulo __obj);

/*
Retorna o y de centro do retangulo
*/
double get_center_y(Retangulo __obj);

/*
Libera a memoria dos itens de um retangulo
*/
int bites_zadasto(Retangulo __obj);

/*
Retorna o x do retangulo
*/
double rect_x(Retangulo __obj);

/*
Retorna o y do retangulo
*/
double rect_y(Retangulo __obj);

/*
Retorna o w do retangulo
*/
double rect_w(Retangulo __obj);

/*
Retorna o y do retangulo
*/
double rect_h(Retangulo __obj);

/*
Seta o sentido kd do retangulo
*/
int set_kd_rect(Retangulo __obj, int __n);

/*Comparadores*/
int compare_xy_rect(Retangulo __obj1, Retangulo __obj2);
int compare_id_rect(Retangulo __obj1, Retangulo __obj2);
int compare_id_rect_qsort(const void* rect1, const void* rect2);

/*
Getters
*/
int get_kd_rect(Retangulo __obj);
char* get_id_rect(Retangulo __obj);
char* get_rect_fill_color(Retangulo __obj);
void* get_sheltered_in(void* __obj, int __ind);
char* get_rect_stroke_color(Retangulo __obj);
int get_rect_number_sheltered(Retangulo __obj);

/**/
#endif