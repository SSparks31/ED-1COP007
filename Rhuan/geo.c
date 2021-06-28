#include "geo.h"

#include "DataStructures/list.h"
#include "DataStructures/tree.h"
#include "GeometricForms/circle.h"
#include "GeometricForms/rectangle.h"
#include "argvFunc.h"
#include "controller.h"
#include "qry.h"
#include "svg.h"
#include "util.h"


int geo_cc(FILE* geo_file, char coresAux[2][50]) {
    fscanf(geo_file, "%s", coresAux[STROKE]);
    if (!strcmp(coresAux[STROKE], "@"))
        strcpy(coresAux[STROKE], "rgba(0,0,0,0)");
}

int geo_cp(FILE* geo_file, char coresAux[2][50]) {
    fscanf(geo_file, "%s", coresAux[FILL]);
    if (!strcmp(coresAux[FILL], "@"))
        strcpy(coresAux[FILL], "rgba(0,0,0,0)");
}

int geo_r(FILE* geo_file, Arvore rectangle_tree, char coresAux[2][50], Controlador Controller) {
    void* retan;

    double properties[4];
    
    char id[100];

    fscanf(geo_file, "%s %lf %lf %lf %lf", id, &properties[X], &properties[Y], &properties[W], &properties[H]);

    insert_tree(rectangle_tree, create_rect(id, properties, coresAux), compare_xy_rect, set_kd_rect);
}

int geo_c(FILE* geo_file, Arvore circle_tree, char coreAux_circle[2][50], Controlador Controller) {
    char id[100];
    double properties[4];

    fscanf(geo_file, "%s %lf %lf %lf", id, &properties[X], &properties[Y], &properties[W]);
    
    insert_tree(circle_tree, create_circle(id, properties[X], properties[Y], properties[W], coreAux_circle), compare_xy_circ, set_kd_circ);
}

int geo_bc(FILE* geo_file, char coreAux_circle[2][50]) {
    fscanf(geo_file, "%s", coreAux_circle[1]);
    if (!strcmp(coreAux_circle[1], "@"))
        strcpy(coreAux_circle[1], "rgba(0,0,0,0)");
}

int geo_pc(FILE* geo_file, char coreAux_circle[2][50]) {
    fscanf(geo_file, "%s", coreAux_circle[0]);
    if (!strcmp(coreAux_circle[0], "@"))
        strcpy(coreAux_circle[0], "rgba(0,0,0,0)");
}

Lista geo_processor(Endereco Paths, Controlador Controller, Arvore rectangle_tree, Arvore circle_tree) {
    void* retan;
    int nx;
    char coresAux[2][50] = {"\0", "\0"}, function[3], coreAux_circle[2][50] = {"\0", "\0"};

    FILE* geo_file = fopen(get_input_geo_full_path(Paths), "r");

    if (!geo_file) {
        printf("--> \" %s \"\n", get_input_geo_full_path(Paths));
        return print_and_return_null("geo_processor: Erro ao abrir arquivo Geo");
    }

    fscanf(geo_file, "%s %d", function, &nx);

    while (fscanf(geo_file, "%s", function) != EOF) {
        if (!strcmp(function, "cc"))
            geo_cc(geo_file, coresAux);

        if (!strcmp(function, "cp"))
            geo_cp(geo_file, coresAux);

        if (!strcmp(function, "r"))
            geo_r(geo_file, rectangle_tree, coresAux, Controller);

        if (!strcmp(function, "bc"))
            geo_bc(geo_file, coreAux_circle);

        if (!strcmp(function, "pc"))
            geo_pc(geo_file, coreAux_circle);

        if (!strcmp(function, "c"))
            geo_c(geo_file, circle_tree, coreAux_circle, Controller);
    }

    fclose(geo_file);
    return NULL;
}