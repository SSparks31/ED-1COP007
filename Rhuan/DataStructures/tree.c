#include "tree.h"

#include "../GeometricForms/rectangle.h"
#include "../controller.h"
#include "../util.h"
#include "list.h"

typedef struct node {
    void* data;
    int kd_way;
    int visible;
    struct node* father;
    struct node* left_son;
    struct node* right_son;
} node;

typedef struct tree {
    size_t size;
    node* root;
    int type_of_tree;
    int type_of_data;
} tree;

void* father(void* __node) {
    return ((node*)__node)->father;
}

void* right_son(void* st_node) {
    node* node = st_node;
    return node ? node->right_son : NULL;
}

void* left_son(void* st_node) {
    node* node = st_node;
    return node ? node->left_son : NULL;
}

void* root(void* st_node) {
    tree* node = st_node;
    return node->root;
}

void* get_data(void* st_node) {
    node* node = st_node;

    return node ? node->data : NULL;
}

int get_visible(void* st_node) {
    node* node = st_node;

    return node ? node->visible : puts("get_visible: Parametro invalido") - ERROR;
}

int destroy_node(void* st_current_node, int (*free_data)(void* __data), int free_data_cont) {
    node* current_node = st_current_node;

    if (!current_node) return puts("destroy_node: Parametro invalido");

    if (free_data_cont) {
        free_data(current_node->data);
        free(current_node->data);
    }
    free(current_node);

    return 1;
}

int tree_type(Arvore st_tree) {
    tree* tree = st_tree;

    return tree ? tree->type_of_tree : puts("tree_type: Parametro invalido");
}

Arvore tree_factory(int tree_type, int data_type) {
    tree* output = calloc(1, sizeof(tree));

    if (!output) return print_and_return_null("create_tree:\tErro ao alocar a memoria");

    output->type_of_tree = tree_type;
    output->type_of_data = data_type;
    output->root = NULL;

    return output;
}

int data_type(Arvore st_tree) {
    tree* tree = st_tree;

    return tree ? tree->type_of_data : puts("data_type: Parametro invalido");
}

int insert_tree_recursion(tree* main_tree, node* current_node, void* data, int (*compare_nodes)(void* node1, void* node2)) {
    node* new_node = NULL;
    int comp = compare_nodes(current_node->data, data);
    
    if (comp == 1 || comp == 0)
        if (current_node->right_son)
            insert_tree_recursion(main_tree, current_node->right_son, data, compare_nodes);
        else {
            new_node = calloc(1, sizeof(node));
            current_node->right_son = new_node;
        }

    if (comp == -1)
        if (current_node->left_son)
            insert_tree_recursion(main_tree, current_node->left_son, data, compare_nodes);
        else {
            new_node = calloc(1, sizeof(node));
            current_node->left_son = new_node;
        }

    if (new_node) {
        new_node->visible = 1;
        new_node->data = data;
        new_node->father = current_node;
        new_node->left_son = NULL;
        new_node->right_son = NULL;
        main_tree->size++;
    }

    return 1;
}

int kd_set(node* current_node, int camada, int (*set_kd)(void* __obj, const int __dep)) {
    if(current_node->left_son)
        kd_set(current_node->left_son, camada ? 0 : 1, set_kd);

    if (current_node->right_son)
        kd_set(current_node->right_son, camada ? 0 : 1, set_kd);

    set_kd(current_node->data, camada);
}

int insert_tree(Arvore st_tree, void* data, int (*compare_nodes)(void* node1, void* node2), int (*set_kd)(void* __obj, const int __dep)) {
    tree* tree = st_tree;

    if (!tree) return puts("insert_tree:\tA memoria da arvore esta vazia") - ERROR;

    if (!data) return puts("insert_tree:\tData esta vazia") - ERROR;

    if (!tree->root) {
        tree->root = calloc(1, sizeof(node));
        tree->root->visible = 1;
        tree->root->right_son = NULL;
        tree->root->left_son = NULL;
        tree->root->father = NULL;
        tree->root->data = data;
        tree->size++;

        kd_set(tree->root, 0, set_kd);

        // printf("Size %ld\n", tree->size);

        return 1;
    }

    insert_tree_recursion(tree, tree->root, data, compare_nodes);

    kd_set(tree->root, 0, set_kd);

    // printf("Size %ld\n", tree->size);

    return 1;
}

int debug_tab(int camada) {
    for (int i = 0; i < camada; i++)
        printf("\t");

    return 1;
}

int run_tree_recursion(node* current_node, int (*print_node)(void* data_node), int camada, int where) {
    print_node(current_node->data);

    if (current_node->right_son)
        run_tree_recursion(current_node->right_son, print_node, camada + 1, 1);

    if (current_node->left_son)
        run_tree_recursion(current_node->left_son, print_node, camada + 1, 0);

    return 1;
}

int run_tree(Arvore st_tree, String message, int (*print_node)(void* data_node)) {
    tree* tree = st_tree;
    int camada = 0;

    if (!st_tree) return puts("run_tree: A memoria da arvore esta vazia") - ERROR;

    print_node(tree->root->data);

    if (tree->root->right_son)
        run_tree_recursion(tree->root->right_son, print_node, camada + 1, 1);

    if (tree->root->left_son)
        run_tree_recursion(tree->root->left_son, print_node, camada + 1, 0);

    return 1;
}

node* deepest_node(node* current_node) {
    if (!current_node) return print_and_return_null("deepest_node:\t\tParametro invalido");

    if (!current_node->left_son) return current_node;

    return deepest_node(current_node->left_son);
}

int new_root(tree* tree, node* new) {
    node* aux;

    aux = tree->root;

    tree->root = new;
    tree->root->father = NULL;

    free(aux->data);
    free(aux);

    return 1;
}

int new_root_with_two_sons(tree* tree) {
    node* aux = deepest_node(tree->root->right_son);

    // bites_zadasto(tree->root->data);
    //free(tree->root->data);
    tree->root->data = aux->data;

    if (!aux->right_son) {
        if (aux != tree->root->right_son)
            aux->father->left_son = NULL;
        else {
            tree->root->right_son = NULL;
        }
        free(aux);

        return 1;
    }

    tree->root->right_son = aux->right_son;
    free(aux);

    tree->size--;
    return 1;
}

int remove_one_size_tree(Arvore st_tree) {
    tree* tree = st_tree;

    free(tree->root->data);
    free(tree->root);

    tree->root = NULL;

    return 1;
}

int remove_reference(node* father, node* new, int where) {
    if (where) {
        new->father = father;
        father->right_son = new;
    }

    if (!where) {
        new->father = father;
        father->left_son = new;
    }
    return 1;
}

int remove_this_element(tree* tree, node* current_node, int where, int (*free_data)(void* __data), int free_data_cont) {
    node* old_node = NULL;

    /*    0 - 0    */
    if (!current_node->left_son && !current_node->right_son) {
        if (where)
            current_node->father->right_son = NULL;

        if (!where)
            current_node->father->left_son = NULL;

        destroy_node(current_node, free_data, free_data_cont);

        tree->size--;
        return 1;
    }

    /*    # - 1    */
    if (current_node->right_son) {
        puts("AQUI1");
        node* aux = deepest_node(current_node->right_son);

        if (free_data_cont) {
            free_data(current_node->data);
        }

        current_node->data = aux->data;

        if (!aux->right_son) {
            if (aux != current_node->right_son) {
                aux->father->left_son = NULL;
            } else {
                current_node->right_son = NULL;
            }

            tree->size--;
            free(aux);
            return 1;
        }
        current_node->right_son = aux->right_son;
        aux->right_son->father = current_node;

        tree->size--;
        free(aux);
        return 1;
    }

    /*    1 - 0    */
    if (current_node->left_son && !current_node->right_son) {
        remove_reference(current_node->father, current_node->left_son, where);

        destroy_node(current_node, free_data, free_data_cont);

        tree->size--;
        return 1;
    }

    return 1;
}

int remove_element_tree_recursion(tree* tree, node* current_node, void* data, int (*compare_nodes)(void* node1, void* node2), int (*free_data)(void* __data), int free_data_cont) {
    int comp;

    if (!current_node) return puts("remove_element_tree_recursion:\tEste elemento nao pertence a lista") - ERROR;

    if (current_node->right_son)

        if (compare_nodes(current_node->right_son->data, data) == IGUAL) {
            if (tree->type_of_tree == kd)
                current_node->right_son->visible = 0;
            else
                remove_this_element(tree, current_node->right_son, 1, free_data, free_data_cont);

            return 1;
        }

    if (current_node->left_son)

        if (compare_nodes(current_node->left_son->data, data) == IGUAL) {
            if (tree->type_of_tree == kd)
                current_node->left_son->visible = 0;

            else
                remove_this_element(tree, current_node->left_son, 0, free_data, free_data_cont);

            return 1;
        }

    comp = compare_nodes(current_node->data, data);

    if (comp == DIREITA) remove_element_tree_recursion(tree, current_node->right_son, data, compare_nodes, free_data, free_data_cont);

    if (comp == ESQUERDA) remove_element_tree_recursion(tree, current_node->left_son, data, compare_nodes, free_data, free_data_cont);

    return 1;
}

int remove_element_tree(Arvore st_tree, void* data, int (*compare_nodes)(void* node1, void* node2), int (*set_kd)(void* __obj, const int __dep), int (*free_data)(void* __data), int free_data_cont) {
    tree* tree = st_tree;

    if (!tree) return puts("remove_element_tree:\tA memoria da arvore esta vazia") - ERROR;

    if (!data) return puts("remove_element_tree:\tData esta vazia") - ERROR;

    if (!tree->root) return puts("remove_element_tree:\tArvore vazia") - ERROR;

    if (compare_nodes(tree->root->data, data) == IGUAL) {
        if (tree->type_of_tree == kd) {
            tree->root->visible = 0;

            // bites_zadasto(tree->root->data);

            return 1;
        }

        if (!tree->root->left_son && !tree->root->right_son)
            remove_one_size_tree(tree);

        else if (tree->root->right_son && !tree->root->left_son)
            new_root(tree, tree->root->right_son);

        else if (tree->root->left_son && !tree->root->right_son)
            new_root(tree, tree->root->left_son);

        else if (tree->root->right_son && tree->root->left_son)
            new_root_with_two_sons(tree);

    }

    else if (tree->type_of_tree == kd) {
        node* aux = search_tree(tree, data, compare_nodes);

        if (aux) {
            // bites_zadasto(aux->data);
            aux->visible = 0;
        } else
            puts("remove_element_tree:\tEste elemento nao pertence a arvore") - ERROR;
    }

    else
        remove_element_tree_recursion(tree, tree->root, data, compare_nodes, free_data, free_data_cont);

    if (set_kd)
        set_kd(tree->root, 0);

    return 1;
}

int free_tree_recursion(node* node, int (*free_data)(void* __data), int free_data_cont) {
    if (node->right_son) free_tree_recursion(node->right_son, free_data, free_data_cont);

    if (node->left_son) free_tree_recursion(node->left_son, free_data, free_data_cont);

    destroy_node(node, free_data, free_data_cont);

    return 1;
}

Arvore destroy_tree(Arvore st_tree, int (*free_data)(void* __data), int free_data_cont) {
    tree* tree = st_tree;

    if (!st_tree) return print_and_return_null("free_tree:\tA memoria da arvore esta vazia");

    if (tree->root) {
        if (tree->root->right_son)
            free_tree_recursion(tree->root->right_son, free_data, free_data_cont);

        if (tree->root->left_son)
            free_tree_recursion(tree->root->left_son, free_data, free_data_cont);

        destroy_node(tree->root, free_data, free_data_cont);
    }

    free(tree);

    return NULL;
}

Celula search_tree_recursion(node* current_node, void* data, int (*compare_nodes)(void* node1, void* node2)) {
    if (compare_nodes(current_node->data, data) == IGUAL && current_node->visible) return current_node;

    if (current_node->right_son)
        if (compare_nodes(current_node->data, data) == DIREITA) return search_tree_recursion(current_node->right_son, data, compare_nodes);

    if (current_node->left_son)
        if (compare_nodes(current_node->data, data) == ESQUERDA) return search_tree_recursion(current_node->left_son, data, compare_nodes);

    if (current_node->left_son || current_node->right_son) {
        void *out1 = NULL, *out2 = NULL;

        if (current_node->right_son)
            if (compare_nodes(current_node->data, data) == 2) out1 = search_tree_recursion(current_node->right_son, data, compare_nodes);

        if (current_node->left_son)
            if (compare_nodes(current_node->data, data) == 2) out2 = search_tree_recursion(current_node->left_son, data, compare_nodes);

        if (out1) return out1;

        if (out2) return out2;
    }

    return NULL;
}

Celula search_tree(Arvore st_tree, void* data, int (*compare_nodes)(void* node1, void* node2)) {
    tree* tree = st_tree;

    if (!st_tree) return print_and_return_null("search_tree:\tA memoria da arvore esta vazia");

    void* aux = search_tree_recursion(tree->root, data, compare_nodes);

    return aux ? aux : NULL;
}
