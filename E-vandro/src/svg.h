#ifndef LIB_SVG_H
#define LIB_SVG_H

#include <stdio.h>

typedef struct shape* Shape;

enum {
    SVG_TEXT_LEFT = 'i',
    SVG_TEXT_CENTER = 'm',
    SVG_TEXT_RIGHT = 'f',
};

enum {
    SVG_CIRCLE,
    SVG_RECTANGLE,
    SVG_LINE,
    SVG_TEXT,
    SVG_POINT
};

int shape_get_id(Shape shape);

char shape_get_type(Shape shape);

void shape_set_border_color(Shape shape, char* new_color);

char* shape_get_border_color(Shape shape);

void shape_set_fill_color(Shape shape, char* new_color);

char* shape_get_fill_color(Shape shape);

char* shape_get_text(Shape shape);

char shape_get_alignment(Shape shape);

int shape_is_dotted(Shape shape);

void shape_set_coordinate(Shape shape, int coordinate_position, double coordinate);

double* shape_get_coordinates(Shape shape);

Shape circle_create(int id, double x, double y, double r, char* border_color, char* fill_color, int is_dotted);

Shape rectangle_create(int id, double x, double y, double w, double h, char* border_color, char* fill_color, int is_dotted);

Shape line_create(int id, double x1, double y1, double x2, double y2, char* border_color, double border_width, int is_dotted);

Shape text_create(int id, double x, double y, char* border_color, char* fill_color, char alignment, char* text);

Shape point_create(int id, double x, double y);

void shape_write_to_SVG(FILE* svg_file, Shape shape);

void shape_destroy(Shape* shape);

#endif