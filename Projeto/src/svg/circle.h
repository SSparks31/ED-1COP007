#ifndef LIB_CIRCLE_H
#define LIB_CIRCLE_H

/* Modulo voltado ao armazenamento de informacoes utilizadas para criar um circulo */

typedef struct circle* circleT;

circleT createCircle(char* borderColor, char* fillColor, char* opacity, char* ID, char* coordinates);
/* Dadas as strings `borderColor`, `fillColor`, `ID` e `coordinates`, cria circulo com as informacoes nelas contidas */
/* Caso `borderColor`, `fillColor`, `ID` ou `coordinates` sejam vazias ou invalidas, retorna -1 */
/* Caso `borderColor` ou `fillColor` sejam "@", respectivo atributo e considerado transparente */
/* `coordinates` e uma string contendo as coordenadas x e y do centro do circulo, assim como seu raio, separados por espaco */
/* `coordinates` e modificada ao longo da funcao, portanto e importante que nao seja passada const char* por acidente */
/* Funcao nao sanitizada; caso `coordinates` nao contenha coordenadas suficientes, constara comportamento indefinido */

char* getIDCircle(circleT circle);
/* Dado um circulo `circle`, retorna seu ID */
/* Caso `circle` seja invalido, retorna NULL */

char* getBorderColorCircle(circleT circle);
/* Dado um circulo `circle`, retorna string representando cor da borda */
/* Caso `circle` seja invalido, retorna NULL */

void  setBorderColorCircle(circleT circle, char* borderColor);
/* Dado um circulo `circle` e uma string `borderColor`, atualiza cor da borda de `circle` */
/* Caso `circle` seja invalido, ou `borderColor` invalida ou vazia, nao realiza nenhuma acao  */

char* getFillColorCircle(circleT circle);
/* Dado um circulo `circle`, retorna string representando cor de preenchimento */
/* Caso `circle` seja invalido, retorna NULL */

void  setFillColorCircle(circleT circle, char* fillColor);
/* Dado um circulo `circle` e uma string `fillColor`, atualiza cor de preenchimento de `circle` */
/* Caso `circle` seja invalido, ou `fillColor` invalida ou vazia, nao realiza nenhuma acao */

char* getOpacityCircle(circleT circle);
void  setOpacityCircle(circleT circle, char* opacity);

char* getXCenterCircle(circleT circle);
/* Dado um circulo `circle`, retorna string representando coordenada X do centro */
/* Caso `circle` seja invalido, retorna NULL */

void  setXCenterCircle(circleT circle, char* xCenter);
/* Dado um circulo `circle` e uma string `xCenter`, atualiza coordenada X do centro de `circle` */
/* Caso `circle` seja invalido, ou `xCenter` invalida ou vazia, nao realiza nenhuma acao  */

char* getYCenterCircle(circleT circle);
/* Dado um circulo `circle`, retorna string representando coordenada Y do centro */
/* Caso `circle` seja invalido, retorna NULL */

void  setYCenterCircle(circleT circle, char* yCenter);
/* Dado um circulo `circle` e uma string `yCenter`, atualiza coordenada Y do centro de `circle` */
/* Caso `circle` seja invalido, ou `yCenter` invalida ou vazia, nao realiza nenhuma acao  */

char* getRadiusCircle(circleT circle);
/* Dado um circulo `circle`, retorna string representando raio */
/* Caso `circle` seja invalido, retorna NULL */

void  setRadiusCircle(circleT circle, char* radius);
/* Dado um circulo `circle` e uma string `radius`, atualiza raio de `circle` */
/* Caso `circle` seja invalido, ou `radius` invalida ou vazia, nao realiza nenhuma acao  */

void  setCoordinatesCircle(circleT circle, char* coordinates);
/* Dado um circulo `circle` e uma string `coordinates` contendo coordenadas X e Y do centro de um circulo, assim como raio, separados por espaco, atualiza coordenadas de `circle` */
/* Caso `circle` seja invalido, ou `coordinates` invalida ou vazia, nao realiza nenhuma acao  */
/* Funcao nao sanitizada; caso `coordinates` nao contenha coordenadas suficientes, constara comportamento indefinido */

void  destroyCircle(circleT circle);
/* Dado um circulo `circle`, libera toda memoria por ele alocada */
/* Caso `circle` seja invalido, nao realiza nenhuma acao */

#endif