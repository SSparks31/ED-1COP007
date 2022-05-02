#ifndef LIB_pATH_H
#define LIB_HELP_H

/* 
* Modulo voltado a manipulacao de nomes de arquivos e caminhos.
* Nome completamente qualificado: Inclui caminho, relativo ou absoluto, e nome do arquivo, incluindo extensao.
* Caracter de separacao de pastas: '/'
*/

/* Batata */
int get_path(char* result, char* full_path); 

int get_file_name(char* result, char* full_path);

int get_suffix(char* result, char* file_name); 

int strip_suffix(char* result, char* file_name);

int has_slash(char* path); 

int concat_path_file(char* result, char* path, char* file_name); 

int concat_file_suffix(char* result, char* file_name, char* suffix);

#endif