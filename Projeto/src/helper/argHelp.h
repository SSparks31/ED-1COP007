#ifndef LIB_ARGHELP_H
#define LIB_ARGHELP_H

extern char *optarg;
/* Armazena ponteiro para argumento da ultima opcao lida por `getArguments`, ou NULL caso opcao nao contenha argumentos */

extern int optind;
/* Indica proximo argumento de argv a ser lido */

int getArguments(int argc, char *argv[], char *optstring);

/* Dados uma quantidade de argumentos `argc`, um vetor de argumentos `argv`, e uma string `optstring`, percorre `argv` procurando por opcoes nomeadas */
/* Cada caracter em `optstring` representa uma opcao a ser procurada. i.e.: caso `optstring` seja "abc", procura por "-a", "-b", e "-c" */
/* Caso caracter seja seguido de ':', armazena argumento seguinte em `optarg` */
/* A cada chamada da funcao, variavel `optind` e incrementada e indica proximo argumento a ser lido */

/* Valor de retorno: caracter da opcao (i.e.: opcao -f retorna 'f') */
/* Caso opcao encontrada nao esteja presente em `optstring`, retorna '?' */
/* Caso encontre argumento nao precedido de -, retorna -1, indicando fim das opcoes */
/* Caso `optind` seja igual ou maior a `argc`, retorna -1 */
/* Caso `optstring` seja invalida ou vazia, retorna -1 */

/* Funcionamento similar a função `getopt()` da biblioteca <getopt.h>, tambem disponivel em <unistd.h> dependendo da implementacao de C utilizada */
/* Ler mais: https://man7.org/linux/man-pages/man3/getopt.3.html */

/**/

#endif