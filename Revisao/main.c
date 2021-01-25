#include <stdio.h>
#include <stdlib.h>
#include "revisaoEx.h"

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

    char *nullPath = getPath(NULL);
    printf("Caminho de arquivo invalido: %s\n", nullPath);

    char *nullName = getFileName(NULL);
    printf("Nome de arquivo invalido: %s\n", nullName);
    
    char *nullSuffix = getSuffix(NULL);
    printf("Extensao de arquivo invalido: %s\n", nullSuffix);

    int nullSlash = hasSlash(NULL);
    printf("Caminho %s termina em '/': %d\n", "invalido", nullSlash);

    char* nullRemadePath = concatPathFile(NULL, NULL);
    printf("Caminho concatenado com path e name invalidos: %s\n", nullRemadePath);

    printf("\n-------\n\n");

    printf("Caminho completo: %s\n", fullPath);
    
    char *path = getPath(fullPath);
    printf("Caminho do arquivo: %s\n", path);

    char *name = getFileName(fullPath);
    printf("Nome do arquivo: %s\n", name);
    
    char *suffix = getSuffix(name);
    printf("Extensao do arquivo: %s\n", suffix);

    int slash = hasSlash(path);
    printf("Caminho %s termina em '/': %d\n", path, slash);

    char *remadePath = concatPathFile(path, name);
    printf("Caminho concatenado: %s\n", remadePath);

    remadePath = concatPathFile(NULL, name);
    printf("Caminho concatenado com path invalido: %s\n", remadePath);

    remadePath = concatPathFile(path, NULL);
    printf("Caminho concatenado com name invalido: %s\n", remadePath);

    free(path);
    free(nullPath);
    free(name);
    free(nullName);
    free(suffix);
    free(nullSuffix);
    free(remadePath);
    free(nullRemadePath);
    return 0;
}
