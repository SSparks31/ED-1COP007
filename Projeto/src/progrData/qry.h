#ifndef LIB_QRY_H
#define LIB_QRY_H

/* Modulo voltado a leitura e execucao de comandos de arquivo .qry */

#include "./progrData.h"

void qryParser(progrDataT progrData);
/* Dada estrutura de armazenamento de dados `progrData`, analisa e executa comandos lidos no arquivo .qry indicado pelo argumento -q */
/* Caso -q nao tenha sido passado ao programa, nao realiza nenhuma acao */
/* Caso arquivo nao seja encontrado, nao realiza nenhuma acao */
/* Caso `progrData` seja invalida, nao realiza nenhuma acao */

#endif