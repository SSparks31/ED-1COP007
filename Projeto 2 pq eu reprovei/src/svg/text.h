#ifndef MODULE_SVGTEXT_H
#define MODULE_SVGTEXT_H

#include <stdio.h>

typedef struct text* Text;

Text text_create(double coordinates[2], char* string, char* border_color, char* fill_color);

double text_get_x(Text text);
double text_get_y(Text text);
char* text_get_string(Text text);

char* text_get_border_color(Text text);
char* text_get_fill_color(Text text);

void text_set_x(Text text, double x);
void text_set_y(Text text, double y);
void text_set_string(Text text, char* string);

void text_set_border_color(Text text, char* border_color);
void text_set_fill_color(Text text, char* fill_color);

void text_destroy(Text* text);

void text_write_to_SVG(FILE* svg_file, Text text);

#endif