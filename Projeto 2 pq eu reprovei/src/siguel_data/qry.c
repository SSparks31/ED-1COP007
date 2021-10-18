#include "qry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/pathHelp.h"

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

void _o();

void _i();

void _pnt();

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

void _ii(FILE* qry_file, List shapes, List lists[10], List_pos* registers) {
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

void _if(FILE* qry_file, List shapes, List lists[10], List_pos* registers) {
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

void _ia(FILE* qry_file, List shapes, List lists[10], List_pos* registers) {
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

void _ia(FILE* qry_file, List shapes, List lists[10], List_pos* registers) {
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

void _da(FILE* qry_file, List shapes, List* lists[10], List_pos* registers) {
    int identifier;
    int register;
    fscanf(qry_file, "%d %d\n", &identifier, &register);

    List_pos prev = list_get_prev(lists[identifier], registers[register]);
    list_remove(lists[identifier], prev);   
}

void _da(FILE* qry_file, List shapes, List* lists[10], List_pos* registers) {
    int identifier;
    int register;
    fscanf(qry_file, "%d %d\n", &identifier, &register);

    List_pos next = list_get_next(lists[identifier], registers[register]);
    list_remove(lists[identifier], next);   
}

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
    List_pos register[10];

    for (int i = 0; i < 10; ++i) {
        lists[i] = create_list();
        stacks[i] = create_stack();
        queues[i] = create_queue();
        register[i] = NULL;
    }

    char command[999];
    while (fscanf(qry_file, "%s", command) != EOF) {
        if (strcmp(command, "delf") == 0) {
            delf(qry_file, shapes);
        } 
    }

    return;
}