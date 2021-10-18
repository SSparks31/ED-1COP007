#ifndef MODULE_SVGSHAPE_H
#define MODULE_SVGSHAPE_H

enum generic_shapes {  
    GENERIC_CIRCLE = 1,
    GENERIC_RECTANGLE,
    GENERIC_LINE,
    GENERIC_TEXT
};

typedef struct generic_shape* Generic_shape;

Generic_shape generic_shape_create(char* id, int type, void* shape);

char* generic_shape_get_id(Generic_shape generic_shape);
int generic_shape_get_type(Generic_shape generic_shape);
void* generic_shape_get_shape(Generic_shape generic_shape);

void generic_shape_destroy(Generic_shape* generic_shape);

#endif