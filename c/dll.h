#ifndef DOUBLYLINKEDLIST_H_
#define DOUBLYLINKEDLIST_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct dll_type      dll_t;
typedef struct dll_node_type dll_node_t;

/* Utility function prototypes. */
typedef void (*dll_print_fn_t)(const void* data, void* arg);
typedef void (*dll_foreach_fn_t)(const void* data, void* arg);
typedef bool (*dll_find_fn_t)(const void* data, void* arg);
typedef void (*dll_free_fn_t)(void* data);

/**
 * @brief Create an empty list.
 *
 * @return List.
 */
dll_t*
dll_create(void);

/**
 * @brief Destroys a list.
 *
 * @param list List.
 * @param fn   Function to free the inner nodes' data (can be NULL).
 */
void
dll_destroy(dll_t* list, dll_free_fn_t fn);

/**
 * @brief Empty the current list.
 *
 * @param list List.
 * @param fn   Function to free the inner nodes' data (can be NULL).
 */
void
dll_empty(dll_t* list, dll_free_fn_t fn);

/**
 * @brief Test whether the list is empty.
 *
 * @param list List.
 *
 * @return True if empty.
 */
bool
dll_is_empty(const dll_t* list);

/**
 * @brief Get the number of elements in the list.
 *
 * @param list List.
 *
 * @return Element count.
 */
size_t
dll_count(const dll_t* list);

/* Modifiers. */
/**
 * @brief Prepend an element to the list.
 *
 * @param list List.
 * @param p    Element to prepend.
 */
void
dll_insert_beginning(dll_t* list, void* p); 
#define dll_prepend(list, data) dll_insert_beginning(list, data)

/**
 * @brief Append and element to the list.
 *
 * @param list List.
 * @param p    Element to append.
 */
void
dll_insert_end(dll_t* list, void* p); 
#define dll_append(list, data) dll_insert_end(list, data)

/**
 * @brief Get the element at the provided index.
 *        Runs in O(n) (worst case), so don't over-use.
 *
 * @param list  List.
 * @param index Position of the element in the list.
 *
 * @return Element at position @p index.
 */
void*
dll_peek_at(const dll_t* list, size_t index);

/**
 * @brief Remove (extract) the element at the provided index.
 *
 * @param list  List.
 * @param index Position of the element in the list (to be removed).
 *
 * @return Element at position @p index before removal.
 */
void*
dll_extract_at(dll_t* list, size_t index);
#define dll_delete_at(list, index) dll_extract_at(list, index)
#define dll_extract_first(list) dll_extract_at(list, 0)
#define dll_pop_first(list) dll_extract_first(list)
#define dll_extract_last(list) dll_extract_at(list, dll_count(list) ? dll_count(list)-1 : 0)
#define dll_pop_last(list) dll_extract_last(list)

/**
 * @brief Create a clone of the given list.
 *
 * @param list List to clone.
 *
 * @return New list, clone of @p rhs.
 */
dll_t*
dll_clone(const dll_t* list);

/**
 * @brief Find a given element in the list, matching the search criteria given with a custom function.
 *
 * @param list List.
 * @param fn   Search function (must be provided).
 * @param arg  Argument sent to @p fn.
 *
 * @return Pointer to the node whose data matches the search criteria, or NULL if no such element was found.
 */
dll_node_t*
dll_find(const dll_t* list, dll_find_fn_t fn, void* arg);

/**
 * @brief Returns the inner-data contained in the given node.
 *
 * @param node List node.
 *
 * @return Raw data pointer contained in @p node.
 */
void*
dll_node_peek(const dll_node_t* node);

/**
 * @brief Removes the given node from the list, possibly applying a custom function to free the node's inner-data.
 *
 * @param list List.
 * @param node Node to remove.
 * @param fn   Function to destroy @p node's data.
 */
void
dll_remove(dll_t* list, dll_node_t* node, dll_free_fn_t fn);

/**
 * @brief Swap two given nodes of the list by providing their index.
 *
 * @param list   List.
 * @param index1 Index of node 1.
 * @param index2 Index of node 2.
 *
 * @return True if the swap was performed.
 */
bool
dll_swap(dll_t* list, size_t index1, size_t index2);

/**
 * @brief Print the list given a custom printing function.
 *
 * @param list List.
 * @param fn   Printing function (must be provided).
 * @param arg  Argument sent to @p fn.
 */
void
dll_print(const dll_t* list, dll_print_fn_t fn, void* arg);

/**
 * @brief Iterate over all elements in the list, applying a custom function on each of them.
 *
 * @param list List.
 * @param fn   Function to apply to the elements (must be provided).
 * @param arg  Argument sent to @p fn.
 */
void
dll_foreach(const dll_t* list, dll_foreach_fn_t fn, void* arg);

/**
 * @brief Convert the given list to an array.
 *
 * @param list         List.
 * @param size_of_elem Size of the elements in the list, in bytes.
 * @param rv_size      Size of the output array (i.e., number of elements in it).
 *
 * @return Pointer to an array on the heap (caller must free it).
 */
void*
dll_to_array(const dll_t* list, size_t size_of_elem, size_t* rv_size);

/**
 * @brief Given an input array, create a list containing its elements.
 *        Note that elements will be allocated dynamically, so these need to be free'd when destroying the output list.
 *
 * @param array        Array containing the elements.
 * @param count        Number of elements in @p array.
 * @param size_of_elem Size of the elements in the array, in bytes.
 *
 * @return List containing all elements in the input array.
 */
dll_t*
dll_from_array(void* array, size_t count, size_t size_of_elem);
#endif /* DOUBLYLINKEDLIST_H_ */
