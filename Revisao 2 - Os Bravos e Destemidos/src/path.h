#ifndef LIB_PATH_H
#define LIB_PATH_H

/* Modulo voltado a manipulacao de nomes de arquivos e caminhos */
/* Nome completamente qualificado: Inclui caminho, absoluto ou relativo, nome e extensão do arquivo, caso aplicavel */

char *getPath(char *res, char *fullPath);
/* Dados uma string valida `res` e um nome de arquivo possivelmente completamente qualificado `fullPath`, armazena o seu caminho, sem '/' no final, em `res` */
/* Caso `fullPath` seja invalida ou vazia, `res` recebe string vazia */
/* Caso `fullPath` nao contenha caminho, sera considerado caminho relativo, e res recebe "./" */
/* Valor de retorno: ponteiro para primeiro caracter de `res` */
/* Ex.: getPath(res, "/home/usuarios/ze/a.txt") -> res recebe "/home/usuarios/ze" */

char *getFileName(char *res, char *fullPath);
/* Dados uma string valida `res` e um nome de arquivo possivelmente completamente qualificado `fullPath`, armazena apenas o nome do arquivo, incluindo extensao, em `res` */
/* Caso `fullPath` seja invalida ou vazia, `res` recebe string vazia */
/* Caso `fullPath` nao contenha nome de arquivo (ou seja, termine em '/'), `res` recebe string vazia */
/* Valor de retorno: ponteiro para primeiro caracter de `res` */
/* Ex.: getFileName(res, "/home/usuarios/ze/a.txt") -> res recebe "a.txt" */

char *getSuffix(char *res, char *fullPath);
/* Dados uma string valida `res` e um nome de arquivo possivelmente completamente qualificado `fullPath`, armazena apenas a sua extensao em `res` */
/* Caso `fullPath` seja invalida ou vazia, `res` recebe string vazia */
/* Caso `fullPath` nao contenha nome de arquivo (ou seja, termine em '/'), `res` recebe string vazia */
/* Caso `fullPath` nao contenha extensao, res recebe string vazia */
/* Valor de retorno: ponteiro para primeiro caracter de `res` */
/* Ex.: getSuffix(res, "/home/usuarios/ze/a.txt") -> res recebe "txt" */

int hasSlash(char *path);
/* Dado um caminho de arquivo `path`, retorna 1 caso termine em '/', e 0 caso contrario */
/* Caso path seja invalida ou vazia, retorna -1 */
/* Ex.: hasSlash("/home/usuarios/ze") -> funcao retorna 0 */

char *concatFileSuffix(char *res, char *fileName, char *suffix);
/* Dados uma string valida `res`, um nome de arquivo `fileName` e extensao `suffix`, concatena ambos, separando-os com '.' caso necessario, e armazena resultado em `res` */
/* Caso `fileName` seja invalida ou vazia, `res` recebe string vazia */
/* Caso `suffix` seja invalida ou vazia, `res` recebe conteudo de `fileName` */
/* Caso `fileName` ja contenha extensao, nova extensao é concatenada ao final */
/* Valor de retorno: ponteiro para primeiro caracter de `res` */
/* Ex.: concatFileSuffix(res, "a.txt", "old") -> res recebe "a.txt.old" */

char *concatPathFile(char *res, char *path, char *fileName);
/* Dados uma string valida `res`, um caminho absoluto ou relativo `path` e nome de arquivo `fileName`, concatena ambos, separando-os com '/' caso necessario, e armazena resultado em `res` */
/* Caso `fileName` seja invalida ou vazia, `res` recebe string vazia */
/* Caso `path` seja invalida ou vazia, caminho e considerado relativo */
/* Caso `path` ja contenha arquivo, ou `fileName` ja contenha caminho, `res` recebe string vazia */
/* Valor de retorno: ponteiro para primeiro caracter de `res` */
/* Ex.: concatPathFile(res, "/home/usuarios/ze", "a.txt") -> res recebe "/home/usuarios/ze/a.txt" */

#endif