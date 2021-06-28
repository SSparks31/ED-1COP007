#include "../util.h"
#include "rectangle.h"

#ifndef CIRCLE_H
#define CIRCLE_H

typedef void* Circulo;

/*
Retorna o retangulo que abriga __obj
*/
Retangulo get_rectagle_near(Circulo __obj);

/*
Retorna o y original 
*/
double get_original_y_circ(void* __obj);

/*
Retorna o x original 
*/
double get_original_x_circ(void* __obj);

/*
Retorna o x de __obj 
*/
double get_x_circ(Circulo __obj);

/*
Retorna o y de __obj 
*/
double get_y_circ(Circulo __obj);

/*
Retorna o id de __obj 
*/
char* get_id_circ(Circulo __obj);

/*
Seta __obj como morto 
*/
void kill(Circulo __obj);

/*
Retorna o raio de __obj
*/
double get_radius(Circulo __obj);

/*
Retorna o sentido de comparação kd
*/
int get_kd_way(Circulo __obj);

/*
Insere new como novo sentido de comparação kd
*/
int set_kd_circ(Circulo __obj, int new);

/*
Cria um circulo com os seguintes atributos
*/
Circulo create_circle(char* __id, double __x, double __y, double __radius, char __colors[2][50]);

/*
Retorna a cor do stroke de __obj
*/
char* get_circle_stroke_color(Circulo __obj);

/*
Retorna a cor do fill de __obj
*/
char* get_circle_fill_color(Circulo __obj);

/*
Seta um novo retangulo __new que contem __obj
*/
int set_rectangle_near(Circulo __obj,void* __new);

/*
Desvincula __obj do retangulo que o contém
*/
int reset_shelt_circ(Circulo __obj);

/*
Seta o x de __obj
*/
int set_x_circ(Circulo __obj, double __new);

/*
Seta o y de __obj
*/
int set_y_circ(Circulo __obj, double __new);

/*
Compare usada para percorrer a arvore
*/
int compare_xy_circ(Circulo __obj1, Circulo __obj2);

/*
Incrementa a radiação em __obj
*/
void set_circ_radiation(Circulo __obj, double __new);

/*
Retorna a radiação em __obj
*/
double circ_radiation(Circulo __obj);

/*
Retorna 1 caso esteja vivo e 0 caso não
*/
int alive(Circulo __obj);

/*
Seta as cores de __obj
*/
void set_circ_colors(Circulo __obj, char* __fill, char* __stroke);


/**/
#endif