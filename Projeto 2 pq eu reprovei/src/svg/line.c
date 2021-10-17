#include "line.h"

#include <stdlib.h>
#include <string.h>

struct line {
    char* id;

    double x1;
    double y1;
    double x2;
    double y2;

    char* color;
};

Line create_line(char* id, double coordinates[4], char* colors) {
    if (!id || !coordinates || !colors) {
        return NULL;
    }

    Line line = malloc(sizeof(struct line));
    if (!line) {
        return NULL;
    }

    line->id = malloc(strlen(id) + 1);
    strcpy(line->id, id);

    line_set_x1(line, coordinates[0]);
    line_set_y1(line, coordinates[1]);
    line_set_x2(line, coordinates[2]);
    line_set_y2(line, coordinates[3]);

    line_set_color(line, colors);

    return line;
}

char* line_get_id(Line line) {
    if (!line) {
        return NULL;
    }

    return line->id;
}

double line_get_x1(Line line) {
    if (!line) {
        return -1;
    }

    return line->x1;
}

double line_get_y1(Line line) {
    if (!line) {
        return -1;
    }

    return line->y1;
}

double line_get_x2(Line line) {
    if (!line) {
        return -1;
    }

    return line->x2;
}

double line_get_y2(Line line) {
    if (!line) {
        return -1;
    }

    return line->y2;
}

char* line_get_color(Line line) {
    if (!line) {
        return NULL;
    }

    return line->color;
}


void line_set_x1(Line line, double x1) {
    if (!line || x1 < 0) {
        return;
    }

    line->x1 = x1;
}

void line_set_y1(Line line, double y1) {
    if (!line || y1 < 0) {
        return;
    }

    line->y1 = y1;
}

void line_set_x2(Line line, double x2) {
    if (!line || x2 < 0) {
        return;
    }

    line->x2 = x2;
}

void line_set_y2(Line line, double y2) {
    if (!line || y2 < 0) {
        return;
    }

    line->y2 = y2;
}

void line_set_color(Line line, char* color) {
    if (!line || !color) {
        return;
    }

    if (!line->color) {
        line->color = malloc(strlen(color) + 1);
    } else {
        line->color = realloc(line->color, strlen(color) + 1);
    }

    strcpy(line->color, color);
}

void line_destroy(Line* line) {
    if (!line || !*line) {
        return;
    }

    if ((*line)->id) free((*line)->id); 
    
    if ((*line)->color) free((*line)->color); 

    free(*line);
    *line = NULL;
}

void line_write_to_SVG(FILE* svg_file, Line line) {
    if (!svg_file || !line) {
        return;
    }

    const char* format = "<line x1 = \"%.6lf\" y1 = \"%.6lf\" x2 = \"%.6lf\" y2 = \"%.6lf\" stroke = \"%s\" stroke-width=\"1\" />\n";

    double x1 = line_get_x1(line);
    double y1 = line_get_y1(line);
    double x2 = line_get_x2(line);
    double y2 = line_get_y2(line);

    char* color = line_get_color(line);

    fprintf(svg_file, format, x1, y1, x2, y2, color);
}