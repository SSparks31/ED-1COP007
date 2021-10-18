#include "shape.h"

#include <stdlib.h>
#include <string.h>

struct generic_shape {
    char* id;
    int type;
    void* shape;
};

Generic_shape generic_shape_create(char* id, int type, void* shape) {
    if (!shape || type < GENERIC_CIRCLE) {
        return NULL;
    }

    Generic_shape generic_shape = malloc(sizeof(struct generic_shape));

    generic_shape->id = malloc(strlen(id) + 1);
    strcpy(generic_shape->id, id);

    generic_shape->type = type;
    generic_shape->shape = shape;

    return generic_shape;
}

char* generic_shape_get_id(Generic_shape generic_shape) {
    if (!generic_shape) {
        return NULL;
    }
     
    return generic_shape->id;
}

int generic_shape_get_type(Generic_shape generic_shape) {
    if (!generic_shape) {
        return 0;
    }
     
    return generic_shape->type;
}

void* generic_shape_get_shape(Generic_shape generic_shape) {
    if (!generic_shape) {
        return NULL;
    }
     
    return generic_shape->shape;
}


void generic_shape_destroy(Generic_shape* generic_shape);