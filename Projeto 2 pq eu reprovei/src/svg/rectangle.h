#ifndef MODULE_SVGRECTANGLE_H
#define MODULE_SVGRECTANGLE_H

typedef struct rectangle* Rectangle;

Rectangle create_rectangle(char* id, double coordinates[4], char* colors[2]);

char* rectangle_get_id(Rectangle rectangle);

double rectangle_get_x(Rectangle rectangle);
double rectangle_get_y(Rectangle rectangle);
double rectangle_get_width(Rectangle rectangle);
double rectangle_get_height(Rectangle rectangle);

char* rectangle_get_border_color(Rectangle rectangle);
char* rectangle_get_fill_color(Rectangle rectangle);

void rectangle_set_x(Rectangle rectangle, double x);
void rectangle_set_y(Rectangle rectangle, double y);
void rectangle_set_width(Rectangle rectangle, double width);
void rectangle_set_height(Rectangle rectangle, double height);

int rectangle_set_border_color(Rectangle rectangle, char* border_color);
int rectangle_set_fill_color(Rectangle rectangle, char* fill_color);

void rectangle_destroy(Rectangle* rectangle);

#endif