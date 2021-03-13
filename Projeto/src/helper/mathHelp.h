#ifndef LIB_MATHHELP_H
#define LIB_MATHHELP_H

/* Modulo voltado a funcoes de utilidade relacionadas a matematica */

int max(int a, int b);
/* Dados dois inteiros `a` e `b`, retorna o maior entre eles */

int min(int a, int b);
/* Dados dois inteiros `a` e `b`, retorna o menor entre eles */

double dmax(double a, double b);
/* Dados dois doubles `a` e `b`, retorna o maior entre eles */

double dmin(double a, double b);
/* Dados dois doubles `a` e `b`, retorna o menor entre eles */

int charToNum(char num);
/* Dado um caracter `num` entre '0' e '9', retorna valor inteiro por ele representado */
/* Caso caracter nao pertenca ao intervalo valido, retorna -1 */

int stringToInt(char *num);
/* Dada uma string `num` representando um numero, retorna valor em forma inteira */
/* Caso seja encontrado caracter nao numerico, processo e interrompido e resultado possivelmente parcial e retornado */

double stringToDouble(char *num);
/* Dada uma string `num` representando um numero, retorna valor em forma decimal */
/* Caso seja encontrado caracter nao numerico, processo e interrompido e resultado possivelmente parcial e retornado */

double dpow(double base, double exp);
/* Dados dois doubles `base` e `exp`, retorna `base` elevado a `exp` */


#endif