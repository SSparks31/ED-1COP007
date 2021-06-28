#include "circle.h"

#include <stdlib.h>
#include <string.h>

#include "../util.h"

typedef struct circle {
    unsigned int kd_way;
    void* rectangle_near;
    int type;

    struct attributes {
        char id[50];
        double __radius;

        struct colors {
            char stroke_color[50];
            char fill_color[50];
        } colors;

        struct coordinates {
            double __x;
            double __y;
        } coordinates;

    } attributes;

    struct im_stuff {
        double radiation;
        unsigned int dead_alive;
    } im_stuff;

} circle;

void set_circ_radiation(Circulo __obj, double __new) {
    ((circle*)__obj)->im_stuff.radiation += __new;
}

double circ_radiation(Circulo __obj) {
    return __obj ? ((circle*)__obj)->im_stuff.radiation : -1;
}

void kill(Circulo __obj) {
    circle* __cir = __obj;
    __cir->im_stuff.dead_alive = 0;
    strcpy(__cir->attributes.colors.stroke_color, "#000000");
    strcpy(__cir->attributes.colors.fill_color, "#000000");
}

int alive(Circulo __obj) {
    return __obj ? ((circle*)__obj)->im_stuff.dead_alive : -1;
}

int set_x_circ(void* __obj, double __new) {
    circle* __circ = __obj;
    if (__circ->attributes.coordinates.__x == __new) return 0;

    __circ->attributes.coordinates.__x = __new;

    return 1;
}

int set_y_circ(void* __obj, double __new) {
    circle* __circ = __obj;
    if (__circ->attributes.coordinates.__y == __new) return 0;

    __circ->attributes.coordinates.__y = __new;

    return 1;
}

int reset_shelt_circ(void* __obj) {
    void* __o = get_rectagle_near(__obj);

    set_rectangle_near(__obj, NULL);

    return 1;
}

int set_rectangle_near(void* __obj, void* __new) {
    circle* circ = __obj;

    circ->rectangle_near = __new;

    return sizeof(*(__new));
}

void* get_rectagle_near(void* __obj) {
    circle* circle_ob = __obj;

    return circle_ob ? circle_ob->rectangle_near : print_and_return_null("get_rectagle_near: Parametro invalido");
}

double get_original_x_circ(void* __obj) {
    circle* data = __obj;

    return data ? data->attributes.coordinates.__x : 0;
}

double get_original_y_circ(void* __obj) {
    circle* data = __obj;

    return data ? data->attributes.coordinates.__y : 0;
}

double get_x_circ(void* __obj) {
    circle* data = __obj;

    if (data->rectangle_near) return get_center_x(data->rectangle_near);

    return data ? data->attributes.coordinates.__x : 0;
}

char* get_id_circ(void* __obj) {
    circle* data = __obj;

    return data ? data->attributes.id : NULL;
}

double get_y_circ(void* __obj) {
    circle* data = __obj;

    if (data->rectangle_near) return get_center_y(data->rectangle_near);

    return data ? data->attributes.coordinates.__y : 0;
}

double get_radius(void* __obj) {
    circle* data = __obj;

    return data ? data->attributes.__radius : 0;
}

int set_kd_circ(void* data_s, int new) {
    circle* data = data_s;

    data->kd_way = new;
    return 1;
}

int get_kd_circ(void* data_s) {
    circle* circle = data_s;

    return circle->kd_way;
}

void* create_circle(char* __id, double __x, double __y, double __radius, char __colors[2][50]) {
    circle* output = calloc(1, sizeof(circle));

    output->type = 1;

    if (__radius) output->attributes.__radius = __radius;
    if (__x) output->attributes.coordinates.__x = __x;
    if (__y) output->attributes.coordinates.__y = __y;
    if (__id) strcpy(output->attributes.id, __id);

    output->rectangle_near = NULL;

    output->im_stuff.radiation = 0;
    output->im_stuff.dead_alive = 1;

    if (__colors) {
        strcpy(output->attributes.colors.fill_color, __colors[0]);
        strcpy(output->attributes.colors.stroke_color, __colors[1]);
    }

    return output ? output : print_and_return_null("create_circle: Erro ao criar um circulo");
}

void set_circ_colors(Circulo __obj, char* __fill, char* __stroke) {
    strcpy(((circle*)__obj)->attributes.colors.fill_color, __fill);
    strcpy(((circle*)__obj)->attributes.colors.stroke_color, __stroke);
}

char* get_circle_stroke_color(void* __obj) {
    circle* data = __obj;

    return data ? data->attributes.colors.stroke_color : 0;
}

char* get_circle_fill_color(void* __obj) {
    circle* data = __obj;

    return data ? data->attributes.colors.fill_color : 0;
}

int compare_xy_circ(void* __obj1, void* __obj2) {

    if (!get_kd_circ(__obj1)) {
        if (get_x_circ(__obj2) == get_x_circ(__obj1) && get_y_circ(__obj2) == get_y_circ(__obj1)) return 0;
        if (get_x_circ(__obj2) >= get_x_circ(__obj1)) return 1;
        if (get_x_circ(__obj2) < get_x_circ(__obj1)) return -1;
    }

    else {
        if (get_y_circ(__obj2) == get_y_circ(__obj1) && get_x_circ(__obj2) == get_x_circ(__obj1)) return 0;
        if (get_y_circ(__obj2) >= get_y_circ(__obj1)) return 1;
        if (get_y_circ(__obj2) < get_y_circ(__obj1)) return -1;
    }

    return 2;
}