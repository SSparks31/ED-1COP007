#include "qry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/pathHelp.h"

void qry_parser(char* BED, char* BSD, char* geo_name, char* qry_name, List circles, List lines, List rectangles, List texts) {
    if (!BED) {
        char* directory = "./";
        BED = directory;
    }

    char* qry_path = concatPathFile(BED, qry_name);
    FILE* qry_file = fopen(qry_path, "r");
    // free(qry_path);
      
    
    char* geo_no_suffix = stripSuffix(geo_name);
    char* qry_no_suffix = stripSuffix(qry_name);
    char* svg_name = malloc(strlen(geo_no_suffix) + strlen("-") + strlen(qry_no_suffix) + strlen(".svg") + 1);
    sprintf(svg_name, "%s-%s.svg");
    char* svg_path = concatPathFile(BSD, svg_path);
    char* txt_name = stripSuffix(svg_path);
    char* txt_path = concatPathFile(txt_name, ".txt");
    printf("%s %s %s\n", qry_path, svg_path, txt_path);

    return;
}