#include <stdio.h>
#include <stdlib.h>

#include "argparse.h"
#include "path.h"
#include "dataStore.h"
#include "commandParse.h"

int main(int argc, char *argv[]) {
    dataStoreT *dataStore = createDataStore("./", NULL, NULL, NULL);
    FILE *f = fopen("inputFile", "r");
    while (!feof(f)) {
        commandParse(f, dataStore);
    }
    
    return 0;
}