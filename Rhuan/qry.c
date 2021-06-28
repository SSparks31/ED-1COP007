#include "qry.h"

#include "DataStructures/list.h"
#include "DataStructures/tree.h"
#include "GeometricForms/circle.h"
#include "GeometricForms/polygon.h"
#include "GeometricForms/rectangle.h"
#include "GeometricForms/segment.h"
#include "argvFunc.h"
#include "controller.h"
#include "geo.h"
#include "geometry.h"
#include "meteor.h"
#include "shadow.h"
#include "svg.h"
#include "util.h"

typedef struct txt_report {
    char rectangle[50];

    char **circles;

    int n_circles;

} txt_report;

typedef struct txt {
    txt_report *report;

    int num;

} txt;

void LOG_make_sob(Lista list, FILE *dir, Endereco Paths);
int compare_report(const void *a, const void *b);

//FG
int qry_fg(FILE *consultas, void *Paths, Arvore __ct, Arvore __rt);
int qry_fg_compare_points(void *current_node, Lista point_list, double point_x, double point_y, double point_radius);
int qry_fg_bind_points_and_rectangles(Arvore __ct, Arvore __rt, txt *main_report, Lista point_list, double point_x, double point_y, double point_radius);
void *qry_fg_short_path_fg(void *current_node, void *data);
int qry_fg_txt_report(FILE *file, Arvore __rt);

//DPI
int divide_and_conquer(void *current_node, Arvore rectangle_tree, txt *main_report, void *point, int (*qry_remove_func)(void *point, void *st_data, int visibility));
int qry_dpi(FILE *consultas, void *Paths, Arvore rectangle_tree);

//DR
int qry_dr(FILE *consultas, Endereco Paths, Arvore rectangle_tree);

//IM
int qry_im(FILE *consultas, void *Paths, Controlador controller, Arvore __ct, Arvore __rt);

//nve
int qry_nve(FILE *consultas, void *Paths, Controlador controller, Arvore __ct, Arvore __rt);

//t30
int qry_t30(FILE *consultas, void *Paths, Controlador controller, Arvore __ct);

int qry_processor(Lista Stlist, void *Paths, Controlador controller, Arvore __ct, Arvore __rt) {
    FILE *consultas = fopen(get_input_qry_full_path(Paths), "r");

    FILE *txt_report = fopen(get_output_txt_qry_full_path(Paths), "a+");
    fprintf(txt_report, "Rhuan Ferrer da Silva\n\n");
    fclose(txt_report);

    if (!consultas) {
        debug_paths(Paths, "qryFunc.c : linha 68");
        return puts("QRY_con_reader: Erro ao abrir arquivo .qry") - ERROR;
    }

    char func[50] = {0};

    while (fscanf(consultas, "%s", func) != EOF) {
        if (!strcmp(func, "dpi")) {
            qry_dpi(consultas, Paths, __rt);
        }

        if (!strcmp(func, "dr")) {
            qry_dr(consultas, Paths, __rt);
        }

        if (!strcmp(func, "fg")) {
            qry_fg(consultas, Paths, __ct, __rt);
        }

        if (!strcmp(func, "im")) {
            qry_im(consultas, Paths, controller, __ct, __rt);
        }

        if (!strcmp(func, "nve")) {
            qry_nve(consultas, Paths, controller, __ct, __rt);
        }

        if (!strcmp(func, "t30")) {
            qry_t30(consultas, Paths, controller, __ct);
        }
    }

    fclose(consultas);
    return 1;
}

void t30_recursion(void *current_node, txt *main_report) {
    if (right_son(current_node))
        t30_recursion(right_son(current_node), main_report);

    if (left_son(current_node))
        t30_recursion(left_son(current_node), main_report);

    if (circ_radiation(get_data(current_node)) >= 1000) {
        main_report->num++;
        main_report->report = realloc(main_report->report, main_report->num * sizeof(txt_report));
        strcpy(main_report->report[main_report->num - 1].rectangle, get_id_rect(get_data(current_node)));
        kill(get_data(current_node));
    }
}

int qry_t30(FILE *consultas, void *Paths, Controlador controller, Arvore __ct) {
    txt *main_report = calloc(1, sizeof(txt));

    main_report->report = calloc(0, sizeof(txt_report));

    main_report->num = 0;

    t30_recursion(root(__ct), main_report);

    FILE *file = fopen(get_output_txt_qry_full_path(Paths), "a+");
    fprintf(file, "\\\\\\\\\\\\\\\\\\  T30  ///////// \n");

    qsort(main_report->report, main_report->num, sizeof(txt_report), compare_report);

    for (int i = 0; i < main_report->num; i++) {
        fprintf(file, "%s", main_report->report[i].rectangle);
        fprintf(file, "\n");
    }

    free(main_report->report);
    free(main_report);

    fprintf(file, "\n\n");
    fclose(file);
}

int compare_report(const void *a, const void *b) {
    const txt_report *A = a;
    const txt_report *B = b;
    return strcmp(A->rectangle, B->rectangle);
}

int compare_report_fg2(const void *a, const void *b) {
    const char *A = *(const char **)a;
    const char *B = *(const char **)b;
    return strcmp(A, B);
}

double nve_recursion(void *current_node, void *vtx_prov, double *rad, void *met_aux) {
    double off = 0;

    if (get_kd_poly(get_data(current_node))) {
        if (point(vtx_prov)[1] < get_y_rect_poly(get_data(current_node))) {
            if (left_son(current_node))
                off += nve_recursion(left_son(current_node), vtx_prov, rad, met_aux);
        } else {
            if (right_son(current_node))
                off += nve_recursion(right_son(current_node), vtx_prov, rad, met_aux);
            if (left_son(current_node))
                off += nve_recursion(left_son(current_node), vtx_prov, rad, met_aux);
        }
    } else {
        if (point(vtx_prov)[0] < get_x_rect_poly(get_data(current_node))) {
            if (left_son(current_node))
                off += nve_recursion(left_son(current_node), vtx_prov, rad, met_aux);
        } else {
            if (right_son(current_node))
                off += nve_recursion(right_son(current_node), vtx_prov, rad, met_aux);
            if (left_son(current_node))
                off += nve_recursion(left_son(current_node), vtx_prov, rad, met_aux);
        }
    }

    if (inside_of_polygon(vtx_prov, get_data(current_node), get(met_aux))) {
        *rad *= 0.8;
        off++;
    }

    return off;
}

int qry_nve(FILE *consultas, void *Paths, Controlador controller, Arvore __ct, Arvore __rt) {
    double px, py;

    fscanf(consultas, "%lf %lf", &px, &py);

    Vertice vtx_prov = vertex_factory(px, py, "PROVISORIO");

    double rad = 0, aux_rad;

    double t = 0;

    for (Celula meteor_aux = getFirst(get_meteor_impact(controller)); meteor_aux; meteor_aux = getNext(get_meteor_impact(controller), meteor_aux)) {
        aux_rad = meteor_radiation(get(meteor_aux));
        double cont = nve_recursion(root(shadow_polygons(get(meteor_aux))), vtx_prov, &aux_rad, meteor_aux);
        // for (int i = 0; i < cont; i++) {
        //     aux_rad *= 0.8;
        // }
        t += cont;
        rad += aux_rad;
    }
    free(vtx_prov);

    double *in = calloc(3, sizeof(double));
    in[0] = px;
    in[1] = py;
    in[2] = rad;
    insert(nve_points(controller), in);

    FILE *txt_report = fopen(get_output_txt_qry_full_path(Paths), "a+");
    fprintf(txt_report, "\\\\\\\\\\\\\\\\\\  NVE  ///////// \n");
    fprintf(txt_report, "%lf\n\n", rad);
    fclose(txt_report);
}

double im_search_shadow(void *current_node, void *vtx_prov, void *meteor, void *circ) {
    double off = 0;

    if (get_kd_poly(get_data(current_node))) {
        if (point(vtx_prov)[1] < get_y_rect_poly(get_data(current_node))) {
            if (left_son(current_node))
                off += im_search_shadow(left_son(current_node), vtx_prov, meteor, circ);
        } else {
            if (right_son(current_node))
                off += im_search_shadow(right_son(current_node), vtx_prov, meteor, circ);
            if (left_son(current_node))
                off += im_search_shadow(left_son(current_node), vtx_prov, meteor, circ);
        }
    } else {
        if (point(vtx_prov)[0] < get_x_rect_poly(get_data(current_node))) {
            if (left_son(current_node))
                off += im_search_shadow(left_son(current_node), vtx_prov, meteor, circ);
        } else {
            if (right_son(current_node))
                off += im_search_shadow(right_son(current_node), vtx_prov, meteor, circ);
            if (left_son(current_node))
                off += im_search_shadow(left_son(current_node), vtx_prov, meteor, circ);
        }
    }

    if (inside_of_polygon(vtx_prov, get_data(current_node), meteor))
        off++;

    return off;
}

void im_recursion(Noh current_node, Meteoro meteor, Controlador controller, txt *main_report) {
    if (!current_node) return;

    //Não consegui desbrir como otimizar esse aqui, caso tenha como
    if (right_son(current_node))
        im_recursion(right_son(current_node), meteor, controller, main_report);

    if (left_son(current_node))
        im_recursion(left_son(current_node), meteor, controller, main_report);

    if (alive(get_data(current_node))) {
        Vertice vtx_prov = vertex_factory(get_x_circ(get_data(current_node)), get_y_circ(get_data(current_node)), "PROVISORIO");

        double rad = meteor_radiation(meteor);

        int cont = im_search_shadow(root(shadow_polygons(meteor)), vtx_prov, meteor, get_data(current_node));
        for (int i = 0; i < cont; i++)
            rad *= 0.8;

        set_circ_radiation(get_data(current_node), rad);

        if (circ_radiation(get_data(current_node)) > 1000) {
            main_report->num++;
            main_report->report = realloc(main_report->report, main_report->num * sizeof(txt_report));

            if (circ_radiation(get_data(current_node)) >= 8000) {
                sprintf(main_report->report[main_report->num - 1].rectangle, "%s MORTO", get_id_circ(get_data(current_node)));
                kill(get_data(current_node));
            } else {
                sprintf(main_report->report[main_report->num - 1].rectangle, "%s MORTE IMINENTE", get_id_circ(get_data(current_node)));
            }
        }

        Meteoro meteor_aux = meteor_factory(circ_radiation(get_data(current_node)));
        set_circ_colors(get_data(current_node), color_by_rad(meteor_aux), color_by_rad(meteor_aux));
        destroy_meteor(meteor_aux);

        free(vtx_prov);
    }
}

int qry_im(FILE *consultas, void *Paths, Controlador __controller, Arvore __ct, Arvore __rt) {
    double __meteorP[2], __meteor_radiation;

    txt *main_report = calloc(1, sizeof(txt));
    main_report->report = calloc(0, sizeof(txt_report));
    main_report->num = 0;

    fscanf(consultas, "%lf %lf %lf", &__meteorP[0], &__meteorP[1], &__meteor_radiation);

    Meteoro meteor = meteor_factory(__meteor_radiation);

    set_fall_point(meteor, vertex_factory(__meteorP[0], __meteorP[1], "METEOR"));

    void *__seglist = createLista(1);

    segment_list_recursion(root(__rt), __seglist, fall_point(meteor));

    shadows(shadow_polygons(meteor), __seglist, fall_point(meteor), __controller);

    im_recursion(root(__ct), meteor, Paths, main_report);

    FILE *file = fopen(get_output_txt_qry_full_path(Paths), "a+");
    fprintf(file, "\\\\\\\\\\\\\\\\\\  IM  ///////// \n");

    qsort(main_report->report, main_report->num, sizeof(txt_report), compare_report);

    for (int i = 0; i < main_report->num; i++) {
        fprintf(file, "%s", main_report->report[i].rectangle);
        fprintf(file, "\n");
    }

    free(main_report->report);
    free(main_report);

    fprintf(file, "\n\n");
    fclose(file);

    destroy_segment_list(__seglist);

    insert(get_meteor_impact(__controller), meteor);
}

void dr_recursion(void *current_node, void *Rectangle, void *tree, txt *main_report) {
    if (get_kd_rect(get_data(current_node))) {
        if (rect_x(Rectangle) > rect_x(get_data(current_node))) {
            if (right_son(current_node)) {
                dr_recursion(right_son(current_node), Rectangle, tree, main_report);
            }
        } else {
            if (right_son(current_node)) {
                dr_recursion(right_son(current_node), Rectangle, tree, main_report);
            }
            if (left_son(current_node)) {
                dr_recursion(left_son(current_node), Rectangle, tree, main_report);
            }
        }
    } else {
        if (rect_y(Rectangle) > rect_y(get_data(current_node))) {
            if (right_son(current_node)) {
                dr_recursion(right_son(current_node), Rectangle, tree, main_report);
            }
        } else {
            if (right_son(current_node)) {
                dr_recursion(right_son(current_node), Rectangle, tree, main_report);
            }
            if (left_son(current_node)) {
                dr_recursion(left_son(current_node), Rectangle, tree, main_report);
            }
        }
    }

    if (compare_id_rect(get_data(current_node), Rectangle)) {
        if (rectangle_contain(Rectangle, get_data(current_node), get_visible(get_data(current_node)))) {
            main_report->num++;
            main_report->report = realloc(main_report->report, main_report->num * sizeof(txt_report));
            strcpy(main_report->report[main_report->num - 1].rectangle, get_id_rect(get_data(current_node)));
            remove_element_tree(tree, get_data(current_node), compare_id_rect, set_kd_rect, free_rect, 0);
        }
    } else {
        puts("1");
        puts(get_id_rect(get_data(current_node)));
        puts("2");
        puts(get_id_rect(Rectangle));
    }
}

int qry_dr(FILE *consultas, Endereco Paths, Arvore rectangle_tree) {
    char id[100];

    fscanf(consultas, "%s", id);

    void *search_rectangle = create_rect(id, NULL, NULL);
    void *dr_rectangle = get_data(search_tree(rectangle_tree, search_rectangle, compare_id_rect));

    txt *main_report = calloc(1, sizeof(txt));
    main_report->report = calloc(0, sizeof(txt_report));
    main_report->num = 0;

    dr_recursion(root(rectangle_tree), dr_rectangle, rectangle_tree, main_report);

    FILE *file = fopen(get_output_txt_qry_full_path(Paths), "a+");
    fprintf(file, "\\\\\\\\\\\\\\\\\\  DR  ///////// \n");

    qsort(main_report->report, main_report->num, sizeof(txt_report), compare_report);

    for (int i = 0; i < main_report->num; i++) {
        fprintf(file, "%s", main_report->report[i].rectangle);
        fprintf(file, "\n");
    }

    fprintf(file, "\n\n");
    fclose(file);

    free(main_report->report);
    free(main_report);

    free_rect(search_rectangle);
    free(search_rectangle);
}

int qry_fg(FILE *consultas, void *Paths, Arvore __ct, Arvore __rt) {
    if (!consultas || !Paths || !__ct || !__rt) {
        puts("qry_fg: Parametro vazio");
        return -1;
    }

    double point[3];

    fscanf(consultas, "%lf %lf %lf", &point[0], &point[1], &point[2]);

    Lista point_list = createLista(0);

    txt *main_report = calloc(1, sizeof(txt));

    main_report->report = calloc(0, sizeof(txt_report));

    main_report->num = 0;

    FILE *file = fopen(get_output_txt_qry_full_path(Paths), "a+");

    fprintf(file, "\\\\\\\\\\\\\\\\\\  FG  ///////// \n");

    // qry_fg_file(file, __rt);
    // qry_fg_txt_report_recursion(file, root(__rt), main_report);

    qry_fg_compare_points(root(__ct), point_list, point[0], point[1], point[2]);

    qry_fg_bind_points_and_rectangles(__ct, __rt, main_report, point_list, point[0], point[1], point[2]);

    qsort(main_report->report, main_report->num, sizeof(txt_report), compare_report);

    for (int i = 0; i < main_report->num; i++)
        if (main_report->report[i].n_circles)
            qsort((char *)main_report->report[i].circles, main_report->report[i].n_circles, sizeof(main_report->report[i].circles), compare_report_fg2);

    for (int i = 0; i < main_report->num; i++) {
        if (main_report->report[i].n_circles) {
            fprintf(file, "%s  ", main_report->report[i].rectangle);
            for (int j = 0; j < main_report->report[i].n_circles; j++) {
                fprintf(file, " %s%s ", main_report->report[i].circles[j], j < main_report->report[i].n_circles - 1 ? ", " : ".");
                free(main_report->report[i].circles[j]);
            }
            fprintf(file, "\n");
        }
        free(main_report->report[i].circles);
    }

    free(main_report->report);
    free(main_report);

    fprintf(file, "\n\n");
    fclose(file);

    freeList(point_list, 0, free);
    return 1;
}

void *qry_fg_short_path_fg(void *current_node, void *data) {
    void *aux1 = NULL, *aux2 = NULL;

    double dist_atual = 9999, dist_direita = 99999, dist_esquerda = 99999;

    if (get_visible(current_node))
        dist_atual = distancia(get_center_x(get_data(current_node)), get_center_y(get_data(current_node)), get_x_circ(data), get_y_circ(data));

    if (right_son(current_node)) {
        aux1 = qry_fg_short_path_fg(right_son(current_node), data);
        if (aux1)
            dist_direita = distancia(get_center_x(get_data(aux1)), get_center_y(get_data(aux1)), get_x_circ(data), get_y_circ(data));
    }

    if (left_son(current_node)) {
        aux2 = qry_fg_short_path_fg(left_son(current_node), data);
        if (aux2)
            dist_esquerda = distancia(get_center_x(get_data(aux2)), get_center_y(get_data(aux2)), get_x_circ(data), get_y_circ(data));
    }

    if (dist_atual <= dist_esquerda && dist_atual <= dist_direita)
        return get_visible(current_node) ? current_node : NULL;
    if (dist_esquerda <= dist_atual && dist_esquerda <= dist_direita)
        return get_visible(aux2) ? aux2 : NULL;
    if (dist_direita <= dist_atual && dist_direita <= dist_esquerda)
        return get_visible(aux1) ? aux1 : NULL;
}

int qry_fg_bind_points_and_rectangles(Arvore circle_tree, Arvore rectangle_tree, txt *main_report, Lista point_list, double point_x, double point_y, double point_radius) {
    Celula list_node = getFirst(point_list);

    while (list_node) {
        void *aux;

        aux = get_data(qry_fg_short_path_fg(root(rectangle_tree), get(list_node)));

        if (!aux || !alive(get(list_node)))
            return 1;



        set_rectangle_near(get(list_node), aux);
        insert_data_sheltered_in(aux, get(list_node));

        int i;
        for (i = 0; i < main_report->num; i++) {
            if (!strcmp(main_report->report[i].rectangle, get_id_rect(aux)))
                break;
        }

        if (i == main_report->num) {
            main_report->num++;
            main_report->report = realloc(main_report->report, main_report->num * sizeof(txt_report));
            strcpy(main_report->report[i].rectangle, get_id_rect(aux));
            main_report->report[i].n_circles = 0;
        }

        if (!main_report->report[i].n_circles)
            main_report->report[i].circles = calloc(1, sizeof(char *));
        else
            main_report->report[i].circles = realloc(main_report->report[i].circles, (main_report->report[i].n_circles + 1) * sizeof(char *));

        main_report->report[i].circles[main_report->report[i].n_circles] = calloc(50, 1);
        strcpy(main_report->report[i].circles[main_report->report[i].n_circles], get_id_circ(get(list_node)));

        main_report->report[i].n_circles++;

        list_node = getNext(point_list, list_node);
    }

    return 1;
}

int qry_fg_compare_points(void *current_node, Lista point_list, double point_x, double point_y, double point_radius) {
    if (right_son(current_node))
        qry_fg_compare_points(right_son(current_node), point_list, point_x, point_y, point_radius);

    if (left_son(current_node))
        qry_fg_compare_points(left_son(current_node), point_list, point_x, point_y, point_radius);

    if (distancia(get_x_circ(get_data(current_node)), get_y_circ(get_data(current_node)), point_x, point_y) <= point_radius) {
        insert(point_list, get_data(current_node));
    }

    return 1;
}

int divide_and_conquer(void *current_node, Arvore rectangle_tree, txt *main_report, void *point, int (*qry_remove_func)(void *point, void *st_data, int visibility)) {
    if (right_son(current_node))
        divide_and_conquer(right_son(current_node), rectangle_tree, main_report, point, qry_remove_func);

    if (left_son(current_node))
        divide_and_conquer(left_son(current_node), rectangle_tree, main_report, point, qry_remove_func);

    if (qry_remove_func(point, get_data(current_node), get_visible(current_node))) {
        main_report->num++;
        main_report->report = realloc(main_report->report, main_report->num * sizeof(txt_report));
        strcpy(main_report->report[main_report->num - 1].rectangle, get_id_rect(get_data(current_node)));
        remove_element_tree(rectangle_tree, get_data(current_node), compare_xy_rect, set_kd_rect, free_rect, 0);
    }
}

void dpi_recursion(void *current_node, Arvore rectangle_tree, txt *main_report, void *Point) {
    if (get_kd_poly(get_data(current_node))) {
        if (get_x_circ(Point) < rect_x(get_data(current_node))) {
            if (left_son(current_node))
                dpi_recursion(left_son(current_node), rectangle_tree, main_report, Point);
        } else {
            if (right_son(current_node))
                dpi_recursion(right_son(current_node), rectangle_tree, main_report, Point);

            if (left_son(current_node))
                dpi_recursion(left_son(current_node), rectangle_tree, main_report, Point);
        }
    } else {
        if (get_y_circ(Point) < rect_y(get_data(current_node))) {
            if (left_son(current_node))
                dpi_recursion(left_son(current_node), rectangle_tree, main_report, Point);

        } else {
            if (right_son(current_node))
                dpi_recursion(right_son(current_node), rectangle_tree, main_report, Point);

            if (left_son(current_node))
                dpi_recursion(left_son(current_node), rectangle_tree, main_report, Point);
        }
    }

    if (inside_of(Point, get_data(current_node), get_visible(current_node))) {
        main_report->num++;
        main_report->report = realloc(main_report->report, main_report->num * sizeof(txt_report));
        strcpy(main_report->report[main_report->num - 1].rectangle, get_id_rect(get_data(current_node)));
        remove_element_tree(rectangle_tree, get_data(current_node), compare_xy_rect, set_kd_rect, free_rect, 0);
    }
}

int qry_dpi(FILE *consultas, void *Paths, Arvore rectangle_tree) {
    double p_x, p_y;
    fscanf(consultas, "%lf %lf", &p_x, &p_y);

    void *dpi_circle = create_circle(NULL, p_x, p_y, 0, NULL);

    txt *main_report = calloc(1, sizeof(txt));

    main_report->report = calloc(0, sizeof(txt_report));

    main_report->num = 0;

    dpi_recursion(root(rectangle_tree), rectangle_tree, main_report, dpi_circle);

    FILE *file = fopen(get_output_txt_qry_full_path(Paths), "a+");
    fprintf(file, "\\\\\\\\\\\\\\\\\\  DPI  ///////// \n");

    qsort(main_report->report, main_report->num, sizeof(txt_report), compare_report);

    for (int i = 0; i < main_report->num; i++) {
        fprintf(file, "%s", main_report->report[i].rectangle);
        fprintf(file, "\n");
    }

    free(main_report->report);
    free(main_report);

    fprintf(file, "\n\n");
    fclose(file);

    free(dpi_circle);
}