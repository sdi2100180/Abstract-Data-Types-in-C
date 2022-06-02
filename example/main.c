#include <stdio.h>
#include <stdlib.h>
#include "../lib/ADT.h"

//-----int-----//

// CompareFunc that compares two integers
int compare_ints(Pointer a, Pointer b)
{
    int *ia = a;
    int *ib = b;
    return (*ia - *ib);
}

// PrintFunc that prints an integer
void print_int(Pointer a)
{
    int *ia = a;
    printf("Item = %2d\n", *ia);
}

//-----struct-----//

typedef struct test_struct{
    int x;
    int y;
}test;

// compares two test structs
int compare_structs(Pointer a, Pointer b)
{
    test *ia = a, *ib = b;
    return ia->x - ib->x;
}

// destroys a test struct node
void destroy_struct(Pointer a)
{
    free(a);
}

// prints c and y of a test struct
void print_struct(Pointer a)
{
    test *ia = a;
    printf("x = %2d | y = %2d\n", ia->x, ia->y);
}

int main(void)
{
    // red-black tree
    RedBlackTree rbt;
    red_black_initialize(&rbt, compare_ints, NULL, print_int);
    int a4 = 4;
    red_black_insert(&a4, rbt);
    int a7 = 7;
    red_black_insert(&a7, rbt);
    int a12 = 12;
    red_black_insert(&a12, rbt);
    int a15 = 15;
    red_black_insert(&a15, rbt);
    printf("Initial red-black tree:\n");
    red_black_print(rbt);
    printf("The root of the red-black tree is ");
    print_int(red_black_root(rbt));
    printf("After removing 12:\n");
    red_black_remove(&a12, rbt);
    red_black_print(rbt);
    printf("After removing 7:\n");
    red_black_remove(&a7, rbt);
    red_black_print(rbt);
    printf("The root of the red-black tree is ");
    print_int(red_black_root(rbt));
    red_black_destroy(rbt);

    // priority queue
    PriorityQueue pq;
    pq_initialize(&pq, compare_structs, destroy_struct, print_struct);
    test *t1 = malloc(sizeof(test));
    t1->x = 1;
    t1->y = 2;
    pq_insert(t1, pq);
    test *t2 = malloc(sizeof(test));
    t2->x = 3;
    t2->y = 9;
    pq_insert(t2, pq);
    test *t3 = malloc(sizeof(test));
    t3->x = 2;
    t3->y = 4;
    pq_insert(t3, pq);
    printf("\nPriority queue:\n");
    while (!pq_is_empty(pq)){
        test *removed = pq_remove(pq);
        printf("Removed item: ");
        print_struct(removed);
        destroy_struct(removed);
    }
    pq_destroy(pq);

    return 0;
}