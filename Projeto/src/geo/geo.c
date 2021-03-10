#include "geo.h"

#include <stdio.h>
#include <string.h>

#include "../svg/rect.h"
#include "../svg/svg.h"

#include "../helper/stringHelp.h"
#include "../helper/mathHelp.h"

listT geoParser(char* geoPath) {
    FILE *geoFile = fopen(geoPath, "r");
    if (!geoFile) {
        printf("Arquivo .geo nao encontrado\n");
        return NULL;
    }

    char borderColor[SVG_COLOR_MAX_LEN];
    char fillColor[SVG_COLOR_MAX_LEN];
    listT rectList = NULL;

    char command[999];

    while (!isEmpty(fgetLine(geoFile, command, 999))) {
        switch (command[0]) {
            case 'n': {
                char* numPos = rfindCharacter(command, ' ') + 1;
                rectList = createList(stringToInt(numPos));
                break;
            }
            
            case 'c': {
                if (command[1] == 'c') {
                    strcpy(borderColor, rfindCharacter(command, ' ') + 1);
                } else {
                    strcpy(fillColor, rfindCharacter(command, ' ') + 1);
                }
                break;
            }
            
            case 'r': {
                char* ID = findCharacter(command, ' ') + 1;
                char* coordinates = findCharacter(ID, ' ') + 1;
                coordinates[-1] = '\0';

                rectT newRect = createRect(borderColor, fillColor, ID, coordinates);
                appendList(rectList, newRect);
                break;
            }

            default:
                break;
        }
    }

    fclose(geoFile);
    return rectList;
}