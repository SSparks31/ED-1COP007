#include "./argHelp.h"

#include "./stringHelp.h"

int optind = 1;
char* optarg = NULL;

int getArguments(int argc, char *argv[], char *optstring) {
    if (argc == 1 || optind >= argc || !argv || *argv[optind] != '-' || isEmpty(optstring)) {
        return -1;
    }

    char* optstringPos = findCharacter(optstring, argv[optind][1]);
    if (!optstringPos) {
        optind++;
        return '?';
    }

    if (optstringPos[1] == ':') {
        if (argv[optind][2]) {
            optarg = &argv[optind][2];
        } else {
            if (optind + 1 >= argc) {
                optarg = NULL;
            } else {
                optarg = argv[++optind];
            }
        }
    }

    optind++;

    return *optstringPos;
}