#include "geo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"

#include "path.h"

void c(List shapes, FILE* geo_file, FILE* svg_file) {
    int id;

    double x;
    double y;
    double r;
    
    char border_color[99];
    char fill_color[99];

    fscanf(geo_file, "%d %lf %lf %lf %s %s\n", &id, &x, &y, &r, border_color, fill_color);

    Shape new_circle = circle_create(id, x, y, r, border_color, fill_color, 0);
    list_append(shapes, new_circle);
    shape_write_to_SVG(svg_file, new_circle);
}

void l(List shapes, FILE* geo_file, FILE* svg_file) {
    int id;

    double x1;
    double y1;
    double x2;
    double y2;
    
    char border_color[99];

    fscanf(geo_file, "%d %lf %lf %lf %lf %s\n", &id, &x1, &y1, &x2, &y2, border_color);

    Shape new_line = line_create(id, x1, y1, x2, y2, border_color, 1, 0);
    list_append(shapes, new_line);
    shape_write_to_SVG(svg_file, new_line);
}

void r(List shapes, FILE* geo_file, FILE* svg_file) {
    int id;

    double x;
    double y;
    double w;
    double h;
    
    char border_color[20];
    char fill_color[20];

    fscanf(geo_file, "%d %lf %lf %lf %lf %s %s\n", &id, &x, &y, &w, &h, border_color, fill_color);

    Shape new_rectangle = rectangle_create(id, x, y, w, h, border_color, fill_color, 0);
    list_append(shapes, new_rectangle);
    shape_write_to_SVG(svg_file, new_rectangle);
}

void t(List shapes, FILE* geo_file, FILE* svg_file) {
    int id;

    double x;
    double y;

    char text[999];
    char alignment;

    char border_color[99];
    char fill_color[99];

    fscanf(geo_file, "%d %lf %lf %s %s %c ", &id, &x, &y, border_color, fill_color, &alignment);
    fgets(text, 998, geo_file);

    text[strcspn(text, "\r\n")] = '\0';

    Shape new_text = text_create(id, x, y, border_color, fill_color, alignment, text);
    list_append(shapes, new_text);
    shape_write_to_SVG(svg_file, new_text);
}

void geo_parser(char* BED, char* BSD, char* geo_name, List shapes) {
    char result[999], buffer[999];
    concat_path_file(result, BED, geo_name);  
    FILE* geo_file = fopen(result, "r");
    if (!geo_file) {
        return;
    }

    
    strip_suffix(buffer, geo_name);
    concat_file_suffix(buffer, buffer, "svg");
    concat_path_file(result, BSD, buffer);
    FILE* svg_file = fopen(result, "w");
    if (!svg_file) {
        fclose(geo_file);
        return;
    }

    fprintf(svg_file, "<svg>\n");

    char command;

    while (fscanf(geo_file, "%c ", &command) != EOF) {
        switch (command) {
            case 'c':
                c(shapes, geo_file, svg_file);
                break;

            case 'l':
                l(shapes, geo_file, svg_file);
                break;

            case 'r':
                r(shapes, geo_file, svg_file);
                break;

            case 't':
                t(shapes, geo_file, svg_file);
                break;

            default:
                fgets(buffer, 999, geo_file);
                printf("Algo deu errado ao ler os comandos do arquivo geo\n");
                break;
        }   
    }

    fprintf(svg_file, "</svg>");
}