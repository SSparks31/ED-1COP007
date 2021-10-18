#include "qry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../helper/pathHelp.h"
#include "../helper/mathHelp.h"

#include "../queue/queue.h"
#include "../stack/stack.h"

#include "../svg/circle.h"
#include "../svg/line.h"
#include "../svg/rectangle.h"
#include "../svg/text.h"
#include "../svg/shape.h"

List_pos find_shape_with_id(List shapes, char* id) {
    List_pos aux = list_get_first(shapes);
    while (aux) {
        Generic_shape shape = list_get_elem(shapes, aux);
        if (strcmp(generic_shape_get_id(shape), id) == 0) {
            break;
        }

        aux = list_get_next(shapes, aux);
    }

    return aux;
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(dpow(x2-x1, 2) + dpow(y2-y1, 2));
}

void _o();

void _i(FILE* qry_file, List shapes) {
    char id_to_check[999];
    double x;
    double y;

    Generic_shape generic_shape = find_shape_with_id(shapes, id_to_check);
    void* shape = generic_shape_get_shape(generic_shape);
    int shape_type = generic_shape_get_type(generic_shape);

    printf("i? %s %.6lf %.6lf\n");

    int is_inside = 0;

    switch (shape_type) {
        case GENERIC_CIRCLE:
        printf("Circulo - ");
        double x_circle = circle_get_x(shape);
        double y_circle = circle_get_y(shape);
        double radius = circle_set_radius(shape);

        is_inside = fabs(distance(x, y, x_circle, y_circle) - radius) < 0.00001;
        break;

        case GENERIC_LINE:
        printf("Linha - ");
        double x1_line = line_get_x1(shape);
        double y1_line = line_get_y1(shape);
        double x2_line = line_get_x2(shape);
        double y2_line = line_get_y2(shape);
        double angular_coefficient = (y2_line-y1_line)/(x2_line-x1_line);
        double linear_coefficient = y1_line - angular_coefficient * x1_line;

        is_inside = fabs(angular_coefficient * x + linear_coefficient - y) < 0.00001;
        break;

        case GENERIC_RECTANGLE:
        printf("Retangulo - ");
            double x1_rectangle = rectangle_get_x(shape);
            double y1_rectangle = rectangle_get_y(shape);
            double x2_rectangle = x1_rectangle + rectangle_get_width(shape);
            double y2_rectangle = y1_rectangle + rectangle_get_height(shape);

            is_inside = (x > x1_rectangle && x < x2_rectangle) || (y > y1_rectangle && y < y2_rectangle);
            break;

        case default:
            return;
    }

    char new_border_color[999];
    char new_fill_color[999];

    if (is_inside) {
        printf("Interno\n");
        strcpy(new_border_color, "blue");
        strcpy(new_fill_color, "blue");
    } else {
        printf("Externo\n");
        strcpy(new_border_color, "magenta");
        strcpy(new_fill_color, "magenta");
    }

    char* id = "";

    double coordinates[4];
    coordinates[0] = x;
    coordinates[1] = y;
    coordinates[2] = 1;
    
    Circle point = circle_create(coordinates, new_border_color, new_fill_color);
    Generic_shape generic_point = generic_shape_create(id, GENERIC_CIRCLE, point);

    switch (shape_type) {
        case GENERIC_CIRCLE:
        coordinates[2] = circle_get_x(shape);
        coordinates[3] = circle_get_y(shape);
        break;

        case GENERIC_RECTANGLE:
        coordinates[2] = rectangle_get_x(shape) + rectangle_get_width(shape)/2;
        coordinates[3] = rectangle_get_y(shape) + rectangle_get_height(shape)/2;
        break;

        case GENERIC_LINE:
        coordinates[2] = (line_get_x1(shape) + line_get_2(shape))/2;
        coordinates[3] = (line_get_y1(shape) + line_get_y2(shape))/2;
        break;

        default:
        break;        
    }

    Line line = line_create(coordinates, new_fill_color);
    Generic_shape generic_line = generic_shape_create(id, GENERIC_LINE, line);

    list_insert(shapes, generic_point);
    list_insert(shapes, generic_line);
}

void _pnt(FILE* qry_file, List shapes) {
    char id_to_paint[999];
    char new_border_color[999];
    char new_fill_color[999];
    fscanf(qry_file, "%s %s %s\n", id_to_paint, new_border_color, new_fill_color);
    Generic_shape generic_shape = find_shape_with_id(shapes, id_to_paint);
    void* shape = generic_shape_get_shape(generic_shape);
    int shape_type = generic_shape_get_type(generic_shape);

    switch (shape_type) {
        case GENERIC_CIRCLE:
        circle_set_border_color(shape, new_border_color);
        circle_set_fill_color(shape, new_fill_color);
        break;

        case GENERIC_LINE:
        line_set_color(shape, new_fill_color);
        break;

        case GENERIC_RECTANGLE:
        rectangle_set_border_color(shape, new_border_color);
        rectangle_set_fill_color(shape, new_fill_color);
        break;

        case GENERIC_TEXT:
        circle_set_border_color(shape, new_border_color);
        circle_set_fill_color(shape, new_fill_color);
        break;

        default:
        break;
       
    }

}

void _delf(FILE* qry_file, List shapes) {
    char id_to_remove[999];
    fscanf(qry_file, "%s\n", id_to_remove);

    List_pos shape_pos = find_shape_with_id(shapes, id_to_remove);
        
    if (shape_pos) {
        printf("Removing shape with id %s\n", id_to_remove);
        list_remove(shapes, shape_pos);
    }
}

void _psh(FILE* qry_file, List shapes, Stack stacks[10]) {
    char* id_to_push[999];
    int stack;
    fscanf(qry_file, "%d %s\n", &stack, id_to_push);

    Generic_shape shape = list_get_elem(find_shape_with_id(shapes, id_to_push));
    if (!shape) {
        return;
    }

    stack_insert(stacks[stack], shape);
}

void _pop();

void _inf(FILE* qry_file, List shapes, Queue queues[10]) {
    char* id_to_insert[999];
    int queue;
    fscanf(qry_file, "%d %s\n", &queue, id_to_insert);

    Generic_shape shape = list_get_elem(find_shape_with_id(shapes, id_to_insert));
    if (!shape) {
        return;
    }

    queue_insert(queues[queue], shape);
}

void _rmf();

void _ii(FILE* qry_file, List shapes, List lists[10], List_pos registers[10]) {
    char* id_to_insert[999];
    int identifier;
    int register;
    fscanf(qry_file, "%d %i %d\n", &identifier, id_to_insert, &register);

    Generic_shape shape = list_get_elem(find_shape_with_id(shapes, id_to_insert));
    if (!shape) {
        return;
    }

    List_pos first = list_get_first(lists[identifier]);
    registers[register] = list_insert_before(lists[identifier], first, shape);
}

void _if(FILE* qry_file, List shapes, List lists[10], List_pos registers[10]) {
    char* id_to_insert[999];
    int identifier;
    int register;
    fscanf(qry_file, "%d %i %d\n", &identifier, id_to_insert, &register);

    Generic_shape shape = list_get_elem(find_shape_with_id(shapes, id_to_insert));
    if (!shape) {
        return;
    }

    registers[register] = list_insert(lists[identifier], shape);
}

void _ia(FILE* qry_file, List shapes, List lists[10], List_pos registers[10]) {
    char* id_to_insert[999];
    int identifier;
    int registerO;
    int registerD;
    fscanf(qry_file, "%d %i %d %d\n", &identifier, id_to_insert, &registerO, &registerD);

    Generic_shape shape = list_get_elem(find_shape_with_id(shapes, id_to_insert));
    if (!shape) {
        return;
    }

    registers[registerD] = list_insert_before(lists[identifier], registerO, shape);
}

void _ia(FILE* qry_file, List shapes, List lists[10], List_pos registers[10]) {
    char* id_to_insert[999];
    int identifier;
    int registerO;
    int registerD;
    fscanf(qry_file, "%d %i %d %d\n", &identifier, id_to_insert, &registerO, &registerD);

    Generic_shape shape = list_get_elem(find_shape_with_id(shapes, id_to_insert));
    if (!shape) {
        return;
    }

    registers[registerD] = list_insert_after(lists[identifier], registerO, shape);
}

void _da(FILE* qry_file, List shapes, List lists[10], List_pos registers[10]) {
    int identifier;
    int register;
    fscanf(qry_file, "%d %d\n", &identifier, &register);

    List_pos prev = list_get_prev(lists[identifier], registers[register]);
    list_remove(lists[identifier], prev);   
}

void _da(FILE* qry_file, List shapes, List lists[10], List_pos registers[10]) {
    int identifier;
    int register;
    fscanf(qry_file, "%d %d\n", &identifier, &register);

    List_pos next = list_get_next(lists[identifier], registers[register]);
    list_remove(lists[identifier], next);   
}

void _dpl(FILE* qry_file, List shapes, List lists[10])

void qry_parser(char* BED, char* BSD, char* geo_name, char* qry_name, List shapes) {
    char* qry_path = concatPathFile(BED, qry_name);
    FILE* qry_file = fopen(qry_path, "r");
    
    char* geo_no_suffix = stripSuffix(geo_name);
    char* qry_no_suffix = stripSuffix(qry_name);
    char* geo_qry = malloc(strlen(geo_no_suffix) + strlen("-") + strlen(qry_no_suffix) + 1);
    sprintf(geo_qry, "%s-%s", geo_no_suffix, qry_no_suffix);
       
    char* svg_txt_path = concatPathFile(BSD, geo_qry);
    char* svg_path = concatFileSuffix(svg_txt_path, "svg");
    char* txt_path = concatFileSuffix(svg_txt_path, "txt");
    
    FILE* svg_file = fopen(svg_path, "w");
    FILE* txt_file = fopen(txt_path, "w");

    free(qry_path);
    free(geo_no_suffix);
    free(qry_no_suffix);
    free(geo_qry);
    free(svg_txt_path);
    free(svg_path);
    free(txt_path);

    List lists[10];
    Stack stacks[10];
    Queue queues[10];
    List_pos registers[10];

    for (int i = 0; i < 10; ++i) {
        lists[i] = create_list();
        stacks[i] = create_stack();
        queues[i] = create_queue();
        registers[i] = NULL;
    }

    char command[999];
    while (fscanf(qry_file, "%s", command) != EOF) {
        if (strcmp(command, "i?") == 0) {
            _i(qry_file, shapes);
        } else if (strcmp(command, "delf") == 0) {
            delf(qry_file, shapes);
        } 
    }

    return;
}