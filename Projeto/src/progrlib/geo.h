#ifndef LIB_GEO_H
#define LIB_GEO_H 

/* Modulo voltado a leitura e execucao de comandos de arquivos .geo */

#include "./progrData.h"

void geoParser(progrData data);
/* Dada estrutura de armazenamento de dados `progrData`, analisa e executa comandos lidos no arquivo .geo indicado pelo argumento -f */
/* Responsavel por inicializar a lista de retangulos presente em `progrData` */
/* Caso arquivo nao seja encontrado, nao realiza nenhuma acao */
/* Caso `progrData` seja invalida, nao realiza nenhuma acao */

#endif