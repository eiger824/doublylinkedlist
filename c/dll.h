#ifndef __DOUBLYLINKEDLIST_H
#define __DOUBLYLINKEDLIST_H

#include <stdio.h>
#include <stdbool.h>

/* Move this to definitions.h */
typedef struct dll_node_type
{
    void * data;
    struct dll_node_type *next;
    struct dll_node_type *prev;

} dll_node_t;

typedef struct dll_type
{
    dll_node_t * head;
    dll_node_t * tail;

    int count;

} dll_t;

dll_t *dll_init(void);
void dll_destroy(dll_t * list);

void dll_insert_after(dll_t * list, dll_node_t *node, void * p);
void dll_insert_before(dll_t * list, dll_node_t *node, void * p);

void dll_insert_beginning(dll_t * list, void * p); 
void dll_prepend(dll_t * list, void * p);

void dll_insert_end(dll_t * list, void * p); 
void dll_append(dll_t * list, void * p);

dll_node_t * dll_at(dll_t * list, int index);

dll_node_t * dll_extract_at(dll_t * list, int index, void * data, size_t size_of_data);
dll_node_t * dll_extract(dll_t * list, dll_node_t *node, void * data, size_t size_of_data);

dll_node_t * dll_delete_at(dll_t * list, int index);
dll_node_t * dll_delete(dll_t * list, dll_node_t *node);

void dll_print(dll_t * list, void (*custom_print)(void *));
void dll_print_node(dll_node_t * node, void (*custom_print)(void *));

void dll_empty(dll_t * list);
bool dll_is_empty(dll_t * list);

dll_t * dll_copy_list(dll_t * rhs);

void * dll_to_array(dll_t * list, size_t size_of_data);
dll_t   * dll_from_array(void * array, int count, size_t size_of_data);

bool dll_swap(dll_t * list, int index1, int index2);
bool dll_swap_nodes(dll_t * list, dll_node_t * node1, dll_node_t * node2);

#endif /* __DOUBLYLINKEDLIST_H */
