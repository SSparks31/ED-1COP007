#include "svg.h"

#include "DataStructures/list.h"
#include "DataStructures/tree.h"
#include "GeometricForms/circle.h"
#include "GeometricForms/rectangle.h"
#include "argvFunc.h"
#include "controller.h"
#include "geo.h"
#include "meteor.h"
#include "qry.h"
#include "util.h"

int print_circle_in_svg(FILE* __file, double opacity, Circulo st_circle);

int RET_sobreposto(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) {
    int verify = 0;
    if ((x1 >= x2 && x1 <= x2 + w2) || (x2 >= x1 && x2 <= x1 + w1))
        verify++;
    if ((y1 >= y2 && y1 <= y2 + h2) || (y2 >= y1 && y2 <= y1 + h1))
        verify++;
    return (verify == 2);
}

int RET_ponto_interno(double px, double py, double x, double y, double l, double w) {
    return ((px >= x && px <= x + l) && (py >= y && py <= y + w));
}

int RET_esta_contido(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) {
    return ((x2 >= x1 && x2 <= x1 + w1) && (x2 + w2 >= x1 && x2 + w2 <= x1 + w1) && (y2 >= y1 && y2 <= y1 + h1) && (y2 + h2 >= y1 && y2 + h2 <= y1 + h1));
}

void print_text_svg(FILE* __file, int size, char* color, char* text, double x, double y) {
    fprintf(__file, "\t<text x= \"%lf\" y=\"%lf\" class=\"small\" font-size=\"%d\" fill=\"%s\" stroke=\"%s\"  >%s</text>\n", x, y, size, color, color, text);
}

void print_colors_svg(FILE* __file, char* fill_color, char* stroke_color) {
    fprintf(__file, " stroke=\"%s\" stroke-width=\" 1 \" ", stroke_color);
    fprintf(__file, " fill=\"%s\" ", fill_color);
}

int svg_maker(FILE* full_path, Controlador controller, Arvore __ct, Arvore __rt) {
    if (!full_path) return puts("svg_maker: Parametro vazio") - ERROR;

    double objects_opacity[] = {1, 0.5};

    fprintf(full_path, "<!-- RHuan Ferrer da Silva -->\n\n<svg  xmlns=\"http://www.w3.org/2000/svg\"  xmlns:xlink=\"http://www.w3.org/1999/xlink\"> \n\n");

    int cont = -1;

    if (length(get_meteor_impact(controller))) {
        for (Celula aux = getFirst(get_meteor_impact(controller)); aux; aux = getNext(get_meteor_impact(controller), aux)) {
            char colors[2][50] = {"silver", "silver"};
            Circulo meteoro = create_circle("M", point(fall_point(get(aux)))[0], point(fall_point(get(aux)))[1], meteor_radiation(get(aux)) / 5, colors);
            print_circle_in_svg(full_path, 0.2, meteoro);
            free(meteoro);
        }
    }

    print_rectangle_tree_svg(full_path, objects_opacity[data_type(__rt)], __rt);
    print_circle_tree_svg(full_path, objects_opacity[data_type(__ct)], __ct);

    char txt[100];
    if (length(nve_points(controller))) {
        Meteoro meteor_aux;
        for (void* aux = getFirst(nve_points(controller)); aux; aux = getNext(nve_points(controller), aux)) {
            meteor_aux = meteor_factory(((double*)get(aux))[2]);

            fprintf(full_path, "<rect x=\"%lf\" y=\"%lf\" rx=\"2\" ry=\"2\" width=\"10\" height=\"10\" fill=\"%s\" />\n", ((double*)get(aux))[0], ((double*)get(aux))[1], color_by_rad(meteor_aux));
            char txt[9999];
            sprintf(txt, "%lf", ((double*)get(aux))[2]);
            print_text_svg(full_path, 2, txt, "white", ((double*)get(aux))[0] + 1, ((double*)get(aux))[1] + 5);

            destroy_meteor(meteor_aux);
        }
    }
    
    fprintf(full_path, "\n</svg>\n");

    return 1;
}

void print_circle_center_svg(FILE* __file, void* circle) {
    fprintf(__file, " cx=\"%lf\" ", get_x_circ(circle));
    fprintf(__file, " cy=\"%lf\" ", get_y_circ(circle));
}

void print_circle_radius_svg(FILE* __file, void* circle) {
    fprintf(__file, " r=\" %lf \" ", get_radius(circle));
}

void print_opacity_svg(FILE* __file, double opacity) {
    fprintf(__file, " opacity=\"%lf\" ", opacity);
}

char* print_path_svg(FILE* __file, double __ini_x, double __ini_y, double __end_x, double __end_y, char* __id) {
    char* id = calloc(strlen(__id) + 7, sizeof(char));

    sprintf(id, "path_%s", __id);
    fprintf(__file, "\n<path");
    fprintf(__file, " stroke-dasharray=\"1.2\" stroke-dashoffset=\"2\" ");
    print_colors_svg(__file, "none", "red");
    fprintf(__file, " d=\"M%lf,%lf  %lf,%lf z\" ", __ini_x, __ini_y, __end_x, __end_y);
    fprintf(__file, " id=\"%s\" />", id);

    return id;
}

int print_circle_in_svg(FILE* __file, double opacity, Circulo st_circle) {
    char* __path_id = NULL;

    if (get_rectagle_near(st_circle))
        __path_id = print_path_svg(__file, get_original_x_circ(st_circle), get_original_y_circ(st_circle), get_center_x(get_rectagle_near(st_circle)), get_center_y(get_rectagle_near(st_circle)), get_id_circ((st_circle)));

    fprintf(__file, " \n<circle ");

    print_circle_radius_svg(__file, st_circle);

    print_colors_svg(__file, get_circle_fill_color(st_circle), get_circle_stroke_color(st_circle));

    print_opacity_svg(__file, 0.5);

    if (!get_rectagle_near(st_circle))
        print_circle_center_svg(__file, st_circle);
    else {
        fprintf(__file, " cx=\"\" cy=\"\" >\n");
        fprintf(__file, "\t<animateMotion dur=\"6s\" repeatCount=\"indefinite\">\n");
        fprintf(__file, "\t\t<mpath xlink:href=\"#%s\"/>\n", __path_id);
        fprintf(__file, "\t</animateMotion>");
        fprintf(__file, "\n</circle>\n<circle cx=\"%lf\" cy=\"%lf\" r=\" %lf \"  stroke=\" #494444 \" opacity=\"0.5\" stroke-width=\" 1 \" fill=\" grey \" ", get_original_x_circ(st_circle), get_original_y_circ(st_circle), get_radius(st_circle));
    }

    fprintf(__file, "  ></circle>\n\n");

    if (!alive(st_circle)){
        fprintf(__file, "<line x1=\"%lf\" x2=\"%lf\" y1=\"%lf\" y2=\"%lf\" stroke=\"white\"/>\n", get_x_circ(st_circle) - get_radius(st_circle), get_x_circ(st_circle) + get_radius(st_circle), get_y_circ(st_circle), get_y_circ(st_circle));

        fprintf(__file, "<line x1=\"%lf\" x2=\"%lf\" y1=\"%lf\" y2=\"%lf\" stroke=\"white\"/>\n", get_x_circ(st_circle), get_x_circ(st_circle), get_y_circ(st_circle) - get_radius(st_circle), get_y_circ(st_circle) + get_radius(st_circle));
    }

    if (__path_id)
        free(__path_id);
    return 1;
}

void print_rect_coordinates_svg(FILE* __file, void* rectangle) {
    fprintf(__file, " x=\"%lf\" ", rect_x(rectangle));
    fprintf(__file, " y=\"%lf\" ", rect_y(rectangle));
    fprintf(__file, " width=\"%lf\" ", rect_w(rectangle));
    fprintf(__file, " height=\"%lf\" ", rect_h(rectangle));
}

int print_rectangle_in_svg(FILE* __file, double opacity, Circulo st_rectangle) {
    fprintf(__file, "\n<rect ");
    print_rect_coordinates_svg(__file, st_rectangle);
    print_colors_svg(__file, get_rect_fill_color(st_rectangle), get_rect_stroke_color(st_rectangle));
    print_opacity_svg(__file, 0.5);
    fprintf(__file, "/>\n");
    print_text_svg(__file, 5, "black", get_id_rect(st_rectangle), rect_x(st_rectangle) + 1, rect_y(st_rectangle) + 5);

    if (get_rect_number_sheltered(st_rectangle) > 0) {
        String aux = (String)malloc(sizeof(int) + 1);
        sprintf(aux, "%d", get_rect_number_sheltered(st_rectangle));
        print_text_svg(__file, 5, "black", aux, rect_x(st_rectangle) + 1, rect_y(st_rectangle) + 10);
        free(aux);
    }

    return 1;
}

int print_circle_tree_svg_recursion(FILE* full_path, double objects_opacity, void* node) {
    if (right_son(node)) print_circle_tree_svg_recursion(full_path, objects_opacity, right_son(node));

    if (left_son(node)) print_circle_tree_svg_recursion(full_path, objects_opacity, left_son(node));

    print_circle_in_svg(full_path, objects_opacity, get_data(node));
}

int print_circle_tree_svg(FILE* full_path, double objects_opacity, void* __tree) {
    if (!__tree || !root(__tree)) return ERROR;

    print_circle_tree_svg_recursion(full_path, objects_opacity, root(__tree));
    fprintf(full_path, "\n");

    return 1;
}

int print_rectangle_tree_svg_recursion(FILE* full_path, double objects_opacity, void* node) {
    if (right_son(node)) print_rectangle_tree_svg_recursion(full_path, objects_opacity, right_son(node));

    if (left_son(node)) print_rectangle_tree_svg_recursion(full_path, objects_opacity, left_son(node));

    if (get_visible(node))
        print_rectangle_in_svg(full_path, objects_opacity, get_data(node));
}

int print_rectangle_tree_svg(FILE* full_path, double objects_opacity, void* __tree) {
    if (!__tree || !root(__tree)) return ERROR;

    print_rectangle_tree_svg_recursion(full_path, objects_opacity, root(__tree));
    fprintf(full_path, "\n");

    return 1;
}
