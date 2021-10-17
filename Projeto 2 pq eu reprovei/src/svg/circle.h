#ifndef MODULE_SVGCIRCLE_H
#define MODULE_SVGCIRCLE_H

typedef struct circle* Circle;

Circle create_circle(char* id, double coordinates[3], char* colors[2]);

char* circle_get_id(Circle circle);

double circle_get_x(Circle circle);
double circle_get_y(Circle circle);
double circle_get_radius(Circle circle);

char* circle_get_border_color(Circle circle);
char* circle_get_fill_color(Circle circle);

void circle_set_x(Circle circle, double x);
void circle_set_y(Circle circle, double y);
void circle_set_radius(Circle circle, double radius);

int circle_set_border_color(Circle circle, char* border_color);
int circle_set_fill_color(Circle circle, char* fill_color);

void circle_destroy(Circle* circle);

#endif