#ifndef MODULE_GEO_H
#define MODULE_GEO_H

typedef struct geo_lists* Geo_lists;

#include "../list/list.h"

List geo_get_rectangles(Geo_lists geo_lists);
List geo_get_circles(Geo_lists geo_lists);
List get_get_lines(Geo_lists geo_lists);
List geo_get_texts(Geo_lists geo_lists);

Geo_lists geo_parser(char* BED, char* BSD, char* geo_name);

#endif