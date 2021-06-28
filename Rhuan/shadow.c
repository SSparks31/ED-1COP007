#include "shadow.h"

#include "DataStructures/list.h"
#include "DataStructures/tree.h"
#include "GeometricForms/polygon.h"
#include "GeometricForms/segment.h"
#include "controller.h"
#include "geometry.h"
#include "util.h"

void shadows(void* __shadow_polygons, void* __seglist, void* __meteor, void* __controller) {
    int num = 1;
    double* Extend;
    for (void* aux = getFirst(__seglist); aux; aux = getNext(__seglist, aux)) {
        void* __vertex1 = vtxcpy(ini_point(get(aux)));

        void* __vertex2 = vtxcpy(end_point(get(aux)));

        double* __equation1 = straight_equation(point(ini_point(get(aux))), point(__meteor));

        double* __equation2 = straight_equation(point(end_point(get(aux))), point(__meteor));

        Extend = extend(__equation1, 9999999 * (point(ini_point(get(aux)))[0] < point(__meteor)[0] ? -1 : 1));
        void* __vertex3 = vertex_factory(Extend[0], Extend[1], "ARTIFICIAL");
        free(Extend);

        Extend = extend(__equation2, 9999999 * (point(end_point(get(aux)))[0] < point(__meteor)[0] ? -1 : 1));
        void* __vertex4 = vertex_factory(Extend[0], Extend[1], "ARTIFICIAL");
        free(Extend);

        //Segments
        void* __segment1 = segment_factory(vtxcpy(__vertex1), vtxcpy(__vertex2), __meteor);

        void* __segment2 = segment_factory(vtxcpy(__vertex1), vtxcpy(__vertex3), __meteor);

        void* __segment3 = segment_factory(vtxcpy(__vertex2), vtxcpy(__vertex4), __meteor);

        void* __segment4 = segment_factory(vtxcpy(__vertex3), vtxcpy(__vertex4), __meteor);

        free(__equation1);
        free(__equation2);
        free(__vertex1);
        free(__vertex2);
        free(__vertex3);
        free(__vertex4);

        void* polygon = polygon_factory(1);

        // FILE* f = fopen("poly.txt", "a+");

        // puts("\n\n\n\nPOLYGON");
        // fprintf(f, "<line x1=\"%lf\" x2=\"%lf\" y1=\"%lf\" y2=\"%lf\" stroke=\"purple\"   />\n", point(ini_point(__segment1))[0], point(end_point(__segment1))[0], point(ini_point(__segment1))[1], point(end_point(__segment1))[1]);

        // fprintf(f, "<line x1=\"%lf\" x2=\"%lf\" y1=\"%lf\" y2=\"%lf\" stroke=\"purple\"  />\n", point(ini_point(__segment2))[0], point(end_point(__segment2))[0], point(ini_point(__segment2))[1], point(end_point(__segment2))[1]);

        // fprintf(f, "<line x1=\"%lf\" x2=\"%lf\" y1=\"%lf\" y2=\"%lf\" stroke=\"purple\"  />\n", point(ini_point(__segment3))[0], point(end_point(__segment3))[0], point(ini_point(__segment3))[1], point(end_point(__segment3))[1]);

        // fprintf(f, "<line x1=\"%lf\" x2=\"%lf\" y1=\"%lf\" y2=\"%lf\" stroke=\"purple\"  />\n", point(ini_point(__segment4))[0], point(end_point(__segment4))[0], point(ini_point(__segment4))[1], point(end_point(__segment4))[1]);

        add_segment(polygon, __segment1);
        add_segment(polygon, __segment2);
        add_segment(polygon, __segment3);
        add_segment(polygon, __segment4);

        insert_tree(__shadow_polygons, polygon, compare_xy_polygon, set_kd_poly);
    }
}
