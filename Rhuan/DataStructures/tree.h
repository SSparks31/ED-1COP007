#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util.h"

#ifndef TREE_H
#define TREE_H

typedef void* Arvore;

typedef void* Noh;

typedef void* Folha;

/*
Cria uma árvore de um tipo específico

Tipos disponíveis: kd , busca -> teste
*/
Arvore tree_factory(int type, int data_type);

/*
Retorna o right_son de OBJ
*/
void* right_son(void* __obj);

/*
Retorna o left_son de OBJ
*/
void* left_son(void* __obj);

void* root(void* st_node);

/*
Cria um elemento com o conteudo de data e o insere na arvore
*/
int insert_tree(Arvore st_tree, void* data, int (*compare_nodes)(void* node1, void* node2), int (*set_kd)(void* __obj, const int __dp));

/*
Retorna um valor correspondende ao tipo da arvore:

0 - kd
1 - busca
*/
int tree_type(Arvore st_tree);

int data_type(Arvore st_tree);

/*
Função de debug da arvore
*/
int debug_tree(Arvore st_tree, String message, int (*print_node)(void* data_node));

/*
Remove o elemento da arvore
*/
int remove_element_tree(Arvore st_tree, void* data, int (*compare_nodes)(void* node1, void* node2), int (*set_kd)(void* __obj, const int __dep), int (*free_data)(void* __data), int free_data_cont);

/*
Libera toda a memória da arvore e retorna NULL
*/
Arvore destroy_tree(Arvore st_tree, int (*free_data)(void* __data), int free_data_cont);

void* father(void* __node);

int destroy_node(void* st_current_node, int (*free_data)(void* __data), int free_data_cont);

/*
Procura por um elemento na arvore comparando data

Retorna o enderece do node, caso seja encontrado
*/
Noh search_tree(Arvore st_tree, void* data, int (*compare_nodes)(void* node1, void* node2));

int print_circle_tree_svg(FILE* full_path, double objects_opacity, void* objects);

int print_rectangle_tree_svg(FILE* full_path, double objects_opacity, void* objects);

double funcao(Arvore arvore, double x, double y);

void* get_data(void* st_celula);

int run_tree(Arvore st_tree, String message, int (*print_node)(void* data_node));

int get_visible(void* st_node);

/**/
#endif