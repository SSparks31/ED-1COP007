#ifndef LIB_STRINGHELP_H
#define LIB_STRINGHELP_H

char *findCharacter(char *str, char query);
/* Dados uma string `str` e um caracter `query`, retorna ponteiro para primeira instancia de `query` em `str` */
/* Caso `str` seja invalida ou vazia, retorna NULL */
/* Caso `query` nao seja encontrado em `str`, retorna NULL */

char *rfindCharacter(char *str, char query);
/* Dados uma string `str` e um caracter `query`, retorna ponteiro para ultima instancia de `query` em `str` */
/* Caso `str` seja invalida ou vazia, retorna NULL */
/* Caso `query` nao seja encontrado em `str`, retorna NULL */

int isEmpty(char *str);
/* Dada uma string `str`, retorna 1 caso ela esteja vazia, 0 caso contrario */
/* Caso `str` seja invalida, retorna -1 */

#endif