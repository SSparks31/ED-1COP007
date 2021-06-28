#include "util.h"

#ifndef ARGVFUNC_H
#define ARGVFUNC_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "GeometricForms/circle.h"
#include "GeometricForms/rectangle.h"
/*Retorno padrão de erro para ponteiros: NULL */
/*Retorno padrão de erro para numericos: -1   */

typedef void* Endereco;

/*
Retorna o nome do arquivo .qry de entrada
*/
String get_input_qry_file_name(Endereco paths);


/*
Retorna o endereço da pasta que contém os arquivos de entrada
*/
String get_inputs_dir_path(Endereco paths);


/*
Retorna o nome do arquivo .geo de entrada
*/
String get_input_geo_file_name(Endereco paths);


/*
Retorna o endereço da pasta que contém os arquivos de saída
*/
String get_outputs_dir_path(Endereco paths);


String get_output_svg_qry_full_path(Endereco Path);

/*
Retorna o path absoluto do .geo de input
*/
String get_input_geo_full_path(Endereco paths);


int set_output_svg_full_path(Endereco Path);


String get_output_svg_full_path(Endereco Path);


String get_output_txt_qry_full_path(Endereco Path);


/*
Retorna o path absoluto do .qry de input
*/
String get_input_qry_full_path(Endereco paths);


/*
Retorna a quantidade de memória que a estrutura de um endereco ocupa
*/
void *paths_factory();

/*
Função que gerencia os inputs de comando do terminal
*/
int argv_processor(String *ARGV, void *Paths, void *Contr);


/*
Libera a memória do Path
*/
int destroy_paths(Endereco Path);


/*
Imprime todas informações para debug
Escreva um texto em 'message' para reconhecer as informações no terminal
*/
int debug_paths(Endereco Path,String message);

/**/
#endif