/* Interface file of Circular List ADT */

#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <stdbool.h>

// generic-pointer typedef
typedef void *Pointer;

// pointer to function that destroys given element
typedef void (*DestroyFunc)(Pointer);

// pointer to function printing circular list's item
typedef void (*PrintFunc)(Pointer);

// pointer to circular list
typedef struct circular_list *CircularList;

/*-----Functions Provided-----*/

// initializes an empty circular list
void cl_initialize(CircularList *, DestroyFunc, PrintFunc);

// inserts a new item in the cl right after the cursor or the cursor if the list was empty
void cl_insert(Pointer, CircularList);

// removes and returns the item right after the cursor or the cursor if it was its only node
// returns NULL if circular list is empty
Pointer cl_remove(CircularList);

// prints items of the circular list
void cl_print(CircularList);

// destroys the given circular list by freeing all nodes
void cl_destroy(CircularList);

// returns the number of elements in the circular list
int cl_size(CircularList);

// returns true/false depending on if circular list is empty or not
bool cl_is_empty(CircularList);

// advances the cursor to the next node
void cl_advance_cursor(CircularList);

// returns the cursor of given circular list or NULL if cl is empty
Pointer cl_cursor(CircularList);

// sets as new DestroyFunc of given circular list the given one
void cl_set_destroy(CircularList, DestroyFunc);

// sets as new PrintFunc of given circular list the given one
void cl_set_print(CircularList, PrintFunc);

#endif