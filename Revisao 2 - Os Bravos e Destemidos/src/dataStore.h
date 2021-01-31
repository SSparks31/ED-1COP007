#ifndef LIB_DATASTORE_H
#define LIB_DATASTORE_H

#include <stdio.h>

typedef struct dataStore {
    char *varX;
    char *varY;
    char *varZ;

    char **parameters;

    char *currentDir;
    char *fileName;
    char *fileSuffix;
} dataStoreT;

typedef struct dataFile {
    FILE *file;
    char mode[2];
} dataFileT;

dataStoreT *createDataStore(char *defaultDir, char **params);
/* Cria estrutura responsavel por armazenar variaveis e parametros do programa */
/* Caso `defaultDir` seja um caminho valido, inicializa diretorio atual do programa com seu valor */
/* Caso haja problema de alocacao de memoria, retorna NULL */

void destroyDataStore(dataStoreT **dataStore);
/* Destroi estrutura do programa */
/* Substitui ponteiro original por NULL para fim de controle */

dataFileT *createDataFile(char *path, char *mode);
/* Cria estrutura responsavel por armazenar stream de arquivo e modo */
/* Caso haja problema de alocacao de memoria, retorna NULL */
/* Caso nao seja possivel abrir o arquivo denominado por `path`, retorna NULL*/

void destroyDataFile(dataFileT **dataFile);
/* Destroi estrutura do arquivo */
/* Substitui ponteiro original por NULL para fim de controle */

#endif