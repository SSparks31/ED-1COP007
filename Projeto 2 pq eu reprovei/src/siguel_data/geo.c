#include "geo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../svg/circle.h"
#include "../svg/line.h"
#include "../svg/rectangle.h"
#include "../svg/text.h"

#include "../helper/pathHelp.h"

void c(List circles, FILE* geo_file, FILE* svg_file) {
    char id[999];
    
    double coordinates[3]; // x y r 
    char border_color[999];
    char fill_color[999];

    fscanf(geo_file, "%s %lf %lf %lf %s %s", id, coordinates + 2, coordinates, coordinates + 1, border_color, fill_color);

    Circle circle = create_circle(id, coordinates, border_color, fill_color);
    list_append(circles, circle);
    circle_write_to_SVG(svg_file, circle);
    fgets(border_color, 999, geo_file);
}

void l(List lines, FILE* geo_file, FILE* svg_file) {
    char id[999];
    
    double coordinates[4]; // x1 y1 x2 y2
    char color[999];

    fscanf(geo_file, "%s %lf %lf %lf %lf %s", id, coordinates, coordinates + 1, coordinates + 2, coordinates + 3, color);

    Line line = create_line(id, coordinates, color);
    list_append(lines, line);
    line_write_to_SVG(svg_file, line);
    fgets(color, 999, geo_file);
}

void r(List rectangles, FILE* geo_file, FILE* svg_file) {
    char id[999];
    
    double coordinates[4]; // x y w h
    char border_color[999];
    char fill_color[999];

    fscanf(geo_file, "%s %lf %lf %lf %lf %s %s", id, coordinates + 2, coordinates + 3, coordinates, coordinates + 1, border_color, fill_color);

    Rectangle rectangle = create_rectangle(id, coordinates, border_color, fill_color);
    list_append(rectangles, rectangle);
    rectangle_write_to_SVG(svg_file, rectangle);
    fgets(border_color, 999, geo_file);
}

void t(List texts, FILE* geo_file, FILE* svg_file) {
    char id[999];
    
    double coordinates[2]; // x y
    char border_color[999];
    char fill_color[999];
    char string[999];

    fscanf(geo_file, "%s %lf %lf %s %s ", id, coordinates, coordinates + 1, border_color, fill_color);
    fgets(string, 999, geo_file);
    if (*(string + strlen(string) - 1) == '\n') {
        *(string + strlen(string) - 1) = '\0';
    }

    printf("%s\n", string);

    Text text = create_text(id, coordinates, string, border_color, fill_color);
    list_append(texts, text);
    text_write_to_SVG(svg_file, text);
}

void geo_parser(char* BED, char* BSD, char* geo_name, List circles, List lines, List rectangles, List texts) {
    if (!BED) {
        char* directory = "./";
        BED = directory;
    }

    char* geo_path = concatPathFile(BED, geo_name);
    FILE* geo_file = fopen(geo_path, "r");
    free(geo_path);
    if (!geo_file) {
        return;
    }

    char* geo_no_suffix = stripSuffix(geo_name);
    char* svg_name = concatFileSuffix(geo_no_suffix, "svg");
    free(geo_no_suffix);
    char* svg_path = concatPathFile(BSD, svg_name);
    FILE* svg_file = fopen(svg_path, "w");
    if (!svg_file) {
        fclose(geo_file);
        return;
    }

    fprintf(svg_file, "<svg>\n");

    char command;
    char buffer[999];

    while (fscanf(geo_file, "%c ", &command) != EOF) {
        switch (command) {
            case 'c':
                c(circles, geo_file, svg_file);
                break;

            case 'l':
                l(lines, geo_file, svg_file);
                break;

            case 'r':
                r(rectangles, geo_file, svg_file);
                break;

            case 't':
                t(rectangles, geo_file, svg_file);
                break;

            default:
                fgets(buffer, 999, geo_file);
                break;
        }   
    }

    fprintf(svg_file, "</svg>");
}