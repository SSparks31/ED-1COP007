#include "./line.h"

#include <stdlib.h>
#include <string.h>

#include "../helper/stringHelp.h"

struct line {
    char* color;

    char* x1;
    char* y1;
    char* x2;
    char* y2;
};

lineT createLine(char* color, char* coordinates) {
    if (isEmpty(color) || isEmpty(coordinates));
    
    lineT newLine = malloc(sizeof(struct line));
    if (!newLine) {
        return NULL;
    }

    char* x1  = coordinates;
    char* y1  = splitString(x1 , ' ');
    char* x2  = splitString(y1 , ' ');
    char* y2  = splitString(x2 , ' ');

    newLine->color = malloc(sizeof(char) * (strlen(color) + 1));
    newLine->x1 = malloc(sizeof(char) * (strlen(x1) + 1));
    newLine->y1 = malloc(sizeof(char) * (strlen(y1) + 1));
    newLine->x2 = malloc(sizeof(char) * (strlen(x2) + 1));
    newLine->y2 = malloc(sizeof(char) * (strlen(y2) + 1));
    
    strcpy(newLine->color, color);
    strcpy(newLine->x1, x1);
    strcpy(newLine->y1, y1);
    strcpy(newLine->x2, x2);
    strcpy(newLine->y2, y2);

    if (!newLine->color || !newLine->x1 || !newLine->y1 || !newLine->x2 || !newLine->y2) {
        destroyLine(newLine);
        return NULL;
    }

    return newLine;
}

char* getColorLine(lineT line) {
    if (!line) {
        return NULL;
    }

    return line->color;
}

void  setColorLine(lineT line, char* color) {
    if (!line || isEmpty(color)) {
        return;
    }

    line->color = realloc(line->color, sizeof(char) * (strlen(color) + 1));
    strcpy(line->color, color);
}

char* getX1Line(lineT line) {
    if (!line) {
        return NULL;
    }

    return line->x1;
}

void  setX1Line(lineT line, char* x1) {
    if (!line || isEmpty(x1)) {
        return;
    }

    line->x1 = realloc(line->x1, sizeof(char) * (strlen(x1) + 1));
    strcpy(line->x1, x1);
}

char* getY1Line(lineT line) {
    if (!line) {
        return NULL;
    }

    return line->y1;
}

void  setY1Line(lineT line, char* y1) {
    if (!line || isEmpty(y1)) {
        return;
    }

    line->y1 = realloc(line->y1, sizeof(char) * (strlen(y1) + 1));
    strcpy(line->y1, y1);
}

char* getX2Line(lineT line) {
    if (!line) {
        return NULL;
    }

    return line->x2;
}

void  setX2Line(lineT line, char* x2) {
    if (!line || isEmpty(x2)) {
        return;
    }

    line->x2 = realloc(line->x2, sizeof(char) * (strlen(x2) + 1));
    strcpy(line->x2, x2);
}

char* getY2Line(lineT line) {
    if (!line) {
        return NULL;
    }

    return line->y2;
}

void  setY2Line(lineT line, char* y2) {
    if (!line || isEmpty(y2)) {
        return;
    }

    line->y2 = realloc(line->y2, sizeof(char) * (strlen(y2) + 1));
    strcpy(line->y2, y2);
}

void  setCoordinatesLine(lineT line, char* coordinates) {
    if (!line || !coordinates) {
        return;
    }

    char* x1  = coordinates;
    char* y1  = splitString(x1 , ' ');
    char* x2  = splitString(y1 , ' ');
    char* y2  = splitString(x2 , ' ');

    setX1Line(line, x1);
    setY1Line(line, y1);
    setX2Line(line, x2);
    setY2Line(line, y2);
}

void  destroyLine(lineT line) {
    if (!line) {
        return;
    }

    if (line->color) free(line->color);
    if (line->x1) free(line->x1);
    if (line->y1) free(line->y1);
    if (line->x2) free(line->x2);
    if (line->y2) free(line->y2);

    free(line);
}