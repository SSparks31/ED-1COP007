#ifndef MODULE_LIST_H
#define MODULE_LIST_H

typedef struct list* List;
typedef struct list_pos* List_pos;
typedef void* List_elem;

List create_list();

int list_get_size(List list);

List_elem list_get_elem(List list, List_pos pos);

List_pos list_append(List list, List_elem elem);

List_pos list_insert_before(List list, List_pos pos, List_elem elem);

List_pos list_insert_after(List list, List_pos pos, List_elem elem);

void list_remove(List list, List_pos pos);

List_pos list_get_first(List list);

List_pos list_get_next(List list, List_pos pos);

List_pos list_get_prev(List list, List_pos pos);

List_pos list_get_last(List list);

void list_destroy(List* list);

#endif