#ifndef LIB_SVG_H
#define LIB_SVG_H

#include <stdio.h>

#include "./rect.h"
#include "./line.h"
#include "./circle.h"

FILE* startSVG(char* path, char* fileName);
/* Dadas as strings `path` e `fileName`, cria arquivo .svg no diretorio `path`, com nome `fileName */
/* Inicializa tag <svg> no arquivo */
/* Caso nao seja possivel criar arquivo, retorna NULL */
/* Retorna ponteiro para arquivo criado */

int addRectToSVG(FILE* svgFile, rectT rect);
/* Dados um ponteiro para arquivo `svgFile` e um retangulo `rect`, desenha `rect` em `svgFile` */
/* Caso `svgFile` ou `rect` sejam invalidos, retorna -1 */
/* Retorna 0 em caso de sucesso */

int addDottedRectToSVG(FILE* svgFile, rectT rect);
/* Dados um ponteiro para arquivo `svgFile` e um retangulo `rect`, desenha `rect` em `svgFile` com borda pontilhada*/
/* Caso `svgFile` ou `rect` sejam invalidos, retorna -1 */
/* Retorna 0 em caso de sucesso */

int addLineToSVG(FILE* svgFile, lineT line);
/* Dados um ponteiro para arquivo `svgFile` e uma reta `line`, desenha `line` em `svgFile` */
/* Caso `svgFile` ou `line` sejam invalidos, retorna -1 */
/* Retorna 0 em caso de sucesso */

int addDottedLineToSVG(FILE* svgFile, lineT line);
/* Dados um ponteiro para arquivo `svgFile` e uma reta `line`, desenha `line` de forma pontilhada em `svgFile` */
/* Caso `svgFile` ou `line` sejam invalidos, retorna -1 */
/* Retorna 0 em caso de sucesso */

int addCircleToSVG(FILE* svgFile, circleT circle);
/* Dados um ponteiro para arquivo `svgFile` e um circulo `circle`, desenha `circle` em `svgFile` */
/* Caso `svgFile` ou `circle` sejam invalidos, retorna -1 */
/* Retorna 0 em caso de sucesso */

int addDottedCircleToSVG(FILE* svgFile, circleT circle);
/* Dados um ponteiro para arquivo `svgFile` e um circulo `circle`, desenha `circle` em `svgFile` com borda pontilhada */
/* Caso `svgFile` ou `circle` sejam invalidos, retorna -1 */
/* Retorna 0 em caso de sucesso */

int finishSVG(FILE* svgFile);
/* Dado um ponteiro para arquivo `svgFile`, encerra tag </svg> e fecha arquivo */
/* Caso `svgFile` seja invalido, retorna -1 */
/* Retorna 0 em caso de sucesso */

#endif