#include "fileHelp.h"

#include <sys/stat.h>
#include <limits.h>

#include <string.h>

int makedirs(char* fullPath) {
    char *temp = fullPath;
    for (; *temp; ++temp); {
        if (*temp == '/') {
            *temp = '\0';
            mkdir(fullPath, 777);
            *temp = '/';
        }
    }
}