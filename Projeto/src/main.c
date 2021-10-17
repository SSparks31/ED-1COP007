#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./progrlib/progrData.h"
#include "./progrlib/geo.h"
#include "./progrlib/qry.h"

#include "./svg/svg.h"
#include "./svg/line.h"
#include "./svg/intersect.h"

#include "./helper/argHelp.h"
#include "./helper/stringHelp.h"

int main(int argc, char* argv[]) {
    char c;

    char* BED = NULL;
    char* BSD = NULL;
    char* geoName = NULL;
    char* qryName = NULL;


    listT lists[10];
    for (int i = 0; i < 10; ++i) {
        lists[i] = list_create()
    }


    pilha_insere(pilha)

    while ((c = getArguments(argc, argv, "e:f:o:q:")) != -1) {
        switch (c) {
        case 'e':
            if (!optarg || optarg[0] == '-') {
                printf("Opcao -%c necessita de argumento\n", c);
                return -1;
            }
            
            BED = optarg;
            break;
        
        case 'f':
            if (!optarg || optarg[0] == '-') {
                printf("Opcao -%c necessita de argumento\n", c);
                return -1;
            }

            geoName = optarg;
            break;
        
        case 'o':
            if (!optarg || optarg[0] == '-') {
                printf("Opcao -%c necessita de argumento\n", c);
                return -1;
            }

            BSD = optarg;
            break;

        case 'q':
            if (!optarg || optarg[0] == '-') {
                printf("Opcao -%c necessita de argumento\n", c);
                return -1;
            }

            qryName = optarg;
            break;
        
        
        default:
            
            break;
        }
    }

    char* relativePath = "./";
    char* emptyString = "";
    if (isEmpty(BED)) {
        BED = relativePath;
    }

    if (isEmpty(BSD)) {
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

    progrData data = createData(BED, BSD, geoName, qryName);
    if (!data) {
        return -1;
    }

    geoParser(data);

    qryParser(data);

    destroyData(data);

    return 0;
}