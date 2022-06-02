/* Interface file of Deque ADT */

#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>

// generic-pointer typedef
typedef void *Pointer;

// pointer to function that destroys given element
typedef void (*DestroyFunc)(Pointer);

// pointer to function printing deque's item
typedef void (*PrintFunc)(Pointer);

// pointer to deque
typedef struct deque *Deque;

/*-----Functions Provided-----*/

// initializes an empty deque
void deque_initialize(Deque *, DestroyFunc, PrintFunc);

// inserts a new item at the back/end of the deque
void deque_insert_back(Pointer, Deque);

// inserts a new item at the front/start of the deque
void deque_insert_front(Pointer, Deque);

// removes and returns the item from the back of the deque
// returns NULL if deque is empty
Pointer deque_remove_back(Deque);

// removes and returns the item from the front of the deque
// returns NULL if deque is empty
Pointer deque_remove_front(Deque);

// prints items of the deque
void deque_print(Deque);

// destroys the given deque by freeing all nodes
void deque_destroy(Deque);

// returns the number of elements in the deque
int deque_size(Deque);

// returns true/false depending on if deque is empty or not
bool deque_is_empty(Deque);

// returns the element at the front of the deque
Pointer deque_front(Deque);

// returns the element at the end of the deque
Pointer deque_rear(Deque);

// sets as new DestroyFunc of given deque the given one
void deque_set_destroy(Deque, DestroyFunc);

// sets as new PrintFunc of given deque the given one
void deque_set_print(Deque, PrintFunc);

#endif