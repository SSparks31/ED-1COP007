#include "geometry.h"

#include <stdio.h>

#include "DataStructures/list.h"
#include "DataStructures/tree.h"
#include "GeometricForms/circle.h"
#include "GeometricForms/polygon.h"
#include "GeometricForms/rectangle.h"
#include "GeometricForms/segment.h"
#include "argvFunc.h"
#include "controller.h"
#include "geo.h"
#include "meteor.h"
#include "qry.h"
#include "svg.h"
#include "util.h"


int inside_of(void* point, void* st_data, int visibility) {
    int verify = RET_ponto_interno(get_x_circ(point), get_y_circ(point), rect_x(st_data), rect_y(st_data), rect_w(st_data), rect_h(st_data));

    return verify && visibility;
}

int rectangle_contain(void* st_ret1, void* st_ret2, int visibility) {
    int verify = strcmp(get_id_rect(st_ret1), get_id_rect(st_ret2)) && RET_esta_contido(rect_x(st_ret1), rect_y(st_ret1), rect_w(st_ret1), rect_h(st_ret1), rect_x(st_ret2), rect_y(st_ret2), rect_w(st_ret2), rect_h(st_ret2));

    return verify && visibility;
}

double* straight_equation(double point_1[2], double point_2[2]) {
    double* output = calloc(4, sizeof(double));

    if (point_1[0] == point_2[0]) {
        output[0] = 1;
        output[1] = 0;
        output[2] = point_1[0];

    } else if (point_1[1] == point_2[1]) {
        output[0] = 0;
        output[1] = 1;
        output[2] = point_1[1];

    } else {
        double m = slope(point_1, point_2);
        double n = point_2[1] - (m * point_2[0]);

        output[0] = m;
        output[1] = -1;
        output[2] = -1 * n;
    }

    return output;
}

double slope(const double point_1[2], const double point_2[2]) {
    return (point_2[1] - point_1[1]) / (point_2[0] - point_1[0]);
}

double* intersec(Segmento __seg1, Segmento __seg2) {
    double determinant = ((point(end_point(__seg2))[0] - point(ini_point(__seg2))[0]) * (point(end_point(__seg1))[1] - point(ini_point(__seg1))[1]) - (point(end_point(__seg2))[1] - point(ini_point(__seg2))[1]) * (point(end_point(__seg1))[0] - point(ini_point(__seg1))[0]));

    if (determinant == 0) {
        return NULL;
    }

    double* output = calloc(3, sizeof(double));

    double s = ((point(end_point(__seg2))[0] - point(ini_point(__seg2))[0]) * (point(ini_point(__seg2))[1] - point(ini_point(__seg1))[1]) - (point(end_point(__seg2))[1] - point(ini_point(__seg2))[1]) * (point(ini_point(__seg2))[0] - point(ini_point(__seg1))[0]));

    s /= determinant;

    double t = ((point(end_point(__seg1))[0] - point(ini_point(__seg1))[0]) * (point(ini_point(__seg2))[1] - point(ini_point(__seg1))[1]) - (point(end_point(__seg1))[1] - point(ini_point(__seg1))[1]) * (point(ini_point(__seg2))[0] - point(ini_point(__seg1))[0]));

    t /= determinant;

    if (!(s >= 0 && s <= 1)) {
        free(output);
        return NULL;
    }

    if (!(t >= 0 && t <= 1)) {
        free(output);
        return NULL;
    }

    output[0] = point(ini_point(__seg1))[0] + (point(end_point(__seg1))[0] - point(ini_point(__seg1))[0]) * s;

    output[1] = point(ini_point(__seg1))[1] + (point(end_point(__seg1))[1] - point(ini_point(__seg1))[1]) * s;

    return output;
}

double* extend(double __equation[3], double x) {
    double* point = calloc(2, sizeof(double));
    if (__equation[0] != 0 && __equation[1] != 0) {
        point[0] = x;
        point[1] = ((x * __equation[0]) - __equation[2]) / (-1 * __equation[1]);
    } else if (__equation[0] != 0) {
        point[0] = x;
        point[1] = __equation[2] / __equation[1];
    } else if (__equation[1] != 0) {
        point[0] = __equation[2] / __equation[0];
        point[1] = x;
    }
    return point;
}

int quadrant(double* center, const double point[2]) {
    if ((point[0] > center[0]) && (point[1] <= center[1])) return 1;

    if ((point[0] <= center[0]) && (point[1] < center[1])) return 2;

    if ((point[0] < center[0]) && (point[1] >= center[1])) return 3;

    if ((point[0] >= center[0]) && (point[1] > center[1])) return 4;

    return 1;
}

int inside_of_polygon(Vertice __vtx, Poligono __plg, Meteoro __mtr) {
   
    Segmento meteor_plg_radius = segment_factory(vertex_factory(point(fall_point(__mtr))[0], point(fall_point(__mtr))[1], "MET"), vertex_factory(point(__vtx)[0], point(__vtx)[1], "POINT"), fall_point(__mtr));

    int cont = 0;

    for (int index = 0; index < n_segments(__plg); index++) {
        Segmento seg_aux = segment_index(__plg, index);

        double* intersec_aux = intersec(seg_aux, meteor_plg_radius);

        if (intersec_aux)
            cont++;

        free(intersec_aux);
    }

    destroy_segment(meteor_plg_radius);
    return cont;
}