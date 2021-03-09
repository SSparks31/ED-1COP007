#include "bibliotecas.h"
#include "listaDIN.h"
#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED
    void getData(listaDupla sequence, void* location); //Funcao para ler o .geo
    // void S_getData(listaEstatica sequence, char* PathArquivoGeoInicial);
    // void getFunctions(listaDupla sequence, char* ArquivoQry); //leitura do .qry
    // void S_getFunctions(listaEstatica sequence, char* ArquivoQry);
    // void freeAllandClose(FILE* geo, FILE* svg_source);
    void showlist(listaDupla sequence);
    void getArguments(int argc, char** argv, void* locations);
    // void checarColetas();
    // void createTempFiles();
    // void removeTempFiles();
    // void mostrarVariaveisGlobais();
#endif