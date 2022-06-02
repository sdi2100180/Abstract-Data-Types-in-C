/* Interface file of Binary Search Tree (BST) ADT */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

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

// pointer to function printing bst's item
typedef void (*PrintFunc)(Pointer);

// pointer to bst
typedef struct binary_search_tree *BinarySearchTree;

/*-----Functions Provided-----*/

// initializes an empty bst
void bst_initialize(BinarySearchTree *, CompareFunc, DestroyFunc, PrintFunc);

// inserts a new item in the right place in the bst
void bst_insert(Pointer, BinarySearchTree);

// removes and destroys given item from the bst
void bst_remove(Pointer, BinarySearchTree);

// prints items of the bst 
void bst_print(BinarySearchTree);

// destroys the given bst by freeing all nodes
void bst_destroy(BinarySearchTree);

// returns the number of elements in the bst
int bst_size(BinarySearchTree);

// returns true/false depending on if bst is empty or not
bool bst_is_empty(BinarySearchTree);

// returns true/false based on if given item is found in the bst or not
bool bst_search(Pointer, BinarySearchTree);

// returns the root element of the bst
Pointer bst_root(BinarySearchTree);

// returns the element with lowest value
Pointer bst_min(BinarySearchTree);

// returns the element with highest value
Pointer bst_max(BinarySearchTree);

// sets as new CompareFunc of given bst the given one
void bst_set_compare(BinarySearchTree, CompareFunc);

// sets as new DestroyFunc of given bst the given one
void bst_set_destroy(BinarySearchTree, DestroyFunc);

// sets as new PrintFunc of given bst the given one
void bst_set_print(BinarySearchTree, PrintFunc);

#endif