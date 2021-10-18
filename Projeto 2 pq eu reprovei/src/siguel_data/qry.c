#include "qry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/pathHelp.h"

#include "../svg/circle.h"
#include "../svg/line.h"
#include "../svg/rectangle.h"
#include "../svg/text.h"
#include "../svg/shape.h"

void o();

void i();

void pnt();

void delf(FILE* qry_file, List shapes) {
    char id_to_remove[999];
    fscanf(qry_file, "%s\n", id_to_remove);

    List_pos aux = list_get_first(shapes);
    while (aux) {
        Generic_shape shape = list_get_elem(shapes, aux);
        if (strcmp(generic_shape_get_id(shape), id_to_remove) == 0) {
            break;
        }

        aux = list_get_next(shapes, aux);
    }
        
    if (aux) {
        printf("Removing shape with id %s\n", id_to_remove);
        list_remove(shapes, aux);
    }
}

void qry_parser(char* BED, char* BSD, char* geo_name, char* qry_name, List shapes) {
    char* qry_path = concatPathFile(BED, qry_name);
    FILE* qry_file = fopen(qry_path, "r");
    
    char* geo_no_suffix = stripSuffix(geo_name);
    char* qry_no_suffix = stripSuffix(qry_name);
    char* geo_qry = malloc(strlen(geo_no_suffix) + strlen("-") + strlen(qry_no_suffix) + 1);
    sprintf(geo_qry, "%s-%s", geo_no_suffix, qry_no_suffix);
       
    char* svg_txt_path = concatPathFile(BSD, geo_qry);
    char* svg_path = concatFileSuffix(svg_txt_path, "svg");
    char* txt_path = concatFileSuffix(svg_txt_path, "txt");
    
    FILE* svg_file = fopen(svg_path, "w");
    FILE* txt_file = fopen(txt_path, "w");

    free(qry_path);
    free(geo_no_suffix);
    free(qry_no_suffix);
    free(geo_qry);
    free(svg_txt_path);
    free(svg_path);
    free(txt_path);

    char command[5];
    while (fscanf(qry_file, "%s", command) != EOF) {
        
    }

    return;
}