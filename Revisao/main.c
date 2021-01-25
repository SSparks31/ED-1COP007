#include <stdio.h>
#include <stdlib.h>
#include "RevisaoEx.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Por favor, insira o caminho do arquivo como argumento na linha de comando.\n");
        return -1;
    }
    if (argc > 2) {
        printf("Por favor, insira apenas um argumento na linha de comando.\n");
        return -2;
    }

    char* fullPath = argv[1];

    printf("Caminho completo: %s\n", fullPath);
    
    char *path = getPath(fullPath);
    printf("Caminho do arquivo: %s\n", path);

    char *name = getFileName(fullPath);
    printf("Nome do arquivo: %s\n", name);
    
    char *suffix = getSuffix(name);
    printf("Extensao do arquivo: %s\n", suffix);

    int slash = hasSlash(path);
    printf("Caminho %s termina em '/': %s\n", path, slash ? "Sim" : "Nao");

    char *remadePath = concatPathFile(path, name);
    printf("Caminho concatenado a partir das funcoes: %s\n", remadePath);

    free(path);
    free(name);
    free(suffix);
    free(remadePath);
    return 0;
}