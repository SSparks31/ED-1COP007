#include "qry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"

#include "list.h"
#include "queue.h"

void inp(FILE* qry_file, List shapes, Queue pol_queue) {
    int id;
    fscanf(qry_file, " %d\n", &id);

    List_pos aux = list_get_first(shapes);
    while (aux) {
        Shape shape = list_get_elem(aux);
        if (shape_get_id(shape) == id) {
            break;
        }
    }
    if (!aux) {
        return;
    }

    Shape anchor;

    switch (shape_get_type(shape)) {
    case SVG_CIRCLE:
        anchor = point_create(0, shape_get_coordinates(shape)[0], shape_get_coordinates(shape)[1]);
        break;
        
    case SVG_RECTANGLE:
        anchor = point_create(0, shape_get_coordinates(shape)[0], shape_get_coordinates(shape)[1]);
        break;

    case SVG_LINE:
        double coordinates[4] = shape_get_coordinates(shape);
        double x1 = coordinates[0],
        y1 = coordinates[1],
        x2 = coordinates[2],
        y2 = coordinates[3];
        
        int which;

        if (x1 == x2) {
            if (y1 < y2) {
                which = 1;
            } else {
                which = 2
            }
        } else if (x1 < x2) {
            which = 1;
        } else {
            which = 2;
        }

        if (which == 1) {
            anchor = point_create(0, x1, y1);
        } else {
            anchor = point_create(0, x2, y2);
        }

        break;

    case SVG_TEXT:
        anchor = point_create(0, shape_get_coordinates(shape)[0], shape_get_coordinates(shape)[1]);
        break;
    }

    queue_insert(pol_queue, point);
}

void rmp() {

}

void pol() {

}

void clp() {

}

void sel() {

}

void selplus() {

}

void dels() {

}

void dps() {

}

void ups() {

}

void qry_parser(char* BED, char* BSD, char* geo_name, char* qry_name, List shapes) {    
    if (!qry_name || strlen(qry_name) == 0) {
        return;
    }

    char* qry_path = calloc(1, strlen(BED) + 1 + strlen(qry_name) + 1);
    if (BED[strlen(BED)-1] != '/') {
        sprintf(qry_path, "%s/%s", BED, qry_name);
    } else {
        sprintf(qry_path, "%s%s", BED, qry_name);
    }

    FILE* qry_file = fopen(qry_path, "r");
    if (!qry_file) {
        return;
    }

    if (strrchr(geo_name, '/')) {
        geo_name = strrchr(geo_name, '/') + 1;
    }
    qry_name = strrchr(qry_path, '/') + 1;
    *strrchr(geo_name, '.') = '\0';
    *strrchr(qry_name, '.') = '\0';

    char* svg_path = calloc(1, strlen(BSD) + 1 + strlen(geo_name) + 1 + strlen(qry_name) + 1);
    char* txt_path = calloc(1, strlen(BSD) + 1 + strlen(geo_name) + 1 + strlen(qry_name) + 1);

    if (BSD[strlen(BSD)-1] != '/') {
        sprintf(svg_path, "%s/%s-%s.svg", BSD, geo_name, qry_name);
    } else {
        sprintf(svg_path, "%s%s-%s.svg", BSD, geo_name, qry_name);
    }

    strncpy(txt_path, svg_path, strlen(svg_path) - 3);
    strcat(txt_path, "txt");
    
    FILE* svg_file = fopen(svg_path, "w");
    FILE* txt_file = fopen(txt_path, "w");
    free(svg_path);    
    free(txt_path);    
    
    char command[999];
    while (fscanf(qry_file, "%s", command) != EOF) {
        printf("%s\n", command);
        fgets(command, 999, qry_file);
        if (strcmp(command, "inp") == 0) {
            inp();
        } else if (strcmp(command, "rmp") == 0) {
            rmp();
        } else if (strcmp(command, "pol") == 0) {
            pol();
        } else if (strcmp(command, "clp") == 0) {
            clp();
        } else if (strcmp(command, "sel") == 0) {
            sel();
        } else if (strcmp(command, "sel+") == 0) {
            selplus();
        } else if (strcmp(command, "dels") == 0) {
            dels();
        } else if (strcmp(command, "dps") == 0) {
            dps();
        } else if (strcmp(command, "ups") == 0) {
            ups();
        } else {

        }
    }
    return;
}