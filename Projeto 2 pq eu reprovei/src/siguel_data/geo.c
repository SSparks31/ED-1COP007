#include "geo.h"

#include <stdio.h>
#include <stdlib.h>

#include "../helper/pathHelp.h"

struct geo_lists {
    List squares;
    List circles;
    List lines;
    List texts;
};

Geo_lists create_geo_lists() {
    Geo_lists geo_lists = malloc(sizeof(struct geo_lists));
    if (!geo_lists) {
        return NULL;
    }
    geo_lists->squares = create_list();
    geo_lists->circles = create_list();
    geo_lists->lines = create_list();
    geo_lists->texts = create_list();
}

List geo_get_squares(Geo_lists geo_lists) {
    if (!geo_lists) {
        return NULL;
    }
    return geo_lists->squares;
}

List geo_get_circles(Geo_lists geo_lists){
    if (!geo_lists) {
        return NULL;
    }
    return geo_lists->circles;
}

List get_get_lines(Geo_lists geo_lists){
    if (!geo_lists) {
        return NULL;
    }
    return geo_lists->lines;
}

List geo_get_texts(Geo_lists geo_lists){
    if (!geo_lists) {
        return NULL;
    }
    return geo_lists->texts;
}

void c(List circles, FILE* geo_file) {

}

Geo_lists geo_parser(char* BED, char* BSD, char* geo_name) {
    if (!BED) {
        char* directory = "./";
        BED = directory;
    }

    char* geo_path = concatPathFile(BED, geo_name);
    FILE* geo_file = fopen(geo_path, "r");
    free(geo_path);
    if (!geo_file) {
        return NULL;
    }

    char* geo_no_suffix = stripSuffix(geo_name);
    char* svg_name = concatFileSuffix(geo_no_suffix, "svg");
    free(geo_no_suffix);
    char* svg_path = concatPathFile(BSD, svg_name);
    FILE* svg_file = fopen(svg_path, "w");
    if (!svg_file) {
        fclose(geo_file);
        return NULL;
    }

    Geo_lists geo_lists = create_geo_lists();
    if (!geo_lists) {
        fclose(geo_file);
        fclose(svg_file);
        return NULL;
    }

    char command[2];
    while (fscanf(geo_file, "%s ", command) != EOF) {
        fgets(command + 200, 500, geo_file);
        command[200 + strlen(command+200) - 1] = '\0';
        printf("%s - %s\n", command, command + 200);
    }

    return geo_lists;
}