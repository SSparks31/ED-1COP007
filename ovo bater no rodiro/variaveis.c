#include "variaveis.h"
typedef struct vars{
    char* DirBaseDeEntrada;           //Diretorio de entrada
    char* DirBaseDeSaida;             //Diretorio de saida
    char* GeoInicial;                 //Arquivo .geo (sem diretorio)
    char* QryConsultas;               //Arquivo .qry (sem diretorio)
    char* NomeQRY;                    //Nome do .qry sem o .qry
    char* NomeGEO;                    //Nome do .geo sem o .geo
    char* NomeArqSVGFinal;            //Nome do .svg final sem o .svg
    char* TituloGrafFinal;            //Titulo do grafico final
    char* PathArquivoGeoInicial;      //Path ate o .geo inicial
    char* PathArquivoQryAtual;        //Path ate o .qry que esta sendo usado
    char* PathDoSvgDoGeoSemMudanca;   //Path ate o svg que sera gerado sem alteracoes
    char* PathDoSvgComOQryExecutado;  //Path ate o svg com as alteracoes do qry
    char* PathDoTXTComOQryExecutado;  //Path ate o txt com as alteracoes do qry
    char* PathSVGFinalGrafico;        //Path ate o .svg final com o grafico
    char* PathTXTFinal;               //Path ate o .txt final
    bool IbExecutado;
    bool CbExecutado;
    bool FbExecutado;
    bool Fail;
    bool Consultafeita;
    bool BBIexecutado;
    bool BBIDexecutado;
    bool TPExecutado;
    bool TPRExecutado;
    bool FileGeo;
    bool PathSaida;
    bool dinamica;
    bool estatica;
    bool iidExecutado;
    long int visitas;
    int tamanhoLista;
    int numOfRect;
    long int tamanho;
    int tamanhoOriginal;
}vars;

void* createVars(){
    vars* aux = calloc(1, sizeof(vars));
    aux->DirBaseDeEntrada = calloc(100, sizeof(char));
    aux->DirBaseDeSaida = calloc(100, sizeof(char));
    aux->GeoInicial = calloc(100, sizeof(char));
    aux->QryConsultas = calloc(100, sizeof(char));
    aux->NomeQRY = calloc(100, sizeof(char));
    aux->NomeGEO = calloc(100, sizeof(char));
    aux->NomeArqSVGFinal = calloc(100, sizeof(char));
    aux->TituloGrafFinal = calloc(100, sizeof(char));
    aux->PathArquivoGeoInicial = calloc(100, sizeof(char));
    aux->PathArquivoQryAtual = calloc(100, sizeof(char));
    aux->PathDoSvgDoGeoSemMudanca = calloc(100, sizeof(char));
    aux->PathDoSvgComOQryExecutado = calloc(100, sizeof(char));
    aux->PathDoTXTComOQryExecutado = calloc(100, sizeof(char));
    aux->PathSVGFinalGrafico = calloc(100, sizeof(char));
    aux->PathTXTFinal = calloc(100, sizeof(char));
    return aux;
}

char* getDirBaseDeEntrada(void* variaveis){
    vars* aux = variaveis;
    return aux->DirBaseDeEntrada;
}
char* getDirBaseDeSaida(void* variaveis){
    vars* aux = variaveis;
    return aux->DirBaseDeSaida;
}
char* getGeoInicial(void* variaveis){
    vars* aux = variaveis;
    return aux->GeoInicial;
}
char* getQryConsultas(void* variaveis){
    vars* aux = variaveis;
    return aux->QryConsultas;
}
char* getNomeQRY(void* variaveis){
    vars* aux = variaveis;
    return aux->NomeQRY;
}
char* getNomeGEO(void* variaveis){
    vars* aux = variaveis;
    return aux->NomeGEO;
}
char* getNomeArqSVGFinal(void* variaveis){
    vars* aux = variaveis;
    return aux->NomeArqSVGFinal;
}
char* getTituloGrafFinal(void* variaveis){
    vars* aux = variaveis;
    return aux->TituloGrafFinal;
}
char* getPathArquivoGeoInicial(void* variaveis){
    vars* aux = variaveis;
    return aux->PathArquivoGeoInicial;
}
char* getPathArquivoQryAtual(void* variaveis){
    vars* aux = variaveis;
    return aux->PathArquivoQryAtual;
}
char* getPathDoSvgDoGeoSemMudanca(void* variaveis){
    vars* aux = variaveis;
    return aux->PathDoSvgDoGeoSemMudanca;
}
char* getPathDoSvgComOQryExecutado(void* variaveis){
    vars* aux = variaveis;
    return aux->PathDoSvgComOQryExecutado;
}
char* getPathDoTXTComOQryExecutado(void* variaveis){
    vars* aux = variaveis;
    return aux->PathDoTXTComOQryExecutado;
}
char* getPathSVGFinalGrafico(void* variaveis){
    vars* aux = variaveis;
    return aux->PathSVGFinalGrafico;
}
char* getPathTXTFinal(void* variaveis){
    vars* aux = variaveis;
    return aux->PathTXTFinal;
}
bool* getIbExecutado(void* variaveis){
    vars* aux = variaveis;
    return &aux->IbExecutado;
}
bool* getCbExecutado(void* variaveis){
    vars* aux = variaveis;
    return &aux->CbExecutado;
}
bool* getFbExecutado(void* variaveis){
    vars* aux = variaveis;
    return &aux->FbExecutado;
}
bool* getFail(void* variaveis){
    vars* aux = variaveis;
    return &aux->Fail;
}
bool* getConsultafeita(void* variaveis){
    vars* aux = variaveis;
    return &aux->Consultafeita;
}
bool* getBBIexecutado(void* variaveis){
    vars* aux = variaveis;
    return &aux->BBIexecutado;
}
bool* getBBIDexecutado(void* variaveis){
    vars* aux = variaveis;
    return &aux->BBIDexecutado;
}
bool* getTPExecutado(void* variaveis){
    vars* aux = variaveis;
    return &aux->TPExecutado;
}
bool* getTPRExecutado(void* variaveis){
    vars* aux = variaveis;
    return &aux->TPRExecutado;
}
bool* getFileGeo(void* variaveis){
    vars* aux = variaveis;
    return &aux->FileGeo;
}
bool* getPathSaida(void* variaveis){
    vars* aux = variaveis;
    return &aux->PathSaida;
}
bool* getdinamica(void* variaveis){
    vars* aux = variaveis;
    return &aux->dinamica;
}
bool* getestatica(void* variaveis){
    vars* aux = variaveis;
    return &aux->estatica;
}
bool* getiidExecutado(void* variaveis){
    vars* aux = variaveis;
    return &aux->iidExecutado;
}
long int getVisitas(void* variaveis){
    vars* aux = variaveis;
    return aux->visitas;
}
int gettamanhoLista(void* variaveis){
    vars* aux = variaveis;
    return aux->tamanhoLista;
}
int getnumOfRect(void* variaveis){
    vars* aux = variaveis;
    return aux->numOfRect;
}
long int gettamanho(void* variaveis){
    vars* aux = variaveis;
    return aux->tamanho;
}
int gettamanhoOriginal(void* variaveis){
    vars* aux = variaveis;
    return aux->tamanhoOriginal;
}

void liberarVariaveisDaStruct(void* locations) {
    vars* wow;
    if (wow->DirBaseDeEntrada) {
        free(wow->DirBaseDeEntrada);
    }
    if (wow->DirBaseDeSaida) {
        free(wow->DirBaseDeSaida);
    }
    if (wow->GeoInicial) {
        free(wow->GeoInicial);
    }
    if (wow->QryConsultas) {
        free(wow->QryConsultas);
    }
    if (wow->NomeArqSVGFinal) {
        free(wow->NomeArqSVGFinal);
    }
    if (wow->TituloGrafFinal) {
        free(wow->TituloGrafFinal);
    }
    if (wow->PathSVGFinalGrafico) {
        free(wow->PathSVGFinalGrafico);
    }
    if (wow->NomeGEO) {
        free(wow->NomeGEO);
    }
    if (wow->NomeQRY) {
        free(wow->NomeQRY);
    }
    if (wow->PathArquivoQryAtual) {
        free(wow->PathArquivoQryAtual);
    }
    if (wow->PathDoSvgDoGeoSemMudanca) {
        free(wow->PathDoSvgDoGeoSemMudanca);
    }
    if (wow->PathDoSvgComOQryExecutado) {
        free(wow->PathDoSvgComOQryExecutado);
    }
    if (wow->PathDoTXTComOQryExecutado) {
        free(wow->PathDoTXTComOQryExecutado);
    }
    free(wow->PathArquivoGeoInicial);
}

void mostrarVariaveisDaStruct(void* locations) {
    puts("\n=========================================================");
    vars* aux = locations;
    if (aux->GeoInicial) {
        puts("\nGeoInicial:");
        puts(aux->GeoInicial);
    }
    if (aux->QryConsultas) {
        puts("\nQryConsultas:");
        puts(aux->QryConsultas);
    }
    if (aux->NomeArqSVGFinal) {
        puts("\nNomeArqSVGFinal:");
        puts(aux->NomeArqSVGFinal);
    }
    if (aux->TituloGrafFinal) {
        puts("\nTituloGrafFinal:");
        puts(aux->TituloGrafFinal);
    }
    if (aux->NomeGEO) {
        puts("\nNomeGeo");
        puts(aux->NomeGEO);
    }
    if (aux->NomeQRY) {
        puts("\nNomeQRY");
        puts(aux->NomeQRY);
    }
    if (aux->DirBaseDeEntrada) {
        puts("\nDirBaseDeEntrada:");
        puts(aux->DirBaseDeEntrada);
    }
    if (aux->DirBaseDeSaida) {
        puts("\nDirBaseDeSaida:");
        puts(aux->DirBaseDeSaida);
    }
    if (aux->PathSVGFinalGrafico) {
        puts("\nPathSVGFinalGrafico:");
        puts(aux->PathSVGFinalGrafico);
    }
    if (aux->PathArquivoQryAtual) {
        puts("\nPathArquivoQryAtual:");
        puts(aux->PathArquivoQryAtual);
    }
    if (aux->PathDoSvgDoGeoSemMudanca) {
        puts("\nPathDoSvgDoGeoSemMudanca:");
        puts(aux->PathDoSvgDoGeoSemMudanca);
    }
    if (aux->PathDoSvgComOQryExecutado) {
        puts("\nPathDoSvgComOQryExecutado:");
        puts(aux->PathDoSvgComOQryExecutado);
    }
    if (aux->PathDoTXTComOQryExecutado) {
        puts("\nPathDoTXTComOQryExecutado:");
        puts(aux->PathDoTXTComOQryExecutado);
    }
    puts("\nPathArquivoGeoInicial:");
    puts(aux->PathArquivoGeoInicial);
    puts("=========================================================\n");
}