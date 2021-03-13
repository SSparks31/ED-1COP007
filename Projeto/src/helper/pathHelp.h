#ifndef LIB_PATHHELP_H
#define LIB_PATHHELP_H

/* 
* Modulo voltado a manipulacao de nomes de arquivos e caminhos.
* Nome completamente qualificado: Inclui caminho, relativo ou absoluto, e nome do arquivo, incluindo extensao.
* Caracter de separacao de pastas: '/'
*/

char* getPath(char* fullPath); 
/* Dado o nome possivelmente completamente qualificado de um arquivo `fullPath`, retorna o caminho (excluindo o nome do arquivo), sem '/' no final. */
/* Caso `fullPath` seja vazio ou invalido, retorna NULL. */
/* Caso `fullPath` nao inclua caminho, retorna uma string vazia. */
/* Retorna uma string dinamicamente alocada. */

char* getFileName(char* fullPath);
/* Dada uma string `fullPath` representando o nome possivelmente completamente qualificado de um arquivo, retorna o nome do arquivo, incluindo sua extensao. */
/* Caso `fullPath` seja vazio ou invalido, retorna NULL. */
/* Retorna uma string dinamicamente alocada. */

char* getSuffix(char* fileName); 
/* Dada uma string `fileName` representando um nome de arquivo, retorna a sua extensao, sem incluir o '.' no inicio. */
/* Caso `fileName` nao contenha extensao, retorna uma string vazia. */
/* Caso `fileName` seja vazio ou invalido, retorna NULL. */
/* Retorna uma string dinamicamente alocada. */

char* stripSuffix(char* fileName);
/* Dado uma string `fileName`, retorna apenas o nome do arquivo, removendo caminho e extensao */
/* Caso `fileName` seja invalido ou vazio, retorna NULL */
/* Retorna uma string dinamicamente alocada */

int hasSlash(char* path); 
/* Dado uma string `path` representando um caminho, retorna verdadeiro se o dado caminho termina em '/'; falso, caso contrario. */
/* Caso `path` seja vazia ou invalida, retorna -1. */
/* Retorna um inteiro de valor -1, 0 ou 1, representando invalido, falso e verdadeiro, respectivamente. */

char* concatPathFile(char* path, char* fileName); 
/* Dadas duas strings `path` e `fileName`, concatena ambas a fim de retornar um nome de arquivo completamente qualificado. */
/* Caso `path` nao termine em '/', esta e automaticamente adicionada. */
/* Caso apenas `path` seja vazio ou invalido, arquivo e considerado como caminho relativo ao diretorio atual. */
/* Caso `fileName` seja vazio ou invalido, retorna NULL */
/* Retorna uma string dinamicamente alocada. */

char* concatFileSuffix(char* fileName, char* suffix);
/* Dadas duas strings `fileName` e `suffix`, concatena ambas a fim de retornar um nome de arquivo com extensao */
/* Caso `fileName` ja contenha extensao, nova extensao e concatenada ao final */
/* Caso `fileName` seja invalido ou vazio, retorna NULL */
/* Caso `suffix` seja invalido ou vazio, retorna nova string com conteudo identico a fileName */
/* Retorna uma string dinamicamente alocada */

#endif