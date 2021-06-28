#include "argvFunc.h"
#include "controller.h"
#include "geo.h"
#include "DataStructures/list.h"
#include "qry.h"
#include "svg.h"
#include "DataStructures/tree.h"
#include "util.h"

#include "GeometricForms/circle.h"
#include "GeometricForms/rectangle.h"
typedef struct Paths {
  
    String inputs_dir_path;

    String input_geo_file_name;

    String outputs_dir_path;

    String input_qry_file_name;

    String input_geo_full_path;

    String input_qry_full_path;

    String output_svg_qry_full_path;

    String output_txt_qry_full_path;

    String output_svg_full_path;

} Paths;

int set_output_svg_full_path(Endereco Path) {
    Paths *paths_object = Path;

    String aux_1_0 = separaArq(paths_object->input_geo_file_name);
    String aux_2_0 = MY_strtok(aux_1_0, '.');

    paths_object->output_svg_full_path = calloc(strlen(paths_object->outputs_dir_path) + strlen(aux_2_0) + 6, sizeof(char));

    sprintf(paths_object->output_svg_full_path, "%s%s.svg", paths_object->outputs_dir_path, aux_2_0);

    free(aux_1_0);
    free(aux_2_0);

    SUCCESS;
}

String get_output_svg_full_path(Endereco Path) {
    Paths *paths_object = Path;

    return paths_object && paths_object->output_svg_full_path ? paths_object->output_svg_full_path : print_and_return_null("get_output_svg_full_path: Parametro vazio") - ERROR;
}

int set_output_svg_qry_full_path(Endereco Path) {
    Paths *paths_object = Path;

    String aux_1_0 = separaArq(paths_object->input_geo_file_name), aux_1_1 = separaArq(paths_object->input_qry_file_name);
    String aux_2_0 = MY_strtok(aux_1_0, '.'), aux_2_1 = MY_strtok(aux_1_1, '.');

    paths_object->output_svg_qry_full_path = calloc(strlen(paths_object->outputs_dir_path) + strlen(aux_2_0) + strlen(aux_2_1) + 6, sizeof(char));

    sprintf(paths_object->output_svg_qry_full_path, "%s%s-%s.svg", paths_object->outputs_dir_path, aux_2_0, aux_2_1);

    free(aux_1_0);
    free(aux_1_1);
    free(aux_2_0);
    free(aux_2_1);

    SUCCESS;
}

String get_output_svg_qry_full_path(Endereco Path) {
    Paths *paths_object = Path;

    return paths_object && paths_object->output_svg_qry_full_path ? paths_object->output_svg_qry_full_path : print_and_return_null("get_output_svg_qry_full_path: Parametro vazio") - ERROR;
}

int set_output_txt_qry_full_path(Endereco Path) {
    Paths *paths_object = Path;

    String aux_1_0 = separaArq(paths_object->input_geo_file_name), aux_1_1 = separaArq(paths_object->input_qry_file_name);
    String aux_2_0 = MY_strtok(aux_1_0, '.'), aux_2_1 = MY_strtok(aux_1_1, '.');

    paths_object->output_txt_qry_full_path = calloc(strlen(paths_object->outputs_dir_path) + strlen(aux_2_0) + strlen(aux_2_1) + 6, sizeof(char));

    sprintf(paths_object->output_txt_qry_full_path, "%s%s-%s.txt", paths_object->outputs_dir_path, aux_2_0, aux_2_1);

    free(aux_1_0);
    free(aux_1_1);
    free(aux_2_0);
    free(aux_2_1);

    SUCCESS;
}

String get_output_txt_qry_full_path(Endereco Path) {
    Paths *paths_object = Path;

    return paths_object && paths_object->output_txt_qry_full_path ? paths_object->output_txt_qry_full_path : print_and_return_null("get_output_svg_qry_full_path: Parametro vazio") - ERROR;
}

int debug_paths(Endereco Path, String message) {
    Paths *paths_object = Path;
    char *debug_aux;
    if (!Path) return puts("debug_paths:\t\tParametro vazio");

    printf("\n\n\t\t\t\t====== %s ======\n\n", message);
    printf("Endereco de Path:\t\t%p\n", paths_object);
    printf("inputs_dir_path:\t\t%s\n", paths_object->inputs_dir_path);
    printf("input_geo_full_path:\t\t%s\n", paths_object->input_geo_full_path);
    printf("input_qry_full_path:\t\t%s\n", paths_object->input_qry_full_path);
    debug_aux = separaArq(paths_object->input_geo_file_name);
    printf("input_geo_file_name:\t\t%s\n", debug_aux);
    free(debug_aux);
    debug_aux = separaArq(paths_object->input_qry_file_name);
    printf("input_qry_file_name:\t\t%s\n", debug_aux);
    free(debug_aux);
    printf("outputs_dir_path:\t\t%s\n", paths_object->outputs_dir_path);
    printf("output_svg_full_path:\t\t%s\n", paths_object->output_svg_full_path);
    printf("output_svg_qry_full_path:\t%s\n", paths_object->output_svg_qry_full_path);
    printf("output_svg_txt_full_path:\t%s\n\n", paths_object->output_txt_qry_full_path);

    SUCCESS;
}

int this_is_a_function(String string) {
    return (!strcmp(string, "-e") || !strcmp(string, "-f") || !strcmp(string, "-o") || !strcmp(string, "-q") || !strcmp(string, "-ib") || !strcmp(string, "-cb") || !strcmp(string, "-fb"));
}

int destroy_paths(Endereco Path) {
    Paths *paths_object = Path;

    if (!Path) return puts("free_memory_of_Path:\tParametro vazio") - ERROR;

    free(paths_object->output_svg_qry_full_path);
    free(paths_object->output_txt_qry_full_path);
    free(paths_object->output_svg_full_path);
    free(paths_object->input_geo_full_path);
    free(paths_object->input_qry_full_path);
    free(paths_object->input_qry_file_name);
    free(paths_object->input_geo_file_name);
    free(paths_object->outputs_dir_path);
    free(paths_object->inputs_dir_path);
    free(paths_object);

    SUCCESS;
}

String get_inputs_dir_path(Endereco paths) {
    Paths *str = paths;

    return str ? str->inputs_dir_path : print_and_return_null("get_inputs_dir_path: Parametro vazio");
}

String get_input_geo_file_name(Endereco paths) {
    Paths *str = paths;

    return str ? str->input_geo_file_name : print_and_return_null("get_input_geo_file_name: Parametro vazio");
}

String get_outputs_dir_path(Endereco paths) {
    Paths *str = paths;

    return str ? str->outputs_dir_path : print_and_return_null("get_outputs_dir_path: Parametro vazio");
}

String get_input_qry_file_name(Endereco paths) {
    Paths *str = paths;

    return str ? str->input_qry_file_name : NULL;
}

String get_input_geo_full_path(Endereco paths) {
    Paths *paths_object = paths;

    return paths_object ? paths_object->input_geo_full_path : print_and_return_null("get_input_qry_full_path: Parametro vazio");
}

String get_input_qry_full_path(Endereco paths) {
    Paths *paths_object = paths;

    return paths_object ? paths_object->input_qry_full_path : print_and_return_null("get_input_qry_full_path: Parametro vazio");
}

int set_input_qry_full_path(Paths *paths_object, Controlador Contr) {
    if (paths_object->inputs_dir_path && get_exist_input_qry(Contr)) {
        paths_object->input_qry_full_path = calloc(strlen(paths_object->input_qry_file_name) + strlen(paths_object->inputs_dir_path) + 1, sizeof(char));

        sprintf(paths_object->input_qry_full_path, "%s%s", paths_object->inputs_dir_path, paths_object->input_qry_file_name);

    } else if (get_exist_input_qry(Contr)) {
        paths_object->input_qry_full_path = calloc(strlen(paths_object->input_qry_file_name) + 3, sizeof(char));

        sprintf(paths_object->input_qry_full_path, "./%s", paths_object->input_qry_file_name);
    }
}

int set_input_geo_full_path(Paths *paths_object) {
    if (paths_object->inputs_dir_path) {
        paths_object->input_geo_full_path = calloc(strlen(paths_object->input_geo_file_name) + strlen(paths_object->inputs_dir_path) + 1, sizeof(char));

        sprintf(paths_object->input_geo_full_path, "%s%s", paths_object->inputs_dir_path, paths_object->input_geo_file_name);

    } else {
        paths_object->input_geo_full_path = calloc(strlen(paths_object->input_geo_file_name) + 3, sizeof(char));

        sprintf(paths_object->input_qry_full_path, "./%s", paths_object->input_geo_file_name);
    }
}

int terminal_function_e(String *ARGV, int index, Endereco paths) {
    Paths *paths_object = paths;

    if (!ARGV || !paths)
        return puts("terminal_function_e: Parametros invalidos") - ERROR;

    if (this_is_a_function(ARGV[index + 1]))
        return puts("terminal_function_e: Parametros invalidos no terminal") - ERROR;

    paths_object->inputs_dir_path = calloc(2 + strlen(ARGV[index + 1]), sizeof(char));

    sprintf(paths_object->inputs_dir_path, "%s/", ARGV[index + 1]);

    SUCCESS;
}

int terminal_function_f(String *ARGV, int index, Endereco paths) {
    Paths *paths_object = paths;

    if (!ARGV || !paths)
        return puts("terminal_function_f: Parametros invalidos") - ERROR;

    if (this_is_a_function(ARGV[index + 1]))
        return puts("terminal_function_f: Parametros invalidos no terminal") - ERROR;

    paths_object->input_geo_file_name = calloc(1 + strlen(ARGV[index + 1]), sizeof(char));

    sprintf(paths_object->input_geo_file_name, "%s", ARGV[index + 1]);

    SUCCESS;
}

int terminal_function_o(String *ARGV, int index, Endereco paths) {
    Paths *paths_object = paths;

    if (!ARGV || !paths)
        return puts("terminal_function_o: Parametros invalidos") - ERROR;

    if (this_is_a_function(ARGV[index + 1]))
        return puts("terminal_function_o: Parametros invalidos no terminal") - ERROR;

    paths_object->outputs_dir_path = calloc(2 + strlen(ARGV[index + 1]), sizeof(char));

    sprintf(paths_object->outputs_dir_path, "%s/", ARGV[index + 1]);

    SUCCESS;
}

int terminal_function_q(String *ARGV, int index, Endereco Path) {
    Paths *paths_object = Path;

    if (!ARGV || !Path) return puts("terminal_function_q: Parametros invalidos") - ERROR;

    if (this_is_a_function(ARGV[index + 1])) return puts("terminal_function_q: Parametros invalidos no terminal") - ERROR;

    paths_object->input_qry_file_name = calloc(1 + strlen(ARGV[index + 1]), sizeof(char));

    sprintf(paths_object->input_qry_file_name, "%s", ARGV[index + 1]);

    SUCCESS;
}

int argv_processor(String *ARGV, Endereco paths, Controlador Contr) {
    Paths *paths_object = paths;
    int cont = -1;

    if (!ARGV || !paths_object || !Contr)
        return puts("argv_controller:\tErro na passagem de argumentos") - ERROR;

    while (ARGV[++cont]) {
        if (!strcmp(ARGV[cont], "-e"))
            if (!terminal_function_e(ARGV, cont, paths_object))
                return puts("argv_controller:\tErro em funcao interna (-e)") - ERROR;

        if (!strcmp(ARGV[cont], "-f"))
            if (!terminal_function_f(ARGV, cont, paths_object))
                return puts("argv_controller:\tErro em funcao interna (-f)") - ERROR;

        if (!strcmp(ARGV[cont], "-o"))
            if (!terminal_function_o(ARGV, cont, paths_object))
                return puts("argv_controller:\tErro em funcao interna (-o)") - ERROR;

        if (!strcmp(ARGV[cont], "-q")) {
            if (!terminal_function_q(ARGV, cont, paths_object))
                return puts("argv_controller:\tErro em funcao interna (-q)") - ERROR;
            set_exist_input_qry(Contr, 1);
        }
    }

    if (!get_input_geo_file_name(paths_object) || !get_outputs_dir_path(paths_object)) {
        printf("get_input_geo_file_name:\t%p\n", get_input_geo_file_name(paths_object));
        printf("get_outputs_dir_path:\t%p\n", get_outputs_dir_path(paths_object));
        return puts("argv_controller:\tValores obrigatorios não inseridos") - ERROR;
    }

    set_input_qry_full_path(paths_object, Contr);

    set_input_geo_full_path(paths_object);

    set_output_svg_full_path(paths_object);

    if (get_exist_input_qry(Contr)) {
        set_output_svg_qry_full_path(paths_object);
        set_output_txt_qry_full_path(paths_object);
    }

    SUCCESS;
}

Endereco paths_factory() {
    Paths *paths_object = calloc(1, sizeof(Paths));

    if (!paths_object) return print_and_return_null("createPaths: Erro de alocacao");

    paths_object->input_qry_file_name = NULL;
    paths_object->input_geo_file_name = NULL;
    paths_object->outputs_dir_path = NULL;
    paths_object->inputs_dir_path = NULL;
    paths_object->input_geo_full_path = NULL;
    paths_object->input_qry_full_path = NULL;

    return paths_object;
}
