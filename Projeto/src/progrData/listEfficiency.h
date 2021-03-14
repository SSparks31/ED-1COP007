#ifndef LIB_LISTEFFICIENCY_H
#define LIB_LISTEFFICIENCY_H

#include "./progrData.h"

int reportListEfficiency(progrDataT progrData, int collect, char* collectPath, char* collectTitle);
/* Dados uma estrutura de dados padrao `progrData`, um inteiro `collect`, uma string `collectPath` e uma string `collectTitle`, */
/* inicia, continua ou finaliza relatorio de eficiencia da lista presente em `progrData */
/* Caso `progrData` seja invalida, retorna -1 */
/* Caso `collect` seja 0, nao realiza nenhuma acao */
/* Caso `collect` seja 1, inicia coleta de dados em arquivo temporario */
/* Caso `collect` seja 2, continua coleta de dados em arquivo temporario */
/* Caso `collect` seja 3, finaliza coleta de dados e armazena-os em grafico nomeado por `collectPath`, caso `collectPath` seja valido; retorna -1 caso contrario */
/* Intitula grafico como `collectTitle` caso este seja valido; caso contrario, retorna -1 */
/* Retorna 0 em caso de sucesso */

#endif