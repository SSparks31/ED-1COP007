#include "circle.h"

#include "../helper/stringHelp.h"

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

Circle create_circle(char* id, double coordinates[3], char* colors[2]) {
    if (!id || !coordinates || !colors) {
        return NULL;
    }
    
    for (int i = 0; i < 2; ++i) {
        if (isEmpty(colors[i])) {
            return NULL;
        }
    }

    Circle circle = malloc(sizeof(struct circle));
    if (!circle) {
        return NULL;
    }

    circle->id = malloc(strlen(id) + 1);

    int error = 0;

    circle_set_x           (circle, coordinates[0]);
    circle_set_y           (circle, coordinates[1]);
    circle_set_radius      (circle, coordinates[2]);

    if (!circle->id || circle_set_border_color(circle, colors[0]) || circle_set_fill_color(circle, colors[1])) {
        circle_destroy(&circle);
    }

    strcpy(circle->id, id);

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
    if (!circle) {
        return;
    }

    circle->x = x;
}

void circle_set_y(Circle circle, double y) {
    if (!circle) {
        return;
    }

    circle->y = y;
}

void circle_set_radius(Circle circle, double radius) {
    if (!circle) {
        return;
    }

    circle->radius = radius;
}

int circle_set_border_color(Circle circle, char* border_color) {
    if (!circle || isEmpty(border_color)) {
        return 1;
    }

    if (!circle->border_color) {
        circle->border_color = malloc(strlen(border_color) + 1);
    } else {
        circle->border_color = realloc(circle->border_color, strlen(border_color) + 1);
    }

    if(!circle->border_color) {
        return 1;
    }

    strcpy(circle->border_color, border_color);
	return 0;
}

int circle_set_fill_color(Circle circle, char* fill_color) {
    if (!circle || isEmpty(fill_color)) {
        return 1;
    }

    if (!circle->fill_color) {
        circle->fill_color = malloc(strlen(fill_color) + 1);
    } else {
        circle->fill_color = realloc(circle->fill_color, strlen(fill_color) + 1);
    }

    if(!circle->fill_color) {
        return 1;
    }

    strcpy(circle->fill_color, fill_color);
	return 0;
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