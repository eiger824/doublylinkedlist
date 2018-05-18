/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  A simple test file for the doubly linked list
 *
 *        Version:  1.0
 *        Created:  2018-05-10 09:45:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Santiago Pagola (), santipagola@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "dll.h"

#define NR_ELEMS 20

void print_particle(void * data)
{
    // We know our list has integers
    printf("%d\n", *(int*)data);
}

int main(int argc, char* argv[])
{
    printf("sizeof list:\t%lu\n", sizeof(dll_t));
    printf("sizeof node:\t%lu\n", sizeof(dll_node_t));
    struct timeval t0, t1;
    double elapsed;
    dll_t * list = dll_init();
    // fill up with some elems
    srand(time(NULL));

    for (unsigned i = 0; i < NR_ELEMS; ++i)
    {
        int * c = (int*)malloc(sizeof *c);
        *c = i;
        dll_append(list, (void*)c);
    }
    
    /* Print the list with our helper function */
    dll_print(list, print_particle);

    // Let's try accessing element nr. 199980 (at the end)
    unsigned int target = 19;
    gettimeofday(&t0, NULL);
    dll_node_t * result = dll_at(list, target);
    gettimeofday(&t1, NULL);
    elapsed = ((double)(t1.tv_sec) - (double)(t0.tv_sec)) * 1e3;
    elapsed += ((double)(t1.tv_usec) - (double)(t0.tv_usec)) / 1e3;
    printf("The data at position '%d' is:\t%d\n", target, *(int*)result->data);
    printf("Elapsed time:\t%.5f msecs\n", elapsed);

    dll_node_t * current = list->head->next;
    while (current != list->tail)
    {
        printf("%d\n", *(int*)current->data);
        current = current->next;
    }

    printf("Swapping elems 14 and 9...\n");
    dll_swap(list, 14, 9);

    current = list->head->next;
    dll_node_t * foo;
    int i = 0;
    while (current != list->tail)
    {
        foo = current->next;
        while (foo != list->tail)
        {
            if (i++ == 5)
            {
                printf("Swap!\n");
                dll_swap_nodes(list, current->next, foo);
                current = current->next;
            }
            foo = foo->next;
        }
        current = current->next;
    }


    printf("List looks like this at the end:\n");
    current = list->head->next;
    while (current != list->tail)
    {
        printf("%d\n", *(int*)current->data);
        current = current->next;
    }
    printf("Destroying...\n");
    dll_destroy(list);
    return 0;
}

