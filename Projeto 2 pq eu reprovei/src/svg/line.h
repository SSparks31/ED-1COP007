#ifndef MODULE_SVGLINE_H
#define MODULE_SVGLINE_H

#include <stdio.h>

typedef struct line* Line;

Line create_line(char* id, double coordinates[4], char* color);

char* line_get_id(Line line);

double line_get_x1(Line line);
double line_get_y1(Line line);
double line_get_x2(Line line);
double line_get_y2(Line line);

char* line_get_color(Line line);

void line_set_x1(Line line, double x1);
void line_set_y1(Line line, double y1);
void line_set_x2(Line line, double x2);
void line_set_y2(Line line, double y2);

void line_set_color(Line line, char* color);

void line_destroy(Line* line);

void line_write_to_SVG(FILE* svg_file, Line line);

#endif