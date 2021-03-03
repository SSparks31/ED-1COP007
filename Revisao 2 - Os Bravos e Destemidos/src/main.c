#include "path.h"
#include "dataStore.h"
#include "stringHelp.h"
#include "mathHelp.h"
#include "inputParser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <limits.h>

int main(int argc, char *argv[]) {
    char opt;
    char *options = "f:o:";

    FILE *inputFile = NULL;

    char defaultDir[PATH_MAX] = "";

    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
            case 'f':
                inputFile = fopen(optarg, "r");
                if (!inputFile) {
                    printf("Arquivo passado na opcao -f nao foi encontrado ou nao pode ser aberto.\n");
                    return -1;
                }
                break;
            case 'o':
                strcpy(defaultDir, optarg);
                break;
            case ':':
                printf("Opcao -%c necessita de argumento.\n", opt);
                return -1;
        }
    }

    if (!inputFile) {
        printf("Opcao -f e obrigatoria.\n");
        return -1;
    }

    dataStoreT *dataStore = createDataStore(defaultDir, min(argc - optind, 3), argv + optind);
    
    commandParse(inputFile, dataStore);

    destroyDataStore(&dataStore);
    
    return 0;
}