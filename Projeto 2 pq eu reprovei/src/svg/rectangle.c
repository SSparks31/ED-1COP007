#include "rectangle.h"

#include <stdlib.h>
#include <string.h>

struct rectangle {
    double x;
    double y;
    double width;
    double height;

    char* border_color;
    char* fill_color;
};

Rectangle rectangle_create(double coordinates[4], char* border_color, char* fill_color) {
    if (!coordinates || !border_color || !fill_color) {
        return NULL;
    }

    Rectangle rectangle = malloc(sizeof(struct rectangle));
    if (!rectangle) {
        return NULL;
    }

    rectangle_set_x(rectangle, coordinates[0]);
    rectangle_set_y(rectangle, coordinates[1]);
    rectangle_set_width(rectangle, coordinates[2]);
    rectangle_set_height(rectangle, coordinates[3]);

    rectangle->border_color = NULL;
    rectangle->fill_color = NULL;
    rectangle_set_border_color(rectangle, border_color);
    rectangle_set_fill_color(rectangle, fill_color);

    return rectangle;
}

double rectangle_get_x(Rectangle rectangle) {
    if (!rectangle) {
        return -1;
    }

    return rectangle->x;
}

double rectangle_get_y(Rectangle rectangle) {
    if (!rectangle) {
        return -1;
    }

    return rectangle->y;
}

double rectangle_get_width(Rectangle rectangle) {
    if (!rectangle) {
        return -1;
    }

    return rectangle->width;
}

double rectangle_get_height(Rectangle rectangle) {
    if (!rectangle) {
        return -1;
    }

    return rectangle->height;
}

char* rectangle_get_border_color(Rectangle rectangle) {
    if (!rectangle) {
        return NULL;
    }

    return rectangle->border_color;
}
char* rectangle_get_fill_color(Rectangle rectangle) {
    if (!rectangle) {
        return NULL;
    }

    return rectangle->fill_color;
}

void rectangle_set_x(Rectangle rectangle, double x) {
    if (!rectangle || x < 0) {
        return;
    }

    rectangle->x = x;
}

void rectangle_set_y(Rectangle rectangle, double y) {
    if (!rectangle || y < 0) {
        return;
    }

    rectangle->y = y;
}

void rectangle_set_width(Rectangle rectangle, double width) {
    if (!rectangle || width < 0) {
        return;
    }

    rectangle->width = width;
}

void rectangle_set_height(Rectangle rectangle, double height) {
    if (!rectangle || height < 0) {
        return;
    }

    rectangle->height = height;
}

void rectangle_set_border_color(Rectangle rectangle, char* border_color) {
    if (!rectangle || !border_color) {
        return;
    }

    rectangle->border_color = realloc(rectangle->border_color, strlen(border_color) + 1);
    strcpy(rectangle->border_color, border_color);
}

void rectangle_set_fill_color(Rectangle rectangle, char* fill_color) {
    if (!rectangle || !fill_color) {
        return;
    }

    rectangle->fill_color = realloc(rectangle->fill_color, strlen(fill_color) + 1);
    strcpy(rectangle->fill_color, fill_color);
}

void rectangle_destroy(Rectangle* rectangle) {
    if (!rectangle || !*rectangle) {
        return;
    }

    if ((*rectangle)->border_color) free((*rectangle)->border_color); 
    if ((*rectangle)->fill_color) free((*rectangle)->fill_color); 

    free(*rectangle);
    *rectangle = NULL;
}

void rectangle_write_to_SVG(FILE* svg_file, Rectangle rectangle) {
    if (!svg_file || !rectangle) {
        return;
    }

    const char* format = "<rect x = \"%.6lf\" y = \"%.6lf\" width = \"%.6lf\" height = \"%.6lf\" stroke = \"%s\" fill=\"%s\" />\n" ;

    double x = rectangle_get_x(rectangle);
    double y = rectangle_get_y(rectangle);
    double width = rectangle_get_width(rectangle);
    double height = rectangle_get_height(rectangle);

    char* border_color = rectangle_get_border_color(rectangle);
    char* fill_color = rectangle_get_fill_color(rectangle);

    fprintf(svg_file, format, x, y, width, height, border_color, fill_color);
}