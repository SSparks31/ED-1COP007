#include <stdio.h>
#include <stdlib.h>

#include "siguel_data/geo.h"
#include "siguel_data/qry.h"

#include "svg/rectangle.h"
#include "svg/line.h"
#include "svg/circle.h"
#include "svg/text.h"

#include <unistd.h>
#include <getopt.h>

int main(int argc, char* argv[]) {
    char option;
    
    char* BED = "./";
    char* BSD = NULL;
    char* geo_name = NULL;
    char* qry_name = NULL;

    while ((option = getopt(argc, argv, "e:f:o:q:")) != -1) {
        switch (option) {
        case 'e':
            BED = optarg;
            break;
        
        case 'f':
            geo_name = optarg;
            break;
        
        case 'o':
            BSD = optarg;
            break;
        
        case 'q':
            qry_name = optarg;
            break;
        
        default:
            break;
        }
    }
    if (!geo_name) {
        printf("Opcao `f` e obrigatoria\n");
        return -1;
    }

    if (!BSD) {
        printf("Opcao `o` e obrigatoria\n");
        return -1;
    }

    List shapes = create_list();

    geo_parser(BED, BSD, geo_name, shapes);

    if (qry_name) {
        qry_parser(BED, BSD, geo_name, qry_name, shapes);
    }

    return 0;
}