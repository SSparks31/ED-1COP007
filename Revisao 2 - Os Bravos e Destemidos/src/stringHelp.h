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

char *stripQuotes(char *res, char *str);
/* Dadas uma string valida `res` e uma string valida `str`, remove aspas posicionadas no comeco e final de `str` e armazena resultado em `res` */
/* Caso `str` seja invalida ou vazia, res recebe string vazia */
/* Caso `str` nao contenha aspas, nao ocorre modificacao */
/* Valor de retorno: ponteiro para primeiro caracter de `res` */
/* Ex.: stripQuotes(res, "\"Batata") -> res recebe "Batata"; */

#endif