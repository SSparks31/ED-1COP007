#include "line.h"

#include "../helper/stringHelp.h"

#include <stdlib.h>
#include <string.h>

struct line {
    char* id;

    char* x1;
    char* y1;
    char* x2;
    char* y2;

    char* color;
};

Line create_line(char* id, char* coordinates[4], char* color) {
    if (!id || !coordinates || isEmpty(color)) {
        return NULL;
    }
    for (int i = 0; i < 4; ++i) {
        if (isEmpty(coordinates[i])) {
            return NULL;
        }
    }

    Line line = malloc(sizeof(struct line));
    if (!line) {
        return NULL;
    }

    line->id = malloc(strlen(id) + 1);

    int error = 0;

    error += line_set_x1     (line, coordinates[0]);
    error += line_set_y1     (line, coordinates[1]);
    error += line_set_x2     (line, coordinates[2]);
    error += line_set_y2     (line, coordinates[3]);

    error += line_set_color  (line, color);

    if (!line->id || error) {
        line_destroy(&line);
    }

    strcpy(line->id, id);

    return line;
}

char* line_get_id(Line line) {
    if (!line) {
        return NULL;
    }

    return line->id;
}

char* line_get_x1(Line line) {
    if (!line) {
        return NULL;
    }

    return line->x1;
}

char* line_get_y1(Line line) {
    if (!line) {
        return NULL;
    }

    return line->y1;
}

char* line_get_x2(Line line) {
    if (!line) {
        return NULL;
    }

    return line->x2;
}

char* line_get_y2(Line line) {
    if (!line) {
        return NULL;
    }

    return line->y2;
}

char* line_get_color(Line line) {
    if (!line) {
        return NULL;
    }

    return line->color;
}


int line_set_x1(Line line, char* x1) {
    if (!line || isEmpty(x1)) {
        return 1;
    }

    if (!line->x1) {
        line->x1 = malloc(strlen(x1) + 1);
    } else {
        line->x1 = realloc(line->x1, strlen(x1) + 1);
    }

    if (!line->x1) {
        return 1;
    }

    strcpy(line->x1, x1);
    return 0;
}

int line_set_y1(Line line, char* y1) {
    if (!line || isEmpty(y1)) {
        return 1;
    }

    if (!line->y1) {
        line->y1 = malloc(strlen(y1) + 1);
    } else {
        line->y1 = realloc(line->y1, strlen(y1) + 1);
    }

    if (!line->y1) {
        return 1;
    }

    strcpy(line->y1, y1);
    return 0;
}

int line_set_x2(Line line, char* x2) {
    if (!line || isEmpty(x2)) {
        return 1;
    }

    if (!line->x2) {
        line->x2 = malloc(strlen(x2) + 1);
    } else {
        line->x2 = realloc(line->x2, strlen(x2) + 1);
    }

    if (!line->x2) {
        return 1;
    }

    strcpy(line->x2, x2);
	return 0;
}

int line_set_y2(Line line, char* y2) {
    if (!line || isEmpty(y2)) {
        return 1;
    }

    if (!line->y2) {
        line->y2 = malloc(strlen(y2) + 1);
    } else {
        line->y2 = realloc(line->y2, strlen(y2) + 1);
    }

    if (!line->y2) {
        return 1;
    }

    strcpy(line->y2, y2);
	return 0;
}

int line_set_color(Line line, char* color) {
    if (!line || isEmpty(color)) {
        return 1;
    }

    if (!line->color) {
        line->color = malloc(strlen(color) + 1);
    } else {
        line->color = realloc(line->color, strlen(color) + 1);
    }

    if(!line->color) {
        return 1;
    }

    strcpy(line->color, color);
	return 0;
}

void line_destroy(Line* line) {
    if (!line || !*line) {
        return;
    }

    if ((*line)->id) free((*line)->id);

    if ((*line)->x1) free((*line)->x1);
    if ((*line)->y1) free((*line)->y1);
    if ((*line)->x2) free((*line)->x2);
    if ((*line)->y2) free((*line)->y2);

    if ((*line)->color) free((*line)->color);

    free(*line);
    *line = NULL;
}