#ifndef __DOUBLYLINKEDLIST_H
#define __DOUBLYLINKEDLIST_H

#include <stdio.h>
#include <stdbool.h>

typedef struct dll_node_type
{
    void * data;
    struct dll_node_type * next;
    struct dll_node_type * prev;

} dll_node_t;

typedef struct dll_type
{
    dll_node_t * head;
    dll_node_t * tail;

    int count;

} dll_t;

/*
 * Function:	dll_init
 * Brief:	    Initializes an empty dll.
 * Returns:	    Nothing
*/
dll_t *dll_init(void);

/*
 * Function:	dll_destroy
 * Brief:	    Destroys a given list.
 * @param list:	The list to destroy
 * Returns:	    Nothing, memory allocated by @list is freed.
*/
void dll_destroy(dll_t * list);

/*
 * Function:	dll_insert_after
 * Brief:	    Given a list and a node within the list, it inserts
 *              new data after the given node.
 * @param list:	The target list
 * @param node:	The node after which the data is to be inserted
 * @param p:	Pointer to raw data that the new node will keep
 * Returns:	    Nothing.
*/
void dll_insert_after(dll_t * list, dll_node_t * node, void * p);
/*
 * Function:	dll_insert_before
 * Brief:	    Given a list and a node within the list, it inserts
 *              new data before the given node.
 * @param list:	The target list
 * @param node: The node before which the data is to be inserted
 * @param p:    Pointer to raw data that the new node will keep
 * Returns:	    Nothing.
*/
void dll_insert_before(dll_t * list, dll_node_t * node, void * p);

/*
 * Function:	dll_insert_beginning
 * Brief:	    Given a list, it inserts data at the first position
 * @param list:	The target list
 * @param p:	Pointer to raw data that the new node will keep
 * Returns:	    Nothing.
*/
void dll_insert_beginning(dll_t * list, void * p); 
/*
 * Function:	dll_prepend
 * Brief:       Alias to function @dll_insert_beginning.
 * @param list:	The target list
 * @param p:	Pointer to raw data that the new node will keep
 * Returns:	    Nothing.
*/
void dll_prepend(dll_t * list, void * p);

/*
 * Function:	dll_insert_end
 * Brief:	    Given a list, it inserts data at the last position
 * @param list:	The target list
 * @param p:	Pointer to raw data that the new node will keep
 * Returns:	    Nothing.
*/
void dll_insert_end(dll_t * list, void * p); 
/*
 * Function:	dll_append
 * Brief:	    Alias to function @dll_insert_end
 * @param list:	The target list
 * @param p:	Pointer to raw data that the new node will keep
 * Returns:	    Nothing.
*/
void dll_append(dll_t * list, void * p);

/*
 * Function:	dll_at
 * Brief:	    Given an index, it returns the node associated to
 *              that position. Note that this function runs in O(n),
 *              so it should not be used to access a certain node
 *              when looping through the list, since it will loop
 *              through all elements until the current one.
 * @param list: The target list
 * @param index:The index of that node
 * Returns:	    If the index is within the list's count, it returns
 *              a pointer to the node at that position, otherwise a
 *              null pointer is returned.
*/
dll_node_t * dll_at(dll_t * list, int index);

/*
 * Function:	dll_extract_at
 * Brief:	    Given a list and an index, it removes the node at
 *              that position and copies its data for further use
 *              outside the list.
 * @param list:	The target list
 * @param index:The index associated with the node to remove
 * @param data:	Pointer to raw data that will be updated with the
 *              contents of the node to remove
 * @param size_of_data:	How many bytes will be copied
 * Returns:	    On success, a pointer to the next node in the list
 *              will be returned and the contents of the deleted
 *              node will have been copied to @data, exactly
 *              @size_of_data bytes. Otherwise, a null pointer will
 *              be returned.
*/
dll_node_t * dll_extract_at(dll_t * list, int index, void * data, size_t size_of_data);
/*
 * Function:	dll_extract
 * Brief:	    Given a list and a node belonging to it, it removes
 *              that node and copies its data for further use outside
 *              the list.
 * @param list:	The target list
 * @param node:	The node to remove
 * @param data:	Pointer to raw data that will be updated with the
 *              contents of the node to remove
 * @param size_of_data:	How many bytes will be copied
 * Returns:	    On success, a pointer to the next node in the list will
 *              be returned and the contents of the deleted node will
 *              have been copied to @data, exactly @size_of_data bytes.
 *              Otherwise, a null pointer will be returned.
*/
dll_node_t * dll_extract(dll_t * list, dll_node_t *node, void * data, size_t size_of_data);

/*
 * Function:	dll_delete_at
 * Brief:	    Given a list and an index, it removes the node associated
 *              with that position.
 * @param list:	The target list
 * @param index:The index corresponding to the node to remove
 * Returns:	    On success, a pointer to the next node on the list shall
 *              be returned.
*/
dll_node_t * dll_delete_at(dll_t * list, int index);
/*
 * Function:	dll_delete
 * Brief:	    Given a list and a node in the list, it removes the node.
 * @param list:	The target list
 * @param node:	The node to be removed
 * Returns:	    On success, a pointer to the next node on the list is
 *              returned
*/
dll_node_t * dll_delete(dll_t * list, dll_node_t *node);

/*
 * Function:	dll_print
 * Brief:	    Given a list and a custom-defined printing function
 *              for the node datatype, it outputs the contents of the
 *              list.
 *
 *              Note that this implementation of doubly linked list
 *              has been generalized to use any type of data type /
 *              structure as inner-node data, since every node holds
 *              a void * pointer. Hence, if the user wants to print
 *              the list with own datatypes he / she shall create a
 *              function that takes a raw data pointer as only input
 *              argument, cast it to the desired datatype and print it.
 *
 *              Example:
 *
 *              struct foo
 *              {
 *                  int a;
 *                  char b;
 *                  float c;
 *              }
 *
 *              The list contains elements of the type 'struct foo'.
 *              Hence a function similar to the following one shall
 *              be defined somewhere:
 *
 *              void printing_function(void * data)
 *              {
 *                  struct foo * item = (struct foo *) data;
 *                  printf("%d, %c, %f\n", item->a, item->b, item->c);
 *              }
 *
 *              And in order to print the whole list:
 *
 *              .....
 *              dll_print(my_list, printing_function);
 *              .....
 * @param list:	The target list
 * @param custom_print:	Function pointer to the user-defined
 *                      node-printing function
 * Returns:	    Nothing.
*/
void dll_print(dll_t * list, void (*custom_print)(void *));
/*
 * Function:	dll_print_node
 * Brief:	    Given a node belonging to the list, it prints its contents (see
 *              comments on how to pass a user-defined function on the description
 *              of @dll_print)
 * @param node:	Pointer to the node in question
 * @param custom_print:	Function pointer to the user-defined node-printing function
 * Returns:	    Nothing.
*/
void dll_print_node(dll_node_t * node, void (*custom_print)(void *));

/*
 * Function:	dll_emtpy
 * Brief:	    Given a list, it removes all its nodes and becomes and empty list
 *              (as in after a call to @dll_init).
 * @param list:	The target list
 * Returns:	    Nothing.
*/
void dll_empty(dll_t * list);
/*
 * Function:	dll_is_empty
 * Brief:	    Given a list, it determines whether the list is empty or not
 * @param list: The target list
 * Returns:	    true if the list is empty, false otherwise
*/
bool dll_is_empty(dll_t * list);

/*
 * Function:	dll_copy_list
 * Brief:	    Given a list, it outputs a copy it. It allocates new memory
 *              for the data held by the nodes.
 * @param rhs:	The list to be copied
 * @param size_of_data: Byte count of the data type being held by every node.
 * Returns:	    Pointer to the newly create list out of @rhs
*/
dll_t * dll_copy_list(dll_t * rhs, size_t size_of_data);

/*
 * Function:	dll_to_array
 * Brief:	    Given a list, it converts it to a C-style array
 * @param list:	The target list
 * @param size_of_data:	Byte count of every inner-node data
 * Returns:	    Pointer to raw data containing the list as an array.
*/
void * dll_to_array(dll_t * list, size_t size_of_data);
/*
 * Function:	dll_from_array
 * Brief:	    Given an array and the length of the array and the size of every
 *              element, it returns a list containing that data.
 * @param array:The array to convert
 * @param count:The number of elements in the array
 * @param size_of_data:	Byte count of the array elements
 * Returns:	    Pointer to the new list
*/
dll_t   * dll_from_array(void * array, int count, size_t size_of_data);

/*
 * Function:	dll_swap
 * Brief:	    Given a list and two indexes in that list, it swaps the nodes
 *              at the given positions
 * @param list:	The target list
 * @param index1:	Position on that list
 * @param index2:	Position on that list
 * Returns:	    true on success, false otherwise
*/
bool dll_swap(dll_t * list, int index1, int index2);
/*
 * Function:	dll_swap_nodes
 * Brief:	    Given a list and two nodes on that list, it swaps them
 * @param list:	The targe tlist
 * @param node1:Node on that list
 * @param node2:Node on that list
 * Returns:	    true on success, false otherwise
*/
bool dll_swap_nodes(dll_t * list, dll_node_t * node1, dll_node_t * node2);

#endif /* __DOUBLYLINKEDLIST_H */

