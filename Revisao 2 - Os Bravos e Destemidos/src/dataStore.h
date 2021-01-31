#ifndef LIB_DATASTORE_H
#define LIB_DATASTORE_H

#include <stdio.h>

typedef struct dataFile {
    FILE *file;
    char mode[2];
} dataFileT;

typedef struct dataStore {
    char *varX;
    char *varY;
    char *varZ;

    char **parameters;
    int numParameters;

    char *currentDir;
    char *fileName;
    char *fileSuffix;

    dataFileT fileList[10];
} dataStoreT;

dataStoreT *createDataStore(char *defaultDir, int numParams, char **params);
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

void setVarX(dataStoreT *dataStore, char *varX); /* Altera valor da variavel x do programa */
char *getVarX(dataStoreT *dataStore); /* Retorna valor da variavel x do programa */

void setVarY(dataStoreT *dataStore, char *varY); /* Altera valor da variavel y do programa */
char *getVarY(dataStoreT *dataStore); /* Retorna valor da variavel y do programa */

void setVarZ(dataStoreT *dataStore, char *varZ); /* Altera valor da variavel z do programa */
char *getVarZ(dataStoreT *dataStore); /* Retorna valor da variavel z do programa */

char *getParam1(dataStoreT *dataStore); /* Retorna valor do parametro 1 do programa */
char *getParam2(dataStoreT *dataStore); /* Retorna valor do parametro 2 do programa */
char *getParam3(dataStoreT *dataStore); /* Retorna valor do parametro 3 do programa */

void setVarD(dataStoreT *dataStore, char *varD); /* Altera valor da variavel d do programa */
char *getVarD(dataStoreT *dataStore); /* Retorna valor da variavel d do programa */

void setVarA(dataStoreT *dataStore, char *varA); /* Altera valor da variavel a do programa */
char *getVarA(dataStoreT *dataStore); /* Retorna valor da variavel a do programa */

void setVarE(dataStoreT *dataStore, char *varE); /* Altera valor da variavel e do programa */
char *getVarE(dataStoreT *dataStore); /* Retorna valor da variavel e do programa */

void addFileToList(dataStoreT *dataStore, int id, char *path, char *mode); /* Cria estrutura dataFileT e armazena na lista do programa */
dataFileT *getFileFromID(dataStoreT *dataStore, int id); /* Retorna estrutura dataFileT com ID requisitado */

#endif