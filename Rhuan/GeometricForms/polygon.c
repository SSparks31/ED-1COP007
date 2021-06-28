#include "polygon.h"

#include <stdio.h>
#include <stdlib.h>

#include "../DataStructures/list.h"
#include "../DataStructures/tree.h"
#include "../geometry.h"
#include "../util.h"
#include "segment.h"

typedef struct polygon {

    unsigned int kd_way;

    int __type;

    size_t __n_segments;

    void** __segments;

    struct rectangle {
        double __x, __y;
    } rectangle;

} polygon;

double get_x_rect_poly(void* __poly){
    return ((polygon*)__poly)->rectangle.__x;
}

double get_y_rect_poly(void* __poly){
    return ((polygon*)__poly)->rectangle.__y;
}

int compare_xy_polygon(void* __obj1, void* __obj2) {
    polygon *__poly1 = __obj1, *__poly2 = __obj2;

    if (!__poly1->kd_way) {
        if (__poly2->rectangle.__x == __poly1->rectangle.__x && __poly2->rectangle.__y == __poly1->rectangle.__y) return 0;
        if (__poly2->rectangle.__x >= __poly1->rectangle.__x) return 1;
        if (__poly2->rectangle.__x < __poly1->rectangle.__x) return -1;
    }

    else {
        if (__poly2->rectangle.__y == __poly1->rectangle.__y && __poly2->rectangle.__x == __poly1->rectangle.__x) return 0;
        if (__poly2->rectangle.__y >= __poly1->rectangle.__y) return 1;
        if (__poly2->rectangle.__y < __poly1->rectangle.__y) return -1;
    }

    return 2;
}

int get_kd_poly(void* __obj){
    return ((polygon*)__obj)->kd_way;
}

int set_kd_poly(void* __obj, int __dp) {
    polygon* __poly = __obj;
    __poly->kd_way = __dp;
    return 1;
}

int destroy_polygon(Poligono __obj) {
    polygon* fri = __obj;

    if (!__obj) return 0;

    for (int cont = 0; cont < fri->__n_segments; cont++) {
        destroy_segment(fri->__segments[cont]);
    }
    free(fri->__segments);
}

void destroy_polygon_list(Lista __obj) {
    if (!__obj) return;
    for (Celula aux = getFirst(__obj); aux; aux = getNext(__obj, aux)) {
        destroy_polygon(get(aux));
    }
    freeList(__obj, 0, free);
}

void* polygon_factory(const int __type) {
    polygon* out = calloc(1, sizeof(polygon));

    out->__n_segments = 0;

    out->__segments = calloc(1, sizeofSeg);

    out->__type = __type;

    out->rectangle.__x = out->rectangle.__y = 9999999;

    return out;
}

size_t n_segments(void* __obj) {
    polygon* __poly = __obj;
    return __poly ? __poly->__n_segments : -1;
}

void* add_segment(void* __obj, void* __src) {
    polygon* __poly = __obj;

    __poly->__segments = realloc(__poly->__segments, sizeofSeg * (n_segments(__poly) + 2));

    __poly->__segments[n_segments(__poly)] = (__src);

    __poly->__n_segments++;

    if (point(ini_point(__src))[0] < __poly->rectangle.__x) __poly->rectangle.__x = point(ini_point(__src))[0];

    if (point(end_point(__src))[0] < __poly->rectangle.__x) __poly->rectangle.__x = point(end_point(__src))[0];
    
    if (point(ini_point(__src))[1] < __poly->rectangle.__y) __poly->rectangle.__y = point(ini_point(__src))[1];

    if (point(end_point(__src))[1] < __poly->rectangle.__y) __poly->rectangle.__y = point(end_point(__src))[1];

    return __poly->__segments[n_segments(__poly) - 1];
}

void* segment_index(Poligono __obj, int __index) {
    return __obj && ((polygon*)__obj)->__segments ? ((polygon*)__obj)->__segments[__index] : NULL;
}