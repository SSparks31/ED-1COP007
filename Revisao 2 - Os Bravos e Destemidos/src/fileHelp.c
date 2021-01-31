#include "fileHelp.h"

#include <sys/stat.h>

#define DIR_MASK 0777

int makedirs(char *fullPath) {
    char *aux = fullPath;
    for (; *aux; ++aux) {
        if (*aux == '/') {
            *aux = '\0';
            mkdir(fullPath, DIR_MASK);
            *aux = '/';
        }
    }
    mkdir(fullPath, DIR_MASK);
}