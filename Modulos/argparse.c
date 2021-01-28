#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argparse.h"


int argumentParse(char* result, int argc, char* argv[], char* target) {
    if (!argv || !target || strlen(target) == 0) {
        return -1;
    }
    
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i],target) == 0) {
            if (!argv[i+1] || argv[i+1][0] == '-') {
                return -2;
            }
            strcpy(result, argv[i+1]);
            return 0;
        }
    }
    
    return -3;
}