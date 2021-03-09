#include "bibliotecas.h"
#include "listaDIN.h"
#include "system.h"
#include "variaveis.h"

int main(int argc, char** argv){
    void* location = createVars();
    getArguments(argc, argv, location);
    lista* teste = createList();
    getData(teste, location);
    showlist(teste);
    mostrarVariaveisDaStruct(location);
}