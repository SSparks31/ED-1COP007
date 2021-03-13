#ifndef LIB_GEO_H
#define LIB_GEO_H 

/* Modulo voltado a interacao com arquivos .geo */

#include "../progrData/progrData.h"

#include "../list/list.h"

void geoParser(progrDataT progrData);
/* Dada a struct padrao de armazenamento de dados `progrData`, analisa e executa comandos lidos no arquivo .geo indicado pelo argumento -f */
/* Responsavel por inicializar a lista de retangulos presente em `progrData` */
/* Caso `progrData` seja invalida, nao realiza nenhuma acao */

#endif