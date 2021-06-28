#include "meteor.h"
#include "DataStructures/tree.h"
#include "util.h"

typedef struct meteor {    
    /*
    Ponto de queda do meteoro
    */
    Vertice __fall_point;

    /*
    Radiação do meteoro
    */
    double radiation;

    /*
    Poligono de visibilidade
    */
    Poligono __visibility_polygon;

    /*
    Lista que armazena os poligonos de sombra
    */
    Arvore __shadow_polygons;

} meteor;

char* color_by_rad(Meteoro __meteor) {
    if (meteor_radiation(__meteor) < 25) return "#00ffff";

    if (meteor_radiation(__meteor) < 50) return "#00ff00";

    if (meteor_radiation(__meteor) < 100) return "#ff00ff";

    if (meteor_radiation(__meteor) < 250) return "#0000ff";

    if (meteor_radiation(__meteor) < 600) return "#800080";

    if (meteor_radiation(__meteor) < 1000) return "#000080";

    if (meteor_radiation(__meteor) < 8000) return "#ff0000";

    return "#000000";
}

double meteor_radiation(Meteoro __meteor) {
    return __meteor ? ((meteor*)__meteor)->radiation : -1;
}

void destroy_meteor_polygons(Meteoro __meteor) {
    destroy_polygon(((meteor*)__meteor)->__visibility_polygon);
    destroy_tree(((meteor*)__meteor)->__shadow_polygons, destroy_polygon, 1);
}

void destroy_meteor(Meteoro __meteor) {
    destroy_meteor_polygons(__meteor);
    free(((meteor*)__meteor)->__fall_point);
    free(__meteor);
}

Meteoro meteor_factory(double __rad) {
    meteor* out = calloc(1, sizeof(meteor));

    out->__fall_point = NULL;
    out->radiation = __rad;
    out->__shadow_polygons = tree_factory(kd, 2);
    out->__visibility_polygon = NULL;

    return out;
}

Vertice fall_point(Meteoro __meteor) {
    return __meteor ? ((meteor*)__meteor)->__fall_point : NULL;
}

void set_fall_point(Meteoro __meteor, Vertice __new) {
    ((meteor*)__meteor)->__fall_point = __new;
}

Poligono visibility_polygon(Meteoro __meteor) {
    return __meteor ? ((meteor*)__meteor)->__visibility_polygon : NULL;
}

void set_visibility_polygon(Meteoro __meteor, Poligono __new) {
    ((meteor*)__meteor)->__visibility_polygon = __new;
}

Arvore shadow_polygons(Meteoro __meteor) {
    return __meteor ? ((meteor*)__meteor)->__shadow_polygons : NULL;
}

void insert_shadow_polygon(Meteoro __meteor, Poligono __new) {
    insert_tree(((meteor*)__meteor)->__shadow_polygons, __new, compare_xy_polygon, set_kd_poly);
}