#include "fileHelp.h"

#include <sys/stat.h>

#define DIR_MASK 0777

int makedirs(char* fullPath) {
    char *temp = fullPath;
    for (; *temp; ++temp) {
        if (*temp == '/') {
            *temp = '\0';
            mkdir(fullPath, DIR_MASK);
            *temp = '/';
        }
    }
    mkdir(fullPath, DIR_MASK);
}