#ifndef LIB_PROGRDATA_H
#define LIB_PROGRDATA_H

/* Programa de analise de arquivos .geo, contendo informacoes de diversos retangulos, e .qry, contendo pesquisas sobre os retangulos */

#include "../list/list.h"

typedef struct progrData* progrDataT;

progrDataT createProgrData(char* inputPath, char* outputPath, char* geoName, char* qryName, int collect);
/* Dadas as strings `inputPath`, `outputPath`, `geoName`, `qryName`, e o inteiro `collect`, */
/* cria estrutura responsavel por armazenar e repassar informacoes vitais do programa */
/* Caso `outputPath` ou `geoName` sejam invalidas ou vazias, retorna NULL */

char* getInputPathProgrData(progrDataT progrData);
/* Dada a estrutura `progrData`, retorna caminho de entrada nela armazenado */
/* Caso `progrData` seja invalida, retorna NULL */

char* getOutputPathProgrData(progrDataT progrData);
/* Dada a estrutura `progrData`, retorna caminho de saida nela armazenado */
/* Caso `progrData` seja invalida, retorna NULL */

char* getGeoNameProgrData(progrDataT progrData);
/* Dada a estrutura `progrData`, retorna nome de arquivo .geo nela armazenado */
/* Caso `progrData` seja invalida, retorna NULL */

char* getQryNameProgrData(progrDataT progrData);
/* Dada a estrutura `progrData`, retorna nome de arquivo .qry nela armazenado */
/* Caso `progrData` seja invalida, retorna NULL */

listT getRectListProgrData(progrDataT progrData);
/* Dada a estrutura `progrData`, retorna lista que armazena retangulos lidos do arquivo .geo */
/* Caso `progrData` seja invalida, retorna NULL */

void setRectListProgrData(progrDataT progrData, listT list);
/* Dada a estrutura `progrData` e uma lista ligada `list`, armazena `list` em `progrData` */
/* Apenas para uso interno; seu uso por modulos nao relacionados pode acarretar em comportamento indefinido */

int getCollectProgrData(progrDataT progrData);
/* Dada a estrutura `progrData`, retorna inteiro representando o argumento de coleta de informacoes para relatorio de eficiencia */
/* Caso `progrData` seja invalida, retorna - 1*/

void destroyProgrData(progrDataT progrData);
/* Dada a estrutura `progrData`, libera memoria por ela alocada */

#endif