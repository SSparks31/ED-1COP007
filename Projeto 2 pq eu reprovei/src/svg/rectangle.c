#include "rectangle.h"

#include "../helper/stringHelp.h"

#include <stdlib.h>
#include <string.h>

struct rectangle {
    char* id;

    double x;
    double y;
    double width;
    double height;

    char* border_color;
    char* fill_color;
};

Rectangle create_rectangle(char* id, double coordinates[4], char* colors[2]) {
    if (!id || !coordinates || !colors) {
        return NULL;
    }

    for (int i = 0; i < 2; ++i) {
        if (isEmpty(colors[i])) {
            return NULL;
        }
    }

    Rectangle rectangle = malloc(sizeof(struct rectangle));
    if (!rectangle) {
        return NULL;
    }

    rectangle->id = malloc(strlen(id) + 1);

    int error = 0;

    rectangle_set_x     (rectangle, coordinates[0]);
    rectangle_set_y     (rectangle, coordinates[1]);
    rectangle_set_width (rectangle, coordinates[2]);
    rectangle_set_height(rectangle, coordinates[3]);

    if (!rectangle->id || rectangle_set_border_color(rectangle, colors[0]) || rectangle_set_fill_color  (rectangle, colors[1])) {
        rectangle_destroy(&rectangle);
    }

    strcpy(rectangle->id, id);

    return rectangle;
}

char* rectangle_get_id(Rectangle rectangle) {
    if (!rectangle) {
        return NULL;
    }

    return rectangle->id;
}

char* rectangle_get_x(Rectangle rectangle) {
    if (!rectangle) {
        return NULL;
    }

    return rectangle->x;
}

char* rectangle_get_y(Rectangle rectangle) {
    if (!rectangle) {
        return NULL;
    }

    return rectangle->y;
}

char* rectangle_get_width(Rectangle rectangle) {
    if (!rectangle) {
        return NULL;
    }

    return rectangle->width;
}

char* rectangle_get_height(Rectangle rectangle) {
    if (!rectangle) {
        return NULL;
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
    if (!rectangle) {
        return;
    }

    rectangle->x = x;
}

void rectangle_set_y(Rectangle rectangle, double y) {
    if (!rectangle) {
        return;
    }

    rectangle->y = y;
}

void rectangle_set_width(Rectangle rectangle, double width) {
    if (!rectangle) {
        return;
    }

    rectangle->width = width;
}

void rectangle_set_height(Rectangle rectangle, double height) {
    if (!rectangle) {
        return;
    }

    rectangle->height = height;
}


int rectangle_set_border_color(Rectangle rectangle, char* border_color) {
    if (!rectangle || isEmpty(border_color)) {
        return 1;
    }

    if (!rectangle->border_color) {
        rectangle->border_color = malloc(strlen(border_color) + 1);
    } else {
        rectangle->border_color = realloc(rectangle->border_color, strlen(border_color) + 1);
    }

    if(!rectangle->border_color) {
        return 1;
    }

    strcpy(rectangle->border_color, border_color);
	return 0;
}

int rectangle_set_fill_color(Rectangle rectangle, char* fill_color) {
    if (!rectangle || isEmpty(fill_color)) {
        return 1;
    }

    if (!rectangle->fill_color) {
        rectangle->fill_color = malloc(strlen(fill_color) + 1);
    } else {
        rectangle->fill_color = realloc(rectangle->fill_color, strlen(fill_color) + 1);
    }

    if(!rectangle->fill_color) {
        return 1;
    }

    strcpy(rectangle->fill_color, fill_color);
	return 0;
}

void rectangle_destroy(Rectangle* rectangle) {
    if (!rectangle || !*rectangle) {
        return;
    }

    if ((*rectangle)->id) free((*rectangle)->id);

    if ((*rectangle)->border_color) free((*rectangle)->border_color);
    if ((*rectangle)->fill_color) free((*rectangle)->fill_color);

    free(*rectangle);
    *rectangle = NULL;
}