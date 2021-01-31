#ifndef LIB_STRINGSEARCH_H
#define LIB_STRINGSEARCH_H

char *findCharacter(char *str, char query);
/* Dado uma string `str` e um caracter `query`, retorna ponteiro para primeira instancia de `query` em `str` */
/* Caso `str` seja invalida ou vazia, retorna NULL */
/* Caso `query` nao seja encontrado em `str`, retorna NULL */

char *rfindCharacter(char *str, char query);
/* Dado uma string `str` e um caracter `query`, retorna ponteiro para ultima instancia de `query` em `str` */
/* Caso `str` seja invalida ou vazia, retorna NULL */
/* Caso `query` nao seja encontrado em `str`, retorna NULL */

#endif