/* Interface file of Red Black Tree ADT */

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdbool.h>

// generic-pointer typedef
typedef void *Pointer;

/* pointer to function that compares two elements a and b. Returns:
   < 0 if a < b
   = 0 if a = b (based on given comparison)
   > 0 if a > b                                                   */
typedef int (*CompareFunc)(Pointer a, Pointer b);

// pointer to function that destroys given element
typedef void (*DestroyFunc)(Pointer);

// pointer to function printing red_black tree's item
typedef void (*PrintFunc)(Pointer);

// pointer to red black tree
typedef struct red_black_tree *RedBlackTree;

/*-----Functions Provided-----*/

// initializes an empty red black tree
void red_black_initialize(RedBlackTree *, CompareFunc, DestroyFunc, PrintFunc);

// inserts a new item in the right place in the red black tree
void red_black_insert(Pointer, RedBlackTree);

// removes and destroys given item from the red black tree
void red_black_remove(Pointer, RedBlackTree);

// prints items of the red black tree
void red_black_print(RedBlackTree);

// destroys the given red black tree by freeing all nodes
void red_black_destroy(RedBlackTree);

// returns the number of elements in the red black tree
int red_black_size(RedBlackTree);

// returns true/false depending on if red black tree is empty or not
bool red_black_is_empty(RedBlackTree);

// returns true/false based on if given item is found in the red black tree or not
bool red_black_search(Pointer, RedBlackTree);

// returns the root element of the red black tree
Pointer red_black_root(RedBlackTree);

// returns the element with lowest value
Pointer red_black_min(RedBlackTree);

// returns the element with highest value
Pointer red_black_max(RedBlackTree);

// sets as new CompareFunc of given red black tree the given one
void red_black_set_compare(RedBlackTree, CompareFunc);

// sets as new DestroyFunc of given red black tree the given one
void red_black_set_destroy(RedBlackTree, DestroyFunc);

// sets as new PrintFunc of given red black tree the given one
void red_black_set_print(RedBlackTree, PrintFunc);

#endif