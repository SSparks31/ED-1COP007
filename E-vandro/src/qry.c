#include "qry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path.h"

void qry_parser(char* BED, char* BSD, char* geo_name, char* qry_name, List shapes) {
    char result[999], buffer[999];
    
    concat_path_file(result, BED, qry_name);
    FILE* qry_file = fopen(result, "r");
    
    strip_suffix(buffer, qry_name);
    strip_suffix(result, geo_name);
    sprintf(result, "%s-%s", result, buffer);
       
    concat_path_file(buffer, BSD, result);
    
    concat_file_suffix(result, buffer, "svg");
    concat_file_suffix(buffer, buffer, "txt");
    
    printf("%s %s\n", result, buffer);

    FILE* svg_file = fopen(result, "w");
    FILE* txt_file = fopen(buffer, "w");

    char command[999];
/*    while (fscanf(qry_file, "%s", command) != EOF) {
        if (strcmp(command, "i?") == 0) {
            _i(qry_file, shapes);
        } else if (strcmp(command, "delf") == 0) {
            delf(qry_file, shapes);
        } 
    }
*/
    return;
}