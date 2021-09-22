#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dll.h"

#define abort_unless(expr) \
    if (!(expr)) {\
        fprintf(stderr, "Aborting since condition \"%s\" wan't met.\n", #expr);\
        abort();\
    }

struct dll_node_type {
    struct dll_node_type* next;
    struct dll_node_type* prev;
    void*                 data;
};

struct dll_type {
    dll_node_t* head;
    dll_node_t* tail;
    size_t      count;
};

dll_t*
dll_create(void)
{
    // Create our list
    dll_t* list = malloc(sizeof *list);

    // Init the head
    list->head       = malloc(sizeof *list->head);
    list->head->prev = list->head->data = NULL;

    // Init the tail
    list->tail       = malloc(sizeof *list->tail);
    list->tail->next = list->tail->data = NULL;

    // Head points to tail
    list->head->next = list->tail; 
    // Tail points back to head
    list->tail->prev = list->head; 

    // 0 elements at the beginning
	list->count = 0;

	return list;
}

void
dll_destroy(dll_t* list, dll_free_fn_t fn)
{
    // Empty the list
	dll_empty(list, fn);

    // Free special nodes and the actual list
    free(list->head);
    free(list->tail);
	free(list);
}

static dll_node_t*
dll_delete(dll_t* list, dll_node_t* node, dll_free_fn_t fn)
{
    dll_node_t* out = NULL;

    // Nothing to do here
    if (list->count == 0)
    {
        return NULL;
    }

	if (node->prev == NULL)
    {
		list->head = node->next;
	}
	else
	{
		node->prev->next = node->next;
	}
	if (node->next == NULL)
	{
		list->tail = node->prev;
	}
	else
	{
		node->next->prev = node->prev;
	}
    // Update the output node
    out = node->next;

    // Free stuff
    if (fn) {
        fn(node->data);
    }
	free(node);

    // Decrease count
    list->count--;
    return out;
}

void
dll_empty(dll_t* list, dll_free_fn_t fn)
{
    dll_node_t* current = list->head->next;
    while (current != list->tail) {
        current = dll_delete(list, current, fn);
	}
    abort_unless(list->count == 0);

    // Head points to tail
    list->head->next = list->tail; 
    // Tail points back to head
    list->tail->prev = list->head; 
    // And reset the count
	list->count = 0;
}

bool
dll_is_empty(const dll_t* list)
{
    return !list->count;
}

size_t
dll_count(const dll_t* list)
{
    return list->count;
}

static void
dll_insert_after(dll_t* list, dll_node_t*node, void* data)
{
    dll_node_t* new_node = malloc(sizeof *new_node);

	new_node->prev = node;
	new_node->next = node->next;

    if (node->next == list->tail) {
        list->tail->prev = new_node;
	}
	else {
		node->next->prev = new_node;
	}

	node->next     = new_node;
    new_node->data = data;

	list->count++;
}

static void
dll_insert_before(dll_t* list, dll_node_t*node, void* data)
{
    dll_node_t* new_node = malloc(sizeof *new_node);

	new_node->prev = node->prev;
	new_node->next = node;

    if (node->prev == list->head) {
        list->head->next = new_node;
	}
	else {
		node->prev->next = new_node;
	}
	node->prev     = new_node;
    new_node->data = data;

	list->count++;
}

void
dll_insert_beginning(dll_t* list, void* data)
{
    dll_insert_before(list, list->head->next, data);
}

void
dll_insert_end(dll_t* list, void* data)
{
    dll_insert_after(list, list->tail->prev, data);
}

static dll_node_t*
dll_peek_node_at(const dll_t* list, const size_t index)
{
    if (index >= list->count) {
        return NULL;
    }

    dll_node_t* node = list->head->next;
    size_t count = 0;
    while (node != list->tail) {
        if (count++ == index) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void*
dll_peek_at(const dll_t* list, const size_t index)
{
    const dll_node_t* node = dll_peek_node_at(list, index);

    if (!node) {
        return NULL;
    }

    return node->data;
}

void*
dll_extract_at(dll_t* list, const size_t index)
{
    dll_node_t* node = dll_peek_node_at(list, index);

    if (!node) {
        return NULL;
    }

    void* data = node->data;
    dll_delete(list, node, NULL);

    return data;
}

dll_t*
dll_clone(const dll_t* list)
{
    dll_t*      clone   = dll_create();
    dll_node_t* current = list->head->next;

    while (current != list->tail) {
        dll_append(clone, current->data);
        current = current->next;
    }
    return clone;
}

dll_node_t*
dll_find(const dll_t* list, dll_find_fn_t fn, void* arg)
{
    /* Searching function must be provided (otherwise, what's the point of this function? :)) */
    abort_unless(fn);

    dll_node_t* current = list->head->next;
    while (current != list->tail) {
        if (fn(current->data, arg)) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void*
dll_node_peek(const dll_node_t* node)
{
    return node->data;
}

void
dll_remove(dll_t* list, dll_node_t* node, dll_free_fn_t fn)
{
    dll_delete(list, node, fn);
}

static bool
dll_swap_nodes(dll_t* list, dll_node_t* node1, dll_node_t* node2)
{
    // Don't do this please...
    if (node1 == node2)
        return false;

    if (node1->next == node2) {
        node1->next = node2->next;
        node2->prev = node1->prev;

        if (node1->next != list->tail)
            node1->next->prev = node1;
        else
            list->tail->prev = node1;

        if (node2->prev != list->head)
            node2->prev->next = node2;
        else
            list->head->next = node2;

        node2->next = node1;
        node1->prev = node2;
    }
    else {
        dll_node_t* p = node2->prev;
        dll_node_t* n = node2->next;

        node2->prev = node1->prev;
        node2->next = node1->next;

        node1->prev = p;
        node1->next = n;

        if (node2->next != list->tail)
            node2->next->prev = node2;
        else
            list->tail->prev = node2;

        if (node2->prev != list->head)
            node2->prev->next = node2;
        else
            list->head->next = node2;

        if (node1->next != list->tail)
            node1->next->prev = node1;
        else
            list->tail->prev = node1;

        if (node1->prev != list->head)
            node1->prev->next = node1;
        else
            list->head->next = node1;

    }
    return true;
}

bool
dll_swap(dll_t* list, const size_t index1, const size_t index2)
{
    if (index1 < 0 || index1 >= list->count || index2 < 0 || index2 >= list->count)
        return false;

    // Swap these nodes, give the indexes in order
    size_t min = 0, max = 0;
    if (index1 < index2) {
        min = index1;
        max = index2;
    }
    else {
        min = index2;
        max = index1;
    }

    return dll_swap_nodes(list, dll_peek_node_at(list, min), dll_peek_node_at(list, max));
}

void
dll_print(const dll_t* list, dll_print_fn_t fn, void* arg)
{
    /* Printing function must be provided (otherwise, what's the point of this function? :)) */
    abort_unless(fn);

    dll_node_t* current = list->head->next;
    while (current != list->tail) {
        fn(current->data, arg);
        current = current->next;
    }
}

void
dll_foreach(const dll_t* list, dll_foreach_fn_t fn, void* arg)
{
    /* Function must be provided (otherwise, what's the point of this function? :)) */
    abort_unless(fn);

    dll_node_t* current = list->head->next;
    while (current != list->tail) {
        fn(current->data, arg);
        current = current->next;
	}
}

void*
dll_to_array(const dll_t* list, const size_t size_of_elem, size_t* rv_size)
{
    if (list->count == 0) {
        return NULL;
    }

    void*  outarray  = malloc(size_of_elem * list->count);
    size_t count     = 0;
    dll_node_t* node = list->head->next;

    while (node != list->tail) {
        memcpy(outarray + count++ * size_of_elem, node->data, size_of_elem);
        node = node->next;
    }

    *rv_size = count;

    return outarray;
}

dll_t*
dll_from_array(void* array, const size_t count, const size_t size_of_elem)
{
    dll_t* outlist = dll_create();

    for (size_t i = 0; i < count; ++i) {
        void* data = malloc(count * size_of_elem);
        memcpy(data, array + i*size_of_elem, size_of_elem);
        dll_append(outlist, data);
    }

    return outlist;
}
