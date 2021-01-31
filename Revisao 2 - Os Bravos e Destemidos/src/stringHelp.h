#ifndef LIB_STRINGHELP_H
#define LIB_STRINGHELP_H

#include <stdio.h>
#include <stdlib.h>

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

char *stripQuotes(char *res, char *str);
/* Dadas uma string valida `res` e uma string valida `str`, remove aspas posicionadas no comeco e final de `str` e armazena resultado em `res` */
/* Caso `str` seja invalida ou vazia, res recebe string vazia */
/* Caso `str` nao contenha aspas, nao ocorre modificacao */
/* Valor de retorno: ponteiro para primeiro caracter de `res` */
/* Ex.: stripQuotes(res, "\"Argumento composto\"") -> res recebe "Argumento composto"; */

char *fgetLine(FILE *instream, char* retString, size_t stringLen);
/* Dados um ponteiro para FILE `instream` valido, uma string `retString` valida e um inteiro `stringLen` maior que zero, le conteudo */
/* de `instream` ate que seja encontrado caracter de newline ou EOF, ou `stringLen` seja alcancado, e armazena resultado em `retString` */
/* Nao insere caracter de newline em `retString` */
/* Caso `instream` ou `retstring` sejam invalidos, ou `stringLen` seja menor que zero, retorna NULL */
/* Valor de retorno: ponteiro para primeiro caracter de `retString` */

#endif