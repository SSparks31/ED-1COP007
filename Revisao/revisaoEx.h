#ifndef REVISAOEXH
#define REVISAOEXH

/* 
* Modulo voltado a manipulacao de nomes de arquivos e caminhos 
* Nome completamente qualificado: Inclui caminho, relativo ou absoluto, e nome do arquivo, incluindo extensao
* Caracter de separacao de pastas: '/'
*/

char *getPath(char *fullPath); 
/* Dado o nome possivelmente completamente qualificado de um arquivo, retorna o caminho (excluindo o nome do arquivo), sem '/' no final. */
/* Caso nome seja vazio ou invalido, retorna NULL */
/* Caso nome nao inclua caminho, retorna uma string vazia */
/* Retorna uma string dinamicamente alocada */

char *getFileName(char *fullPath);
/* Dado o nome possivelmente completamente qualificado de um arquivo, retorna o nome do arquivo, incluindo sua extensao. */
/* Caso nome seja vazio ou invalido, retorna NULL */
/* Retorna uma string dinamicamente alocada */

char *getSuffix(char *name); 
/* Dado um nome de arquivo valido, retorna a sua extensao, sem incluir o '.' no inicio. */
/* Caso arquivo nao tenha extensao, retorna uma string vazia */
/* Caso nome seja vazio ou invalido, retorna NULL */
/* Retorna uma string dinamicamente alocada */

int hasSlash(char *path); 
/* Retorna verdadeiro se o caminho "path" termina em '/'; falso, caso contrario. */
/* Caso nome seja vazio ou invalido, retorna -1 */
/* Retorna um inteiro de valor -1, 0 ou 1, representando invalido, falso e verdadeiro, respectivamente. */

char *concatPathFile(char *path, char *fileName); 
/* Concatena caminho e nome de arquivo validos, a fim de retornar um nome de arquivo completamente qualificado. */
/* Caso caminho nao termine em '/', esta e automaticamente adicionada. */
/* Caso apenas o caminho seja vazio ou invalido, arquivo e considerado como caminho relativo ao diretorio atual */
/* Caso apenas o nome de arquivo seja vazio ou invalido, retorna apenas o caminho */
/* Caso ambos sejam vazios ou invalidos, retorna NULL */
/* Retorna uma string dinamicamente alocada */

#endif