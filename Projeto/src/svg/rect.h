#ifndef LIB_RECT_H
#define LIB_RECT_H

/* Modulo voltado ao armazenamento de informacoes utilizadas para criar um retangulo */

typedef struct rect* rectT;

rectT createRect(char* borderColor, char* fillColor, char* opacity, char* ID, char* coordinates);
/* Dadas as strings `borderColor`, `fillColor`, `ID` e `coordinates`, cria retangulo com as informacoes nelas contidas */
/* Caso `borderColor`, `fillColor`, `ID` ou `coordinates` sejam vazias ou invalidas, retorna -1 */
/* Caso `borderColor` ou `fillColor` sejam "@", respectivo atributo e considerado transparente */
/* `coordinates` e uma string contendo as coordenadas x e y de ancora do retangulo, largura e altura, separadas por espaco */
/* `coordinates` e modificada ao longo da funcao, portanto e importante que nao seja passada const char* por acidente */
/* Funcao nao sanitizada; caso `coordinates` nao contenha coordenadas suficientes, constara comportamento indefinido */

char* getIDRect(rectT rect);
/* Dado um retangulo `rect`, retorna seu ID */
/* Caso `rect` seja invalido, retorna NULL */

char* getBorderColorRect(rectT rect);
/* Dado um retangulo `rect`, retorna string representando sua cor de borda */
/* Caso `rect` seja invalido, retorna NULL */

void  setBorderColorRect(rectT rect, char* borderColor);
/* Dado um retangulo `rect` e uma string `borderColor`, atualiza cor de borda de `rect` */
/* Caso `rect` seja invalido, ou `borderColor` invalida ou vazia, nao realiza nenhuma acao  */

char* getFillColorRect(rectT rect);
/* Dado um retangulo `rect`, retorna string representando sua cor de preenchimento */
/* Caso `rect` seja invalido, retorna NULL */

void  setFillColorRect(rectT rect, char* fillColor);
/* Dado um retangulo `rect` e uma string `fillColor`, atualiza cor de preenchimento de `rect` */
/* Caso `rect` seja invalido, ou `fillColor` invalida ou vazia, nao realiza nenhuma acao  */

char* getOpacityRect(rectT rect);
void  setOpacityRect(rectT rect, char* opacity);

char* getXRect(rectT rect);
/* Dado um retangulo `rect, retorna string representando sua coordenada X de ancora */
/* Caso `rect` seja invalido, retorna NULL */

void  setXRect(rectT rect, char* x);
/* Dado um retangulo `rect` e uma string `x`, atualiza coordenada X de ancora de `rect` */
/* Caso `rect` seja invalido, ou `x` invalida ou vazia, nao realiza nenhuma acao  */

char* getYRect(rectT rect);
/* Dado um retangulo `rect`, retorna string representando sua coordenada Y de ancora */
/* Caso `rect` seja invalido, retorna NULL */

void  setYRect(rectT rect, char* y);
/* Dado um retangulo `rect` e uma string `y`, atualiza coordenada Y de ancora de `rect` */
/* Caso `rect` seja invalido, ou `y` invalida ou vazia, nao realiza nenhuma acao  */

char* getWidthRect(rectT rect);
/* Dado um retangulo `rect`, retorna string representando sua largura */
/* Caso `rect` seja invalido, retorna NULL */

void  setWidthRect(rectT rect, char* w);
/* Dado um retangulo `rect` e uma string `w`, atualiza largura de `rect` */
/* Caso `rect` seja invalido, ou `w` invalida ou vazia, nao realiza nenhuma acao  */

char* getHeightRect(rectT rect);
/* Dado um retangulo `rect`, retorna string representando sua altura */
/* Caso `rect` seja invalido, retorna NULL */

void  setHeightRect(rectT rect, char* h);
/* Dado um retangulo `rect` e uma string `h`, atualiza altura de `rect` */
/* Caso `rect` seja invalido, ou `h` invalida ou vazia, nao realiza nenhuma acao  */

void  setCoordinatesRect(rectT rect, char* coordinates);
/* Dado um retangulo `rect` e uma string `coordinates` contendo coordenadas X e Y de ancora, largura e altura, separadas por espaco, atualiza coordenadas de `rect` */
/* Caso `rect` seja invalido, ou `coordinates` invalida ou vazia, nao realiza nenhuma acao  */
/* Funcao nao sanitizada; caso `coordinates` nao contenha coordenadas suficientes, constara comportamento indefinido */

void  destroyRect(rectT rect);
/* Dado um retangulo `rect`, libera toda memoria por ele alocada */
/* Caso `rect` seja invalido, nao realiza nenhuma acao */

#endif