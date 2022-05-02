#include "svg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CIRCLE_FORMAT "<circle cx=\"%.6lf\" cy=\"%.6lf\" r=\"%.6lf\" stroke=\"%s\" stroke-opacity=\"%.2lf\" stroke-width=\"%.2lf\" fill=\"%s\" fill-opacity=\"%.2lf\" stroke-dasharray=\"%d\" />\n"
#define RECTANGLE_FORMAT "<rect x=\"%.6lf\" y=\"%.6lf\" width=\"%.6lf\" height=\"%.6lf\" stroke=\"%s\" stroke-width=\"%.2lf\" stroke-opacity=\"%.2lf\" fill=\"%s\" fill-opacity=\"%.2lf\" stroke-dasharray=\"%d\" />\n"
#define LINE_FORMAT "<line x1=\"%.6lf\" y1=\"%.6lf\" x2=\"%.6lf\" y2=\"%.6lf\" stroke=\"%s\" stroke-width=\"%.2lf\" stroke-dasharray=\"%d\" />\n"
#define TEXT_FORMAT "<text x=\"%.6lf\" y=\"%.6lf\" stroke=\"%s\" stroke-width=\"%.2lf\" fill=\"%s\" font-size=\"20\" text-anchor=\"%s\">%s</text>\n"

struct shape {
    int id;

    char type;

    char* border_color;
    double border_opacity;
    double border_width;

    char* fill_color;
    double fill_opacity;

    int is_dotted;

    char* text;
    char alignment;
    
    double coordinates[4];
};

int shape_get_id(Shape shape) {
    if (!shape) {
        return -1; 
    }

    return shape->id;
}

char shape_get_type(Shape shape) {
    if (!shape) {
        return '\0';
    }

    return shape->type;
}

void shape_set_border_color(Shape shape, char* new_color) {
    if (!shape || !new_color) {
        return;
    }

    shape->border_color = realloc(shape->border_color, strlen(new_color) + 1);
    strcpy(shape->border_color, new_color);
}

char* shape_get_border_color(Shape shape) {
    if (!shape) {
        return NULL;
    }

    return shape->border_color;
}

void shape_set_border_opacity(Shape shape, double opacity) {
    if (!shape || opacity < 0) {
        return;
    }

    shape->border_opacity = opacity;
}

double shape_get_border_opacity(Shape shape) {
    if (!shape) {
        return -1;
    }

    return shape->border_opacity;
}

void shape_set_border_width(Shape shape, double width) {
    if (!shape || width < 0) {
        return;
    }

    shape->border_width = width;
}

double shape_get_border_width(Shape shape) {
    if (!shape) {
        return -1;
    }

    return shape->border_width;
}

void shape_set_fill_color(Shape shape, char* new_color) {
    if (!shape || !new_color) {
        return;
    }

    shape->fill_color = realloc(shape->fill_color, strlen(new_color) + 1);
    strcpy(shape->fill_color, new_color);
}

char* shape_get_fill_color(Shape shape) {
    if (!shape) {
        return NULL;
    }

    return shape->fill_color;
}

void shape_set_fill_opacity(Shape shape, double opacity) {
    if (!shape || opacity < 0) {
        return;
    }

    shape->fill_opacity = opacity;
}

double shape_get_fill_opacity(Shape shape) {
    if (!shape) {
        return -1;
    }

    return shape->fill_opacity;
}

int shape_is_dotted(Shape shape) {
    if (!shape) {
        return -1;
    }

    return shape->is_dotted;
}

char* shape_get_text(Shape shape) {
    if (!shape) {
        return NULL;
    }

    return shape->text;
}

char shape_get_alignment(Shape shape) {
    if (!shape) {
        return '\0';
    }

    return shape->alignment;
}

void shape_set_coordinate(Shape shape, int coordinate_position, double coordinate) {
    if (!shape || coordinate_position < 0 || coordinate_position > 3) {
        return;
    }

    shape->coordinates[coordinate_position] = coordinate;
}

double* shape_get_coordinates(Shape shape) {
    if (!shape) {
        return NULL;
    }

    return shape->coordinates;
}

Shape circle_create(int id, double x, double y, double r, char* border_color, char* fill_color, int is_dotted) {
    Shape new_circle = malloc(sizeof(struct shape));

    new_circle->id = id;

    new_circle->type = SVG_CIRCLE;

    new_circle->border_color = calloc(1, strlen(border_color) + 1);
    strcpy(new_circle->border_color, border_color);
    new_circle->border_opacity = 1;
    new_circle->border_width = 1;

    new_circle->fill_color = calloc(1, strlen(fill_color) + 1);
    strcpy(new_circle->fill_color, fill_color);
    new_circle->fill_opacity = 1;
    
    new_circle->is_dotted = is_dotted;

    new_circle->text = NULL;
    new_circle->alignment = '\0';

    new_circle->coordinates[0] = x;
    new_circle->coordinates[1] = y;
    new_circle->coordinates[2] = r;

    return new_circle;
}

Shape rectangle_create(int id, double x, double y, double w, double h, char* border_color, char* fill_color, int is_dotted) {
    Shape new_rectangle = malloc(sizeof(struct shape));

    new_rectangle->id = id;

    new_rectangle->type = SVG_RECTANGLE;

    new_rectangle->border_color = calloc(1, strlen(border_color) + 1);
    strcpy(new_rectangle->border_color, border_color);
    new_rectangle->border_opacity = 1;
    new_rectangle->border_width = 1;

    new_rectangle->fill_color = calloc(1, strlen(fill_color) + 1);
    strcpy(new_rectangle->fill_color, fill_color);
    new_rectangle->fill_opacity = 1;
    
    new_rectangle->is_dotted = is_dotted;

    new_rectangle->text = NULL;
    new_rectangle->alignment = '\0';

    new_rectangle->coordinates[0] = x;
    new_rectangle->coordinates[1] = y;
    new_rectangle->coordinates[2] = w;
    new_rectangle->coordinates[3] = h;

    return new_rectangle;
}

Shape line_create(int id, double x1, double y1, double x2, double y2, char* border_color, double border_width, int is_dotted) {
    Shape new_line = malloc(sizeof(struct shape));

    new_line->id = id;

    new_line->type = SVG_LINE;

    new_line->border_color = calloc(1, strlen(border_color) + 1);
    strcpy(new_line->border_color, border_color);
    new_line->border_opacity = 1;
    new_line->border_width = border_width;

    new_line->fill_color = NULL;
    new_line->fill_opacity = 0;
    
    new_line->is_dotted = is_dotted;

    new_line->text = NULL;
    new_line->alignment = '\0';

    new_line->coordinates[0] = x1;
    new_line->coordinates[1] = y1;
    new_line->coordinates[2] = x2;
    new_line->coordinates[3] = y2;

    return new_line;
}

Shape text_create(int id, double x, double y, char* border_color, char* fill_color, char alignment, char* text) {
    Shape new_text = malloc(sizeof(struct shape));

    new_text->id = id;

    new_text->type = SVG_TEXT;

    new_text->border_color = calloc(1, strlen(border_color) + 1);
    strcpy(new_text->border_color, border_color);
    new_text->border_opacity = 1;
    new_text->border_width = .6;

    new_text->fill_color = calloc(1, strlen(fill_color) + 1);
    strcpy(new_text->fill_color, fill_color);
    new_text->fill_opacity = 1;
    
    new_text->is_dotted = 0;

    new_text->text = calloc(1, strlen(text) + 1);
    strcpy(new_text->text, text);
    new_text->alignment = alignment;

    new_text->coordinates[0] = x;
    new_text->coordinates[1] = y;

    return new_text;
}

Shape point_create(int id, double x, double y);

void circle_write_to_SVG(FILE* svg_file, Shape shape) {
    char* border_color = shape_get_border_color(shape);
    double border_opacity = shape_get_border_opacity(shape);
    double border_width = shape_get_border_width(shape);
    
    char* fill_color = shape_get_fill_color(shape);
    double fill_opacity = shape_get_fill_opacity(shape);
    
    int is_dotted = shape_is_dotted(shape) ? 1 : 0;
 
    double x = shape_get_coordinates(shape)[0];
    double y = shape_get_coordinates(shape)[1];
    double r = shape_get_coordinates(shape)[2];
    
    fprintf(svg_file, CIRCLE_FORMAT, x, y, r, border_color, border_opacity, border_width, fill_color, fill_opacity, is_dotted);
}

void rectangle_write_to_SVG(FILE* svg_file, Shape shape) {
    char* border_color = shape_get_border_color(shape);
    double border_opacity = shape_get_border_opacity(shape);
    double border_width = shape_get_border_width(shape);
    
    char* fill_color = shape_get_fill_color(shape);
    double fill_opacity = shape_get_fill_opacity(shape);
    
    int is_dotted = shape_is_dotted(shape) ? 1 : 0;
 
    double x = shape_get_coordinates(shape)[0];
    double y = shape_get_coordinates(shape)[1];
    double w = shape_get_coordinates(shape)[2];
    double h = shape_get_coordinates(shape)[3];
    
    fprintf(svg_file, RECTANGLE_FORMAT, x, y, w, h, border_color, border_opacity, border_width, fill_color, fill_opacity, is_dotted);
}

void line_write_to_SVG(FILE* svg_file, Shape shape) {
    char* border_color = shape_get_border_color(shape);
    double border_width = shape_get_border_width(shape);
    
    int is_dotted = shape_is_dotted(shape) ? 1 : 0;
 
    double x1 = shape_get_coordinates(shape)[0];
    double y1 = shape_get_coordinates(shape)[1];
    double x2 = shape_get_coordinates(shape)[2];
    double y2 = shape_get_coordinates(shape)[3];
    
    fprintf(svg_file, LINE_FORMAT, x1, y1, x2, y2, border_color, border_width, is_dotted);
}

void text_write_to_SVG(FILE* svg_file, Shape shape) {
    char* border_color = shape_get_border_color(shape);
    double border_width = shape_get_border_width(shape);
    
    char* fill_color = shape_get_fill_color(shape);

    char* text = shape_get_text(shape);
    char alignment[9];
    switch (shape_get_alignment(shape)) {
    case SVG_TEXT_LEFT:
        strcpy(alignment, "start");
        break;
    
    case SVG_TEXT_CENTER:
        strcpy(alignment, "middle");
        break;

    case SVG_TEXT_RIGHT:
        strcpy(alignment, "end");
        break;

    default:
        printf("Ancora do texto desconhecida\n");
        return;
    }
    
    double x = shape_get_coordinates(shape)[0];
    double y = shape_get_coordinates(shape)[1];

    fprintf(svg_file, TEXT_FORMAT, x, y, border_color, border_width, fill_color, alignment, text);
}

void shape_write_to_SVG(FILE* svg_file, Shape shape) {
    if (!shape) {
        return;
    }

    switch (shape_get_type(shape)) {
    case SVG_CIRCLE:
        circle_write_to_SVG(svg_file, shape);
        break;
    
    case SVG_RECTANGLE:
        rectangle_write_to_SVG(svg_file, shape);
        break;
    
    case SVG_LINE:
        line_write_to_SVG(svg_file, shape);
        break;
    
    case SVG_TEXT:
        text_write_to_SVG(svg_file, shape);
        break;
    
    default:
        break;
    }
}

void shape_destroy(Shape* shape) {
    if ((*shape)->border_color != NULL) {
        free((*shape)->border_color);
    }
    if ((*shape)->fill_color != NULL) {
        free((*shape)->fill_color);
    }
    if ((*shape)->text != NULL) {
        free((*shape)->text);
    }

    free(*shape);
    *shape = NULL;
}