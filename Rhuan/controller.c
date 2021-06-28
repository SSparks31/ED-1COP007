#include "controller.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DataStructures/list.h"
#include "DataStructures/tree.h"
#include "GeometricForms/circle.h"
#include "GeometricForms/rectangle.h"
#include "argvFunc.h"
#include "geo.h"
#include "meteor.h"
#include "qry.h"
#include "svg.h"
#include "util.h"

typedef struct nve {
    double px, py;
} nve;

typedef struct Controller {
    /*Indica se o arquivo .qry será lido*/
    int exist_input_qry;

    Lista meteor_impacts;

    Lista nve_points;

} Controller;

Lista get_meteor_impact(Controlador __obj) {
    return ((Controller *)__obj)->meteor_impacts;
}

Lista nve_points(Controlador __obj) {
    return ((Controller *)__obj)->nve_points;
}

int get_exist_input_qry(Controlador __obj) {
    return ((Controller *)__obj)->exist_input_qry;
}

int destroy_controller(Controlador __obj) {
    if (!__obj) return puts("free_controller:\tParametro vazio");

    freeList(((Controller *)__obj)->meteor_impacts, 1, destroy_meteor);
    freeList(((Controller *)__obj)->nve_points, 1, free);

    free(__obj);

    return 1;
}

int set_exist_input_qry(Controlador __obj, int newI) {
    ((Controller *)__obj)->exist_input_qry = newI;

    return 1;
}

void *controller_factory() {
    Controller *controller = calloc(1, sizeof(Controller));

    controller->exist_input_qry = 0;
    controller->meteor_impacts = createLista(1);

    controller->nve_points = createLista(1);

    return controller ? controller : print_and_return_null("createController: Erro ao alocar memória");
}