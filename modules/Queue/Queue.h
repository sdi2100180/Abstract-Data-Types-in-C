/* Interface file of Queue ADT */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// generic-pointer typedef
typedef void *Pointer;

// pointer to function that destroys given element
typedef void (*DestroyFunc)(Pointer);

// pointer to function printing queue's item
typedef void (*PrintFunc)(Pointer);

// pointer to queue
typedef struct queue *Queue;

/*-----Functions Provided-----*/

// initializes an empty queue
void queue_initialize(Queue *, DestroyFunc, PrintFunc);

// inserts a new item in queue
void queue_insert(Pointer, Queue);

// removes and returns the item at the front of the queue
// returns NULL if queue is empty
Pointer queue_remove(Queue);

// prints items of the queue
void queue_print(Queue);

// destroys the given queue by freeing all nodes
void queue_destroy(Queue);

// returns the number of elements in the queue
int queue_size(Queue);

// returns true/false depending on if queue is empty or not
bool queue_is_empty(Queue);

// returns the element at the front of the queue
Pointer queue_front(Queue);

// returns the element at the end of the queue
Pointer queue_rear(Queue);

// sets as new DestroyFunc of given queue the given one
void queue_set_destroy(Queue, DestroyFunc);

// sets as new PrintFunc of given queue the given one
void queue_set_print(Queue, PrintFunc);

#endif