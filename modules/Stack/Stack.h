/* Interface file of Stack ADT */

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// generic-pointer typedef
typedef void *Pointer;

// pointer to function that destroys given element
typedef void (*DestroyFunc)(Pointer);

// pointer to function printing stack's item
typedef void (*PrintFunc)(Pointer);

// pointer to stack
typedef struct stack_struct *Stack;

/*-----Functions Provided-----*/

// initializes an empty stack
void stack_initialize(Stack *, DestroyFunc, PrintFunc);

// pushes a new item on top of the stack
void stack_push(Pointer, Stack);

// pops the top item of the stack
// returns NULL if stack is empty
Pointer stack_pop(Stack);

// prints items of the stack
void stack_print(Stack);

// destroys the given stack by freeing all nodes
void stack_destroy(Stack);

// returns the number of elements in the stack
int stack_size(Stack);

// returns true/false depending on if stack is empty or not
bool stack_is_empty(Stack);

// returns the element at the top of the stack
// returns NULL if stack is empty
Pointer stack_top(Stack);

// sets as new DestroyFunc of given stack the given one
void stack_set_destroy(Stack, DestroyFunc);

// sets as new PrintFunc of given stack the given one
void stack_set_print(Stack, PrintFunc);

#endif