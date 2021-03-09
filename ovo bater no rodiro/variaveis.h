#ifndef VARIAVEIS_H
#define VARIAVEIS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef void* acessVars;

void* createVars();
char* getDirBaseDeEntrada(void* variaveis);
char* getDirBaseDeSaida(void* variaveis);
char* getGeoInicial(void* variaveis);
char* getQryConsultas(void* variaveis);
char* getNomeQRY(void* variaveis);
char* getNomeGEO(void* variaveis);
char* getNomeArqSVGFinal(void* variaveis);
char* getTituloGrafFinal(void* variaveis);
char* getPathArquivoGeoInicial(void* variaveis);
char* getPathArquivoQryAtual(void* variaveis);
char* getPathDoSvgDoGeoSemMudanca(void* variaveis);
char* getPathDoSvgComOQryExecutado(void* variaveis);
char* getPathDoTXTComOQryExecutado(void* variaveis);
char* getPathSVGFinalGrafico(void* variaveis);
char* getPathTXTFinal(void* variaveis);
bool* getIbExecutado(void* variaveis);
bool* getCbExecutado(void* variaveis);
bool* getFbExecutado(void* variaveis);
bool* getFail(void* variaveis);
bool* getConsultafeita(void* variaveis);
bool* getBBIexecutado(void* variaveis);
bool* getBBIDexecutado(void* variaveis);
bool* getTPExecutado(void* variaveis);
bool* getTPRExecutado(void* variaveis);
bool* getFileGeo(void* variaveis);
bool* getPathSaida(void* variaveis);
bool* getdinamica(void* variaveis);
bool* getestatica(void* variaveis);
bool* getiidExecutado(void* variaveis);
long int getVisitas(void* variaveis);
int gettamanhoLista(void* variaveis);
int getnumOfRect(void* variaveis);
long int gettamanho(void* variaveis);
int gettamanhoOriginal(void* variaveis);
void liberarVariaveisDaStruct(void* locations);
void mostrarVariaveisDaStruct(void* locations);
#endif