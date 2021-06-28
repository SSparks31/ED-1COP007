#include "rectangle.h"

#include "../DataStructures/list.h"
#include "../util.h"
#include "stdlib.h"
#include "string.h"

typedef struct rectangle {
    int type;

    struct attributes_r {
        char id[50];
        struct colors {
            char stroke_color[50];
            char fill_color[50];
        } colors;
        unsigned int opacity;

        struct coordinates_r {
            double __x;
            double __y;
            double __w;
            double __h;

            struct center {
                double __x, __y;
            } center;

        } coordinates_r;

    } attributes_r;

    int kd_way;
    struct sheltered_stuff {
        void** sheltered_in;
        int number_of_sheltered;
    } sheltered_stuff;
} rectangle;

void* create_rect(char* id, double properties[], char colors[2][50]) {
    rectangle* rect = calloc(1, sizeof(rectangle));

    rect->type = 0;

    if (properties) {
        rect->attributes_r.coordinates_r.__x = properties[0];
        rect->attributes_r.coordinates_r.__y = properties[1];
        rect->attributes_r.coordinates_r.__w = properties[2];
        rect->attributes_r.coordinates_r.__h = properties[3];

        rect->attributes_r.coordinates_r.center.__x = (properties[2]) / 2 + properties[0];
        rect->attributes_r.coordinates_r.center.__y = (properties[3]) / 2 + properties[1];
    }

    rect->sheltered_stuff.sheltered_in = NULL;
    rect->sheltered_stuff.number_of_sheltered = 0;

    if (colors) {
        strcpy(rect->attributes_r.colors.stroke_color, colors[1]);
        strcpy(rect->attributes_r.colors.fill_color, colors[0]);
    }

    if (id)
        strcpy(rect->attributes_r.id, id);

    return rect ? rect : print_and_return_null("createRect: Erro ao criar um retangulo");
}

int insert_data_sheltered_in(void* __obj, void* __n) {
    rectangle* rectangle_ob = __obj;

    if (!rectangle_ob) return puts("insert___objheltered_in: Parametro vazio") - ERROR;

    rectangle_ob->sheltered_stuff.sheltered_in = realloc(rectangle_ob->sheltered_stuff.sheltered_in, (rectangle_ob->sheltered_stuff.number_of_sheltered + 2) * sizeof(void*));

    rectangle_ob->sheltered_stuff.sheltered_in[rectangle_ob->sheltered_stuff.number_of_sheltered] = __n;

    rectangle_ob->sheltered_stuff.sheltered_in[rectangle_ob->sheltered_stuff.number_of_sheltered + 1] = NULL;

    rectangle_ob->sheltered_stuff.number_of_sheltered++;

    return 1;
}

int free_rect(void* __obj) {
    rectangle* rectangle_ob = __obj;

    if (!rectangle_ob) return puts("free_data: Parametro invalido");

    if (rectangle_ob->sheltered_stuff.sheltered_in) {
        bites_zadasto(rectangle_ob);
        free(rectangle_ob->sheltered_stuff.sheltered_in);
    }

    return 1;
}

double get_center_x(void* __obj) {
    rectangle* rectangle_ob = __obj;

    return rectangle_ob ? rectangle_ob->attributes_r.coordinates_r.center.__x : (double)puts("get_center_x: Parametro Invalido");
}

double get_center_y(void* __obj) {
    rectangle* rectangle_ob = __obj;

    return rectangle_ob ? rectangle_ob->attributes_r.coordinates_r.center.__y : (double)puts("get_center_y: Parametro Invalido");
}

int bites_zadasto(void* __obj) {
    rectangle* data = __obj;
    int cont = -1;

    while (data->sheltered_stuff.sheltered_in[++cont]) {
        set_x_circ(get_sheltered_in(__obj, cont), get_center_x(__obj));
        set_y_circ(get_sheltered_in(__obj, cont), get_center_y(__obj));
        set_rectangle_near(get_sheltered_in(__obj, cont), NULL);
        data->sheltered_stuff.number_of_sheltered = 0;

        data->sheltered_stuff.number_of_sheltered = 0;
    }
    return 1;
}

double rect_x(void* __obj) {
    rectangle* data = __obj;

    return data ? data->attributes_r.coordinates_r.__x : 0;
}

double rect_y(void* __obj) {
    rectangle* data = __obj;

    return data ? data->attributes_r.coordinates_r.__y : 0;
}

double rect_w(void* __obj) {
    rectangle* data = __obj;

    return data ? data->attributes_r.coordinates_r.__w : 0;
}

double rect_h(void* __obj) {
    rectangle* data = __obj;

    return data->attributes_r.coordinates_r.__h;
}

int set_kd_rect(void* __obj, int __n) {
    
    rectangle* data = __obj;

    data->kd_way = __n;

    return 1;
}

int get_kd_rect(void* __obj) {
    rectangle* rect = __obj;

    return rect->kd_way;
}

char* get_id_rect(void* __obj) {
    rectangle* data = __obj;

    return data ? data->attributes_r.id : NULL;
}


char* get_rect_stroke_color(void* __obj) {
    rectangle* data = __obj;

    return data ? data->attributes_r.colors.stroke_color : 0;
}

void* get_sheltered_in(void* __obj, int __i) {
    rectangle* data = __obj;

    if (!data->sheltered_stuff.sheltered_in) return NULL;

    return data->sheltered_stuff.sheltered_in[__i];
}

char* get_rect_fill_color(void* __obj) {
    rectangle* data = __obj;

    return data ? data->attributes_r.colors.fill_color : 0;
}

int get_rect_number_sheltered(void* __obj) {
    rectangle* data = __obj;

    return data ? data->sheltered_stuff.number_of_sheltered : 0;
}

int compare_id_rect(void* rect1, void* rect2) {
    if (rect1 == rect2) return 0;
    if (!strcmp(get_id_rect(rect1), get_id_rect(rect2))) return 0;
    return 2;
}

int compare_id_rect_qsort(const void* rect1, const void* rect2) {
    const rectangle* um = rect1;
    const rectangle* dois = rect2;

    return strcmp(um->attributes_r.id, dois->attributes_r.id);
}

int compare_xy_rect(void* __obj1, void* __obj2) {
    if (get_kd_rect(__obj1)) {
        if (rect_x(__obj2) == rect_x(__obj1) && rect_y(__obj2) == rect_y(__obj1)) return 0;
        if (rect_x(__obj2) == rect_x(__obj1) && rect_y(__obj2) != rect_y(__obj1)) return 1;
        if (rect_x(__obj2) > rect_x(__obj1) && rect_y(__obj2) != rect_y(__obj1)) return 1;
        if (rect_x(__obj2) < rect_x(__obj1) && rect_y(__obj2) != rect_y(__obj1)) return -1;
    }

    else {
        if (rect_y(__obj2) == rect_y(__obj1) && rect_x(__obj2) == rect_x(__obj1)) return 0;
        if (rect_y(__obj2) == rect_y(__obj1) && rect_x(__obj2) != rect_x(__obj1)) return 1;
        if (rect_y(__obj2) > rect_y(__obj1) && rect_x(__obj2) != rect_x(__obj1)) return 1;
        if (rect_y(__obj2) < rect_y(__obj1) && rect_x(__obj2) != rect_x(__obj1)) return -1;
    }

    return 1;
}