#include "./argHelp.h"

#include "./stringHelp.h"

int optind = 1;
char* optarg = NULL;

int getArguments(int argc, char *argv[], char *optstring) {
    if (argc == 1 || optind >= argc || !argv || *argv[optind] != '-' || isEmpty(optstring)) {
        return -1;
    }

    char* arg = argv[optind];
    optind++;

    char* optstringPos = findCharacter(optstring, arg[1]);
    if (isEmpty(optstringPos)) {
        return '?';
    }

    if (optstringPos[1] == ':') {
        if (arg[2]) {
            optarg = arg + 2;
            optind++;
        } else {
            if (optind == argc) {
                optarg = NULL;
            } else {
                optarg = argv[optind++];
            }
        }
    }

    return *optstringPos;
}