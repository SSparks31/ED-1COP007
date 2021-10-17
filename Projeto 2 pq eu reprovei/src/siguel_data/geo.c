#include "geo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../svg/circle.h"
#include "../svg/line.h"
#include "../svg/rectangle.h"
#include "../svg/text.h"

#include "../helper/pathHelp.h"

struct geo_lists {
    List rectangles;
    List circles;
    List lines;
    List texts;
};

Geo_lists create_geo_lists() {
    Geo_lists geo_lists = malloc(sizeof(struct geo_lists));
    if (!geo_lists) {
        return NULL;
    }
    geo_lists->rectangles = create_list();
    geo_lists->circles = create_list();
    geo_lists->lines = create_list();
    geo_lists->texts = create_list();
}

List geo_get_rectangles(Geo_lists geo_lists) {
    if (!geo_lists) {
        return NULL;
    }
    return geo_lists->rectangles;
}

List geo_get_circles(Geo_lists geo_lists){
    if (!geo_lists) {
        return NULL;
    }
    return geo_lists->circles;
}

List get_get_lines(Geo_lists geo_lists){
    if (!geo_lists) {
        return NULL;
    }
    return geo_lists->lines;
}

List geo_get_texts(Geo_lists geo_lists){
    if (!geo_lists) {
        return NULL;
    }
    return geo_lists->texts;
}

void c(List circles, FILE* geo_file, FILE* svg_file) {
    char id[999];
    
    double coordinates[3];    
    char colors[2][999];

    fscanf(geo_file, "%s %lf %lf %lf %s %s", id, coordinates, coordinates + 1, coordinates + 2, colors, colors + 1);

    Circle circle = create_circle(id, coordinates, colors);
    list_append(circles, circle);
    circle_write_to_SVG(svg_file, circle);
}

void l(List lines, FILE* geo_file, FILE* svg_file) {
    char id[999];
    
    double coordinates[4];    
    char colors[999];

    fscanf(geo_file, "%s %lf %lf %lf %lf %s", id, coordinates, coordinates + 1, coordinates + 2, coordinates + 3, colors);

    Line line = create_line(id, coordinates, colors);
    list_append(lines, line);
    line_write_to_SVG(svg_file, line);
}

void r(List rectangles, FILE* geo_file, FILE* svg_file) {
    char id[999];
    
    double coordinates[4];    
    char colors[2][999];

    fscanf(geo_file, "%s %lf %lf %lf %lf %s %s", id, coordinates, coordinates + 1, coordinates + 2, coordinates + 3, colors, colors + 1);

    Rectangle rectangle = create_rectangle(id, coordinates, colors);
    list_append(rectangles, rectangle);
    rectangle_write_to_SVG(svg_file, rectangle);
}

void t(List texts, FILE* geo_file, FILE* svg_file) {
    char id[999];
    
    double coordinates[2];    
    char colors[2][999];
    char string[999];

    fscanf(geo_file, "%s %lf %lf %s %s", id, coordinates, coordinates + 1, colors, colors + 1);
    fgets(string, 999, geo_file);
    if (*(string + strlen(string) - 1) == '\n') {
        *(string + strlen(string) - 1) = '\0';
    }

    Text text = create_text(id, coordinates, string, colors);
    list_append(texts, text);
    text_write_to_SVG(svg_file, text);
}

Geo_lists geo_parser(char* BED, char* BSD, char* geo_name) {
    if (!BED) {
        char* directory = "./";
        BED = directory;
    }

    char* geo_path = concatPathFile(BED, geo_name);
    FILE* geo_file = fopen(geo_path, "r");
    free(geo_path);
    if (!geo_file) {
        return NULL;
    }

    char* geo_no_suffix = stripSuffix(geo_name);
    char* svg_name = concatFileSuffix(geo_no_suffix, "svg");
    free(geo_no_suffix);
    char* svg_path = concatPathFile(BSD, svg_name);
    FILE* svg_file = fopen(svg_path, "w");
    if (!svg_file) {
        fclose(geo_file);
        return NULL;
    }

    Geo_lists geo_lists = create_geo_lists();
    if (!geo_lists) {
        fclose(geo_file);
        fclose(svg_file);
        return NULL;
    }

    char command;
    while (fscanf(geo_file, "%c ", command) != EOF) {
        switch (command) {
            case 'c':
                c(geo_lists->circles, geo_file, svg_file);
                break;

            case 'l':
                l(geo_lists->lines, geo_file, svg_file);
                break;

            case 'r':
                r(geo_lists->rectangles, geo_file, svg_file);
                break;

            case 't':
                t(geo_lists->texts, geo_file, svg_file);
                break;

            default:
                break;
        }   
    }

    return geo_lists;
}