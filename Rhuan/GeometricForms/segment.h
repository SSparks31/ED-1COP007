#include "../util.h"
#include "../DataStructures/list.h"

#ifndef SEGMENT_H
#define SEGMENT_H

typedef void* Segmento;

typedef void* Vertice;

#define sizeofSeg 8
#define sizeofVtx 80

void destroy_segment(Segmento __obj);
void print_tree_seg(void* current, int camada);
int tree_remove_segment(void* data1, void* data2);
int vertex_type(void* __src);
int remov_segment(void* seg11, void* seg22);
void* vertex_array_index(void* indexArray, int index);
void* segment_of(void* vtx);
int encoberto(void* current_node, void* vertex);
int search_vertex(void* segment, void* vertex);
void *vertex_factory(double x, double y, String code) ;
int compare(const void *st_point_1, const void *st_point_2) ;
void *segment_factory(void *st_point_1, void *st_point_2, void *st_meteor_impact) ;
int print_segment(void *teste);
int intesec_compare(void *st_point, void *st_seg) ;
void* vertex_array_factory(void* segments);
int destroy_vertex_array(void* st_vertex_array);
int segment_list_recursion(Celula current_node, Lista seg_list, void *meteoro) ;
int destroy_segment_list(Lista seg_list) ;
double point_index(void* __vertex, int __index);
char* code(void* __vertex);
double point_index(void* __vertex, int __index);
double* point(void* __vertex);
void* ini_point(void* __segment);
void* end_point(void* __segment);
void* segcpy(void* __src);
void* vtxcpy(void* __src);
void set_ini_point(void *__seg, void *__point);
void set_end_point(void *__seg, void *__point);
int compare_segment(void* data1, void* data2);

/**/
#endif