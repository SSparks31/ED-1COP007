#include "DataStructures/list.h"
#include "DataStructures/tree.h"
#include "GeometricForms/polygon.h"
#include "GeometricForms/segment.h"
#include "argvFunc.h"
#include "controller.h"
#include "geo.h"
#include "geometry.h"
#include "qry.h"
#include "svg.h"
#include "util.h"

int main(int argc, char **argv) {
    Controlador controller = controller_factory();
    Endereco path = paths_factory();
    Arvore circle_tree = tree_factory(kd, CIRCULO);
    Arvore rectangle_tree = tree_factory(kd, RETANGULO);

    argv_processor(argv,  path, controller);

    geo_processor(path, controller, rectangle_tree, circle_tree);

    FILE *file1 = fopen(get_output_svg_full_path(path), "w");
    svg_maker(file1, controller, circle_tree, rectangle_tree);
    fclose(file1);

    if (get_exist_input_qry(controller)) {
        qry_processor(NULL, path, controller, circle_tree, rectangle_tree);

        FILE *file2 = fopen(get_output_svg_qry_full_path(path), "w");
        svg_maker(file2, controller, circle_tree, rectangle_tree);
        fclose(file2);
    }


    destroy_tree(rectangle_tree, free_rect, 1);
    destroy_tree(circle_tree, placebo1, 1);
    destroy_paths(path);
    destroy_controller(controller);
    return 0;
}