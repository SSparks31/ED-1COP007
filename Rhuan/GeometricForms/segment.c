#include "segment.h"

#include <string.h>

#include "../DataStructures/list.h"
#include "../DataStructures/tree.h"
#include "../geometry.h"
#include "../util.h"

typedef struct vertex {
    int type;

    double point[2];

    void *segment;

    char code[50];

} vertex;

typedef struct segment {
    vertex *ini_point;

    vertex *end_point;

} segment;

void destroy_segment(Segmento __obj) {
    free(((segment *)__obj)->ini_point);

    free(((segment *)__obj)->end_point);

    free(__obj);
}

int insert_compare(const void *st_point_1, const void *st_point_2);

void set_end_point(void *__seg, void *__point) {
    ((segment *)__seg)->end_point = __point;
    ((vertex *)__point)->segment = __seg;
    ((vertex *)__point)->type = 0;
}

void set_ini_point(void *__seg, void *__point) {
    ((segment *)__seg)->ini_point = __point;
    ((vertex *)__point)->segment = __seg;
    ((vertex *)__point)->type = 1;
}

vertex *meteor_impact;

void *segment_of(void *vtx) {
    return ((vertex *)vtx)->segment;
}

void *vtxcpy(void *__src) {
    vertex *__dest = calloc(1, sizeof(vertex));

    __dest->point[0] = point_index(__src, 0), __dest->point[1] = point_index(__src, 1);
    __dest->type = vertex_type(__src);

    strcpy(__dest->code, code(__src));

    return __dest;
}

int vertex_type(void *__src) {
    vertex *__vtx = __src;
    return __vtx ? __vtx->type : -1;
}

void *segcpy(void *__src) {
    segment *__dest = calloc(1, sizeof(segment));

    __dest->ini_point = vtxcpy(ini_point(__src));
    __dest->end_point = vtxcpy(end_point(__src));

    return __dest;
}

char *code(void *__vertex) {
    vertex *__ver = __vertex;
    return __ver ? __ver->code : NULL;
}

double point_index(void *__vertex, int __index) {
    double *__point = point(__vertex);
    return __point[__index];
}

double *point(void *__vertex) {
    vertex *__ver = __vertex;
    return __ver ? __ver->point : NULL;
}

int search_vertex(void *segment, void *vertex) {
    double *ve_se_ini = point(ini_point(segment_of(vertex)));
    double *ve_se_end = point(end_point(segment_of(vertex)));

    if (ve_se_ini[0] == point_index(ini_point(segment), 0) && ve_se_ini[1] == point_index(ini_point(segment), 1))
        if (ve_se_end[0] == point_index(end_point(segment), 0) && ve_se_end[1] == point_index(end_point(segment), 1))
            return 0;
    // printf("%lf %lf | %lf %lf\n", point_index(vertex, 0) , point_index(ini_point(segment), 0) , point_index(vertex, 1) , point_index(ini_point(segment), 1));

    //   if (point_index(ini_point(data1), 0) >= point_index(ini_point(data2), 0)) return 1;
    // return -1;

    if (point_index(ini_point(segment), 0) >= point_index(vertex, 0))
        return 1;
    return -1;
}

int remov_segment(void *seg11, void *seg22) {
    vertex *ini_1 = ini_point(seg11), *ini_2 = ini_point(seg22), *end_1 = end_point(seg11), *end_2 = end_point(seg22);
    if (ini_1->point[0] == ini_2->point[0] && ini_1->point[1] == ini_2->point[1])
        if (end_1->point[0] == end_2->point[0] && end_1->point[1] == end_2->point[1])
            return 1;

    return 0;
}

void *ini_point(void *__segment) {
    segment *__seg = __segment;
    return __seg ? __seg->ini_point : NULL;
}

void *end_point(void *__segment) {
    segment *__seg = __segment;
    return __seg ? __seg->end_point : NULL;
}

void *vertex_factory(double x, double y, String code) {
    vertex *output = calloc(1, sizeof(vertex));

    output->point[X] = x, output->point[Y] = y, output->segment = NULL;

    strcpy(output->code, code);

    return output;
}

int insert_compare(const void *st_point_1, const void *st_point_2) {
    const vertex *point_1 = st_point_1;
    const vertex *point_2 = st_point_2;

    if (quadrant(meteor_impact->point, point_1->point) == 4 && quadrant(meteor_impact->point, point_2->point) == 1) return 1;

    if (quadrant(meteor_impact->point, point_1->point) == 1 && quadrant(meteor_impact->point, point_2->point) == 4) return -1;

    if (quadrant(meteor_impact->point, point_1->point) < quadrant(meteor_impact->point, point_2->point)) return 1;

    if (quadrant(meteor_impact->point, point_1->point) > quadrant(meteor_impact->point, point_2->point)) return -1;

    if (slope(meteor_impact->point, point_1->point) < slope(meteor_impact->point, point_2->point)) return -1;

    if (slope(meteor_impact->point, point_1->point) > slope(meteor_impact->point, point_2->point)) return 1;

    double d1 = distancia(meteor_impact->point[0], meteor_impact->point[1], point_1->point[0], point_1->point[1]);

    double d2 = distancia(meteor_impact->point[0], meteor_impact->point[1], point_2->point[0], point_2->point[1]);

    if (d1 < d2) return -1;

    if (d1 > d2) return 1;

    return 0;
}

int compare(const void *st_point_1, const void *st_point_2) {
    const vertex *point_1 = st_point_1;
    const vertex *point_2 = st_point_2;

    if (point_1->point[1] == meteor_impact->point[1]) return -1;

    if (point_2->point[1] == meteor_impact->point[1]) return 1;

    if (quadrant(meteor_impact->point, point_1->point) < quadrant(meteor_impact->point, point_2->point)) return -1;

    if (quadrant(meteor_impact->point, point_1->point) > quadrant(meteor_impact->point, point_2->point)) return 1;

    if (slope(meteor_impact->point, point_1->point) < slope(meteor_impact->point, point_2->point)) return 1;

    if (slope(meteor_impact->point, point_1->point) > slope(meteor_impact->point, point_2->point)) return -1;

    double d1 = distancia(meteor_impact->point[0], meteor_impact->point[1], point_1->point[0], point_1->point[1]);

    double d2 = distancia(meteor_impact->point[0], meteor_impact->point[1], point_2->point[0], point_2->point[1]);

    if (d1 < d2) return -1;

    if (d1 > d2) return 1;

    if (point_1->type == 1) return -1;

    if (point_2->type == 1) return 1;

    return 0;
}

int encoberto(void *current_node, void *vertex) {
    if (!current_node) return 1;

    if (right_son(current_node))
        if (encoberto(right_son(current_node), vertex)) return 1;

    if (left_son(current_node))
        if (encoberto(left_son(current_node), vertex)) return 1;

    if (point_index(ini_point(get_data(current_node)), 0) == point_index(end_point(get_data(current_node)), 0))
        if (point_index(ini_point(get_data(current_node)), 0) < point_index(vertex, 0))
            return 1;

    if (point_index(ini_point(get_data(current_node)), 1) == point_index(end_point(get_data(current_node)), 1))
        if (point_index(ini_point(get_data(current_node)), 1) < point_index(vertex, 1))
            return 1;

    //if (slope(point(ini_point(get_data(current_node))), point(vertex)) < slope(point(ini_point(get_data(current_node))), point(end_point(get_data(current_node))))) return 1;
    return 0;
}

void *segment_factory(void *st_point_1, void *st_point_2, void *st_meteor_impact) {
    segment *output = calloc(1, sizeof(segment));

    meteor_impact = st_meteor_impact;

    vertex *point_1 = st_point_1, *point_2 = st_point_2;

    point_1->segment = point_2->segment = output;

    if (insert_compare(point_1, point_2) == 1) {
        output->ini_point = point_1, output->end_point = point_2;

    } else {
        output->ini_point = point_2, output->end_point = point_1;
    }

    output->ini_point->type = 1;
    output->end_point->type = 0;

    //print_segment(output);

    return output;
}

int print_segment(void *teste) {
    segment *data = teste;

    printf(" Ini = [%lf,%lf] - ", data->ini_point->point[0], data->ini_point->point[1]);
    printf("End = [%lf,%lf]\n", data->end_point->point[0], data->end_point->point[1]);

    return 1;
}

int intesec_compare(void *st_point, void *st_seg) {
    vertex *point = st_point;
    segment *seg = st_seg;

    printf("%lf %lf\n\n\n", point->point[0], point->point[1]);
    if (point->point[Y] > seg->end_point->point[Y] && point->point[Y] < seg->ini_point->point[Y])
        if (point->point[X] < seg->end_point->point[X])
            return 1;

    return 0;
}

int compare_segment(void *data1, void *data2) {
    if (point_index(ini_point(data1), 0) >= point_index(ini_point(data2), 0)) return 1;
    return -1;
}

int tree_remove_segment(void *data1, void *data2) {
    if (point_index(ini_point(data1), 0) > point_index(ini_point(data2), 0)) return 1;
    if (point_index(ini_point(data1), 0) < point_index(ini_point(data2), 0)) return -1;
    if (point_index(ini_point(data1), 1) == point_index(ini_point(data2), 1)) return 0;
    return 1;
}

void *vertex_array_index(void *__indexArray, int __index) {
    vertex *out = calloc(1, sizeofVtx);

    vertex *indexA = __indexArray;
    out->point[0] = indexA[__index].point[0];
    out->point[1] = indexA[__index].point[1];

    out->segment = indexA[__index].segment;

    strcpy(out->code, indexA[__index].code);

    out->type = indexA[__index].type;

    return out;
}

void print_tree_seg(void *current, int camada) {
    for (int i = 0; i < camada; i++) {
        printf("\t");
    }

    if (!current) return;

    printf("Current: %p Father: %p ", current, father(current));
    print_segment(get_data(current));

    if (right_son(current))
        print_tree_seg(right_son(current), camada + 1);

    if (left_son(current))
        print_tree_seg(left_son(current), camada + 1);
}

void *vertex_array_factory(void *segments) {
    vertex *vertex_array = calloc((length(segments) * 2) + 1, sizeof(vertex));

    int index = 0;

    for (void *aux = getFirst(segments); aux; aux = getNext(segments, aux)) {
        vertex_array[index++] = *(((segment *)get(aux))->ini_point);
        vertex_array[index++] = *(((segment *)get(aux))->end_point);
    }

    qsort(vertex_array, length(segments) * 2, sizeofVtx, compare);

    /*      DEBUG       */
    puts("\n\n\n\n\n\n");
    FILE *teste = fopen("DEBUG.svg", "a+");
    fprintf(teste, "<svg>\n");
    printf("%ld\n\n", length(segments) * 2);
    for (index = 0; index < length(segments) * 2; index++) {
        printf("p:%d\tx:%lf\ty:%lf\ta:%lf\tt:%d\n", index, vertex_array[index].point[0], vertex_array[index].point[1], slope(meteor_impact->point, vertex_array[index].point), vertex_array[index].type);
        printf("\nsegment: ");
        double met[] = {72, 50};
        printf("IniQ = %d ", quadrant(met, point(ini_point(vertex_array[index].segment))));
        printf("EndQ = %d \n", quadrant(met, point(end_point(vertex_array[index].segment))));
        print_segment(vertex_array[index].segment);
        puts("\n\n");
        fprintf(teste, "<circle cx=\" %lf \"  cy=\" %lf \"  r=\" 2.000000 \"  stroke=\" green \" stroke-width=\" 1 \"  fill=\" orange \"  opacity=\" 0.5 \" />\n", vertex_array[index].point[0], vertex_array[index].point[1]);
        fprintf(teste, "	<text x= \"%lf\" y=\"%lf\" class=\"small\" font-size=\"5\" >%d</text>\n", vertex_array[index].point[0], vertex_array[index].point[1], index);
    }
    fprintf(teste, "</svg>");
    fclose(teste);
    puts("\n\n\n\n\n\n");

    return vertex_array;
}

int destroy_vertex_array(void *st_vertex_array) {
    vertex *vertex_array = st_vertex_array;
    int tam = sizeof(vertex_array) / sizeof(vertex);
    for (int i = 0; i < tam; i++) {
        if (vertex_array[tam].segment) {
            free(vertex_array[tam].segment);
            vertex_array[tam].segment = NULL;
        }
        free(&vertex_array[tam]);
    }
    free(vertex_array);
}

int segment_list_recursion(Celula current_node, Lista seg_list, void *meteoro) {
    if (right_son(current_node))
        segment_list_recursion(right_son(current_node), seg_list, meteoro);

    if (left_son(current_node))
        segment_list_recursion(left_son(current_node), seg_list, meteoro);

    if (get_visible(current_node)) {
        /*      INSERE O SEGMENTO HORIZONTAL SUPERIOR      */
        insert(seg_list, segment_factory(vertex_factory(rect_x(get_data(current_node)), rect_y(get_data(current_node)), "ORIG"), vertex_factory(rect_x(get_data(current_node)) + rect_w(get_data(current_node)), rect_y(get_data(current_node)), "ORIG"), meteoro));
        /*      INSERE O SEGMENTO VERTICAL ESQUERDO        */
        insert(seg_list, segment_factory(vertex_factory(rect_x(get_data(current_node)), rect_y(get_data(current_node)), "ORIG"), vertex_factory(rect_x(get_data(current_node)), rect_y(get_data(current_node)) + rect_h(get_data(current_node)), "ORIG"), meteoro));
        /*      INSERE O SEGMENTO VERTICAL DIREITO         */
        insert(seg_list, segment_factory(vertex_factory(rect_x(get_data(current_node)) + rect_w(get_data(current_node)), rect_y(get_data(current_node)), "ORIG"), vertex_factory(rect_x(get_data(current_node)) + rect_w(get_data(current_node)), rect_y(get_data(current_node)) + rect_h(get_data(current_node)), "ORIG"), meteoro));
        /*      INSERE O SEGMENTO HORIZONTAL INFERIOR      */
        insert(seg_list, segment_factory(vertex_factory(rect_x(get_data(current_node)), rect_y(get_data(current_node)) + rect_h(get_data(current_node)), "ORIG"), vertex_factory(rect_x(get_data(current_node)) + rect_w(get_data(current_node)), rect_y(get_data(current_node)) + rect_h(get_data(current_node)), "ORIG"), meteoro));
    }

    return 1;
}

int destroy_segment_list(Lista seg_list) {
    for (Celula aux = getFirst(seg_list); aux; aux = getNext(seg_list, aux)) {
        segment *seg_node = get(aux);
        free(seg_node->ini_point);
        free(seg_node->end_point);
    }
    freeList(seg_list, 1, free);
}