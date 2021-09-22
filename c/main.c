/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  A simple test file for the doubly linked list
 *
 *        Version:  2.0
 *        Created:  2018-05-10 09:45:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Santiago Pagola (), santipagola@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "dll.h"

#define NR_ELEMS 20

// Test utilities
#define expect(actual, expected) \
    if (actual != expected) {\
        fprintf(stderr, "Condition \"%s == %s\" was not met.\n", #actual, #expected);\
        abort();\
    }

static void
print_list(const void* data, void* arg)
{
    (void)arg;

    // We know our list has integers
    printf("%d ", *(int*)data);
}

static void
list_foreach_fn(const void* data, void* arg)
{
    const int current = *(const int*)data;
    int       *sum    = arg;

    *sum += current;
}

static bool
list_cmp_fn(const void* elem_, void* arg)
{
    const int current = *(int*)elem_;
    const int target  = *(int*)arg;

    return current == target;
}

int
main(int argc, char* argv[])
{
    dll_t* dll = dll_create();
    expect(dll_is_empty(dll), true);

    int nums[5] = {13, 1, 4, -2, 7};
    for (size_t i = 0; i < 5; ++i) {
        dll_append(dll, &nums[i]);
    }

    expect(dll_count(dll), 5);

    int first = 3;
    dll_insert_beginning(dll, &first);
    expect(dll_count(dll), 6);

    const int verify_first = *(int*)dll_peek_at(dll, 0);
    expect(verify_first, first);

    // Let's remove node at position 4
    const int extracted = *(int*)dll_extract_at(dll, 4);
    expect(extracted, -2);

    // clone && empty
    dll_t* clone = dll_clone(dll);
    expect(dll_is_empty(clone), false);
    expect(dll_count(clone), 5);

    dll_empty(clone, NULL);
    expect(dll_is_empty(clone), true);
    expect(dll_count(clone), 0);

    dll_destroy(clone, NULL);

    // swap
    expect(dll_swap(dll, 2, 3), true);
    expect(dll_swap(dll, -2, 3), false);
    expect(dll_swap(dll, 0, 38), false);

    // print
    printf("List: ");
    dll_print(dll, print_list, NULL);
    printf("\n");

    // foreach
    int sum = 0;
    dll_foreach(dll, list_foreach_fn, &sum);
    expect(sum, 28);

    // list contains following values: {3 13 4 1 7}
    expect(dll_count(dll), 5);

    // to array
    size_t array_size = 0;
    int*   array      = dll_to_array(dll, sizeof(int), &array_size);
    expect(array_size, 5);

    expect(array[0], 3);
    expect(array[1], 13);
    expect(array[2], 4);
    expect(array[3], 1);
    expect(array[4], 7);

    // back to list
    dll_t* new_list = dll_from_array(array, 5, sizeof(int));
    expect(dll_count(new_list), 5);
    expect(*(int*)dll_peek_at(new_list, 0), 3);
    expect(*(int*)dll_peek_at(new_list, 1), 13);
    expect(*(int*)dll_peek_at(new_list, 2), 4);
    expect(*(int*)dll_peek_at(new_list, 3), 1);
    expect(*(int*)dll_peek_at(new_list, 4), 7);

    // test macros
    int awesome_first_element = 37;
    dll_prepend(new_list, &awesome_first_element);

    int fancy_last_element = 1234567890;
    dll_append(new_list, &fancy_last_element);
    expect(dll_count(new_list), 7);

    // let's find the integer 7
    int       target = 7;
    const int match  = *(int*)dll_find(new_list, list_cmp_fn, &target);
    expect(match, target);

    // find something that doesn't exist
    target = -23;
    const void* found = dll_find(new_list, list_cmp_fn, &target);
    expect(found, NULL);

    expect(*(int*)dll_delete_at(new_list, 2), 13);
    // list contains now the following values: {37 3 4 1 7 1234567890}
    expect(dll_count(new_list), 6);

    expect(*(int*)dll_extract_first(new_list), 37);
    // list contains now the following values: {3 4 1 7 1234567890}
    expect(dll_count(new_list), 5);

    expect(*(int*)dll_pop_first(new_list), 3);
    // list contains now the following values: {4 1 7 1234567890}
    expect(dll_count(new_list), 4);

    expect(*(int*)dll_extract_last(new_list), 1234567890);
    // list contains now the following values: {4 1 7}
    expect(dll_count(new_list), 3);

    expect(*(int*)dll_extract_last(new_list), 7);
    // list contains now the following values: {4 1}
    expect(dll_count(new_list), 2);

    // cleanup
    dll_destroy(dll, NULL);
    dll_destroy(new_list, free);
    free(array);

    return 0;
}
