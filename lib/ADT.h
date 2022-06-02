/* Interface file of the ADT library */

#ifndef ADT_LIB_H
#define ADT_LIB_H

#include <stdbool.h>

// Generic typedefs used in all modules

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

////////////////////////////////////////////////////////////////////

// Pointers to modules' structs
typedef struct stack_struct *Stack;
typedef struct queue *Queue;
typedef struct deque *Deque;
typedef struct priority_queue *PriorityQueue;
typedef struct circular_list *CircularList;
typedef struct binary_search_tree *BinarySearchTree;
typedef struct red_black_tree *RedBlackTree;

////////////////////////////////////////////////////////////////////

// Function prototypes for each module

// Stack
void stack_initialize(Stack *, DestroyFunc, PrintFunc);
void stack_push(Pointer, Stack);
Pointer stack_pop(Stack);
void stack_print(Stack);
void stack_destroy(Stack);
int stack_size(Stack);
bool stack_is_empty(Stack);
Pointer stack_top(Stack);
void stack_set_destroy(Stack, DestroyFunc);
void stack_set_print(Stack, PrintFunc);

// Queue
void queue_initialize(Queue *, DestroyFunc, PrintFunc);
void queue_insert(Pointer, Queue);
Pointer queue_remove(Queue);
void queue_print(Queue);
void queue_destroy(Queue);
int queue_size(Queue);
bool queue_is_empty(Queue);
Pointer queue_front(Queue);
Pointer queue_rear(Queue);
void queue_set_destroy(Queue, DestroyFunc);
void queue_set_print(Queue, PrintFunc);

// Deque
void deque_initialize(Deque *, DestroyFunc, PrintFunc);
void deque_insert_back(Pointer, Deque);
void deque_insert_front(Pointer, Deque);
Pointer deque_remove_back(Deque);
Pointer deque_remove_front(Deque);
void deque_print(Deque);
void deque_destroy(Deque);
int deque_size(Deque);
bool deque_is_empty(Deque);
Pointer deque_front(Deque);
Pointer deque_rear(Deque);
void deque_set_destroy(Deque, DestroyFunc);
void deque_set_print(Deque, PrintFunc);

// Priority Queue
void pq_initialize(PriorityQueue *, CompareFunc, DestroyFunc, PrintFunc);
void pq_insert(Pointer, PriorityQueue);
Pointer pq_remove(PriorityQueue);
void pq_print(PriorityQueue);
void pq_destroy(PriorityQueue);
int pq_size(PriorityQueue);
bool pq_is_empty(PriorityQueue);
void pq_set_compare(PriorityQueue, CompareFunc);
void pq_set_destroy(PriorityQueue, DestroyFunc);
void pq_set_print(PriorityQueue, PrintFunc);

// Circular List
void cl_initialize(CircularList *, DestroyFunc, PrintFunc);
void cl_insert(Pointer, CircularList);
Pointer cl_remove(CircularList);
void cl_print(CircularList);
void cl_destroy(CircularList);
int cl_size(CircularList);
bool cl_is_empty(CircularList);
void cl_advance_cursor(CircularList);
Pointer cl_cursor(CircularList);
void cl_set_destroy(CircularList, DestroyFunc);
void cl_set_print(CircularList, PrintFunc);

// Binary Search Tree
void bst_initialize(BinarySearchTree *, CompareFunc, DestroyFunc, PrintFunc);
void bst_insert(Pointer, BinarySearchTree);
void bst_remove(Pointer, BinarySearchTree);
void bst_print(BinarySearchTree);
void bst_destroy(BinarySearchTree);
int bst_size(BinarySearchTree);
bool bst_is_empty(BinarySearchTree);
bool bst_search(Pointer, BinarySearchTree);
Pointer bst_root(BinarySearchTree);
Pointer bst_min(BinarySearchTree);
Pointer bst_max(BinarySearchTree);
void bst_set_compare(BinarySearchTree, CompareFunc);
void bst_set_destroy(BinarySearchTree, DestroyFunc);
void bst_set_print(BinarySearchTree, PrintFunc);

// Red Black Tree
void red_black_initialize(RedBlackTree *, CompareFunc, DestroyFunc, PrintFunc);
void red_black_insert(Pointer, RedBlackTree);
void red_black_remove(Pointer, RedBlackTree);
void red_black_print(RedBlackTree);
void red_black_destroy(RedBlackTree);
int red_black_size(RedBlackTree);
bool red_black_is_empty(RedBlackTree);
bool red_black_search(Pointer, RedBlackTree);
Pointer red_black_root(RedBlackTree);
Pointer red_black_min(RedBlackTree);
Pointer red_black_max(RedBlackTree);
void red_black_set_compare(RedBlackTree, CompareFunc);
void red_black_set_destroy(RedBlackTree, DestroyFunc);
void red_black_set_print(RedBlackTree, PrintFunc);

#endif