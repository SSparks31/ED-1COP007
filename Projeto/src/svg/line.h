#ifndef LIB_LINE_H
#define LIB_LINE_H

/* Modulo voltado ao armazenamento de informacoes utilizadas para criar uma reta */

typedef struct line* lineT;

lineT createLine(char* color, char* coordinates);
/* Dadas as strings `color` e `coordinates`, cria linha com as informacoes nelas contidas */
/* Caso `fillColor` ou `coordinates` sejam vazias ou invalidas, retorna -1 */
/* `coordinates` e uma string contendo as coordenadas X e Y do comeco e fim da reta, separadas por espaco */
/* `coordinates` e modificada ao longo da funcao, portanto e importante que nao seja passada const char* por acidente */
/* Funcao nao sanitizada; caso `coordinates` nao contenha coordenadas suficientes, constara comportamento indefinido */

char* getColorLine(lineT line);
/* Dada uma reta `line`, retorna string representando sua cor */
/* Caso `line` seja invalida, retorna NULL */

void  setColorLine(lineT line, char* color);
/* Dada uma reta `line` e uma string `color`, atualiza cor de `line` */
/* Caso `line` seja invalida, ou `color` invalida ou vazia, nao realiza nenhuma acao */

char* getX1Line(lineT line);
/* Dada uma reta `line`, retorna string representando coordenada X de uma de suas pontas */
/* Caso `line` seja invalida, retorna NULL */

void  setX1Line(lineT line, char* x1);
/* Dada uma reta `line` e uma string `x1`, atualiza coordenada X de uma das pontas de `line` */
/* Caso `line` seja invalida, ou `x1` invalida ou vazia, nao realiza nenhuma acao */

char* getY1Line(lineT line);
/* Dada uma reta `line`, retorna string representando coordenada Y de uma de suas pontas */
/* Caso `line` seja invalida, retorna NULL */

void  setY1Line(lineT line, char* y1);
/* Dada uma reta `line` e uma string `y1`, atualiza coordenada Y de uma das pontas de `line` */
/* Caso `line` seja invalida, ou `y1` invalida ou vazia, nao realiza nenhuma acao */

char* getX2Line(lineT line);
/* Dada uma reta `line`, retorna string representando coordenada X de uma de suas pontas */
/* Caso `line` seja invalida, retorna NULL */

void  setX2Line(lineT line, char* x2);
/* Dada uma reta `line` e uma string `x2`, atualiza coordenada X de uma das pontas de `line` */
/* Caso `line` seja invalida, ou `x2` invalida ou vazia, nao realiza nenhuma acao */

char* getY2Line(lineT line);
/* Dada uma reta `line`, retorna string representando coordenada Y de uma de suas pontas */
/* Caso `line` seja invalida, retorna NULL */

void  setY2Line(lineT line, char* h);
/* Dada uma reta `line` e uma string `y2`, atualiza coordenada Y de uma das pontas de `line` */
/* Caso `line` seja invalida, ou `y2` invalida ou vazia, nao realiza nenhuma acao */

void  setCoordinatesLine(lineT line, char* coordinates);
/* Dada uma reta `line` e uma string `coordinates` contendo coordenadas X e Y de ambas as pontas de uma reta, separadas por espaco, atualiza coordenadas de `line` */
/* Caso `line` seja invalida, ou `coordinates` invalida ou vazia, nao realiza nenhuma acao  */
/* Funcao nao sanitizada; caso `coordinates` nao contenha coordenadas suficientes, constara comportamento indefinido */

void  destroyLine(lineT line);
/* Dada uma reta `line`, libera toda memoria por ela alocada */
/* Caso `line` seja invalido, nao realiza nenhuma acao */

#endif