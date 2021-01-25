#ifndef REVISAOEXH
#define REVISAOEXH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getPath(char *fullPath); /* Dado o nome completamente qualificado de um arquivo, retorna o caminho (excluindo o nome do arquivo), sem '/' no final. */

char *getFileName(char *fullPath); /* Dado o nome completamente qualificado de um arquivo, retorna o nome do arquivo, incluindo a extensao. */

char *getSuffix(char *name); /* Dado um nome de arquivo valido, retorna a sua extensao. */

int hasSlash(char *path); /* Retorna verdadeiro se o caminho “path” termina em '/'; falso, caso contrario. */

char *concatPathFile(char *path, char *fileName); /* Concatena path e fileName, a fim de retornar um caminho completamente qualificado. Caso path nao termine em '/', esta e automaticamente adicionada. */

#endif