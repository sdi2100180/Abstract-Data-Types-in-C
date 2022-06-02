/* Interface file of Priority Queue ADT */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

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

// pointer to function printing priority queue's item
typedef void (*PrintFunc)(Pointer);

// pointer to priority queue
typedef struct priority_queue *PriorityQueue;

/*-----Functions Provided-----*/

// initializes an empty priority queue
void pq_initialize(PriorityQueue *, CompareFunc, DestroyFunc, PrintFunc);

// inserts a new item in priority queue
void pq_insert(Pointer, PriorityQueue);

// removes and returns the item with highest priority
// returns NULL if priority queue is empty
Pointer pq_remove(PriorityQueue);

// prints items of the priority queue
void pq_print(PriorityQueue);

// destroys the given priority queue by freeing all nodes
void pq_destroy(PriorityQueue);

// returns the number of elements in the priority queue
int pq_size(PriorityQueue);

// returns true/false depending on if priority queue is empty or not
bool pq_is_empty(PriorityQueue);

// sets as new CompareFunc of given priority queue the given one
void pq_set_compare(PriorityQueue, CompareFunc);

// sets as new DestroyFunc of given priority queue the given one
void pq_set_destroy(PriorityQueue, DestroyFunc);

// sets as new PrintFunc of given priority queue the given one
void pq_set_print(PriorityQueue, PrintFunc);

#endif