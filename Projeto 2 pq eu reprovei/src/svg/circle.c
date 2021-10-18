#include "circle.h"

#include <stdlib.h>
#include <string.h>

struct circle {
    char* id;

    double x;
    double y;
    double radius;

    char* border_color;
    char* fill_color;
};

Circle create_circle(char* id, double coordinates[3], char* border_color, char* fill_color) {
    if (!id || !coordinates || !border_color || !fill_color) {
        return NULL;
    }

    Circle circle = malloc(sizeof(struct circle));
    if (!circle) {
        return NULL;
    }

    circle->id = malloc(strlen(id) + 1);
    circle->border_color = NULL;
    circle->fill_color = NULL;

    strcpy(circle->id, id);

    circle_set_x(circle, coordinates[0]);
    circle_set_y(circle, coordinates[1]);
    circle_set_radius(circle, coordinates[2]);

    circle_set_border_color(circle, border_color);
    circle_set_fill_color(circle, fill_color);

    return circle;
}

char* circle_get_id(Circle circle) {
    if (!circle) {
        return NULL;
    }

    return circle->id;
}

double circle_get_x(Circle circle) {
    if (!circle) {
        return -1;
    }

    return circle->x;
}

double circle_get_y(Circle circle) {
    if (!circle) {
        return -1;
    }

    return circle->y;
}

double circle_get_radius(Circle circle) {
    if (!circle) {
        return -1;
    }

    return circle->radius;
}

char* circle_get_border_color(Circle circle) {
    if (!circle) {
        return NULL;
    }

    return circle->border_color;
}
char* circle_get_fill_color(Circle circle) {
    if (!circle) {
        return NULL;
    }

    return circle->fill_color;
}

void circle_set_x(Circle circle, double x) {
    if (!circle || x < 0) {
        return;
    }

    circle->x = x;
}

void circle_set_y(Circle circle, double y) {
    if (!circle || y < 0) {
        return;
    }

    circle->y = y;
}

void circle_set_radius(Circle circle, double radius) {
    if (!circle || radius < 0) {
        return;
    }

    circle->radius = radius;
}

void circle_set_border_color(Circle circle, char* border_color) {
    if (!circle || !border_color) {
        return;
    }

    circle->border_color = realloc(circle->border_color, strlen(border_color) + 1);
    strcpy(circle->border_color, border_color);
}

void circle_set_fill_color(Circle circle, char* fill_color) {
    if (!circle || !fill_color) {
        return;
    }

    circle->fill_color = realloc(circle->fill_color, strlen(fill_color) + 1);
    strcpy(circle->fill_color, fill_color);
}

void circle_destroy(Circle* circle) {
    if (!circle || !*circle) {
        return;
    }

    if ((*circle)->id) free((*circle)->id); 
    
    if ((*circle)->border_color) free((*circle)->border_color); 
    if ((*circle)->fill_color) free((*circle)->fill_color); 

    free(*circle);
    *circle = NULL;
}

void circle_write_to_SVG(FILE* svg_file, Circle circle) {
    if (!svg_file || !circle) {
        return;
    }

    const char* format = "<circle cx=\"%.6lf\" cy=\"%.6lf\" r=\"%.6lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"1\" />\n";

    double x = circle_get_x(circle);
    double y = circle_get_y(circle);
    double radius = circle_get_radius(circle);

    char* border_color = circle_get_border_color(circle);
    char* fill_color = circle_get_fill_color(circle);

    fprintf(svg_file, format, x, y, radius, border_color, fill_color);
}