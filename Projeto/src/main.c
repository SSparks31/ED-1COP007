#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./progrData/progrData.h"

#include "./geo/geo.h"
#include "./qry/qry.h"

#include "./svg/svg.h"

#include "./helper/argHelp.h"
#include "./helper/pathHelp.h"
#include "./helper/stringHelp.h"

int main(int argc, char* argv[]) {
    char c;

    char* inputPath = NULL;
    char* outputPath = NULL;
    char* geoName = NULL;
    char* qryName = NULL;

    int collect = 0;
    char* collectPath = NULL;

    while ((c = getArguments(argc, argv, "e:f:o:q:ic")) != -1) {
        switch (c) {
        case 'e':
            if (!optarg || optarg[0] == '-') {
                printf("Opcao -%c necessita de argumento\n", c);
                return -1;
            }
            inputPath = optarg;
            break;
        
        case 'f':
            if (!optarg || optarg[0] == '-') {
                printf("Opcao -%c necessita de argumento\n", c);
                return -1;
            }
            if (strcmp(optarg, "b") == 0) {
                if (optind >= argc || *(optarg = argv[optind++]) == '-') {
                    printf("Opcao -fb necessita de argumento\n");
                    return -1;
                }
                collect = 3;
                collectPath = optarg;
            } else {
                geoName = optarg;
            }
            break;
        
        case 'o':
            if (!optarg || optarg[0] == '-') {
                printf("Opcao -%c necessita de argumento\n", c);
                return -1;
            }
            outputPath = optarg;
            break;

        case 'q':
            if (!optarg || optarg[0] == '-') {
                printf("Opcao -%c necessita de argumento\n", c);
                return -1;
            }
            qryName = optarg;
            break;
        
        case 'i':
            collect = 1;
            break;
        
        case 'c':
            collect = 2;
            break;
        
        default:
            
            break;
        }
    }

    char* emptyString = "";
    if (isEmpty(inputPath)) {
        inputPath = emptyString;
    }
    if (isEmpty(outputPath)) {
        printf("Opcao -o e obrigatoria\n");
        return -1;
    }
    if (isEmpty(geoName)) {
        printf("Opcao -f e obrigatoria\n");
        return -1;
    }
    if (isEmpty(qryName)) {
        qryName = emptyString;
    }

    progrDataT progrData = createProgrData(inputPath, outputPath, geoName, qryName, collect);
    if (!progrData) {
        return -1;
    }

    geoParser(progrData);

    qryParser(progrData);

    listT rectList = getRectListProgrData(progrData);

    while (!isEmptyList(rectList)) {
        destroyRect(removeList(rectList, getFirstElementList(rectList)));
    }

    destroyProgrData(progrData);

    return 0;
}