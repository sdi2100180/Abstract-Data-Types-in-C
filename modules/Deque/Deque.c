#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Deque.h"

// deque node struct
typedef struct deque_node{
    Pointer data; // pointer to the node data
    struct deque_node *next; // pointer to the next deque node
}deque_node;

// deque struct
struct deque{
    deque_node *front; // pointer to the first/front deque element
    deque_node *rear; // pointer to the last/rear deque element
    int size; // number of elements in the deque
    DestroyFunc Destroy;
    PrintFunc Print;
};

// returns a new deque node with given item as data
static deque_node *new_deque_node(Pointer item)
{
    deque_node *new_node = malloc(sizeof(deque_node));
    assert(new_node);
    new_node->data = item;
    new_node->next = NULL;
    return new_node;
}

// inserts the first node in a deque
static void insert_first_node(deque_node *new_node, Deque dq)
{
    dq->front = new_node;
    dq->rear = new_node;
    dq->size++;
}

// Deque ADT functions

// initializes an empty deque
void deque_initialize(Deque *dq, DestroyFunc destroy_func, PrintFunc print_func)
{
    *dq = malloc(sizeof(struct deque));
    assert(*dq);
    (*dq)->front = NULL;
    (*dq)->rear = NULL;
    (*dq)->size = 0;
    deque_set_destroy(*dq, destroy_func);
    deque_set_print(*dq, print_func);
}

// inserts a new item at the back/end of the deque
void deque_insert_back(Pointer item, Deque dq)
{
    deque_node *new_node = new_deque_node(item);
    // check if deque is empty
    if (deque_is_empty(dq)){
        insert_first_node(new_node, dq);
        return;
    }
    dq->rear->next = new_node;
    dq->rear = new_node;
    dq->size++;
}

// inserts a new item at the front/start of the deque
void deque_insert_front(Pointer item, Deque dq)
{
    deque_node *new_node = new_deque_node(item);
    // check if deque is empty
    if (deque_is_empty(dq)){
        insert_first_node(new_node, dq);
        return;
    }
    new_node->next = dq->front;
    dq->front = new_node;
    dq->size++;
}

// removes and returns the item from the back of the deque
// returns NULL if deque is empty
Pointer deque_remove_back(Deque dq)
{
    // check if deque is empty
    if (deque_is_empty(dq)) return NULL;
    // check if deque has only one element; remove front
    if (dq->front == dq->rear) return deque_remove_front(dq);
    // else; remove the back element of the deque
    Pointer item = dq->rear->data;
    deque_node *new_rear = dq->front;
    while(new_rear->next != dq->rear){
        new_rear = new_rear->next;
    }
    free(dq->rear);
    dq->size--;
    dq->rear = new_rear;
    new_rear->next = NULL;
    return item;
}

// removes and returns the item from the start of the deque
// returns NULL if deque is empty
Pointer deque_remove_front(Deque dq)
{
    // check if deque is empty
    if (deque_is_empty(dq)) return NULL;
    // else; remove the front element of the deque
    Pointer item = dq->front->data;
    deque_node *new_front = dq->front->next;
    free(dq->front);
    dq->size--;
    dq->front = new_front;
    return item;
}

// prints items of the deque based on given PrintFunc
void deque_print(Deque dq)
{
    // check if a PrintFunc exists and if deque isn't empty
    if (dq->Print == NULL || deque_is_empty(dq)) return;
    // else; print pq's elements 
    deque_node *node = dq->front;
    while (node != NULL){
        dq->Print(node->data);
        node = node->next;
    }
    printf("\n");
}

// destroys the given deque
void deque_destroy(Deque dq)
{
    // check if deque is empty
    if (deque_is_empty(dq)){
        free(dq);
        return;
    }
    // else; destroy pq's elements 
    deque_node *node = dq->front->next;
    while (!deque_is_empty(dq)){
        if (dq->Destroy != NULL) dq->Destroy(dq->front->data);
        free(dq->front);
        dq->front = node;
        if (node != NULL) node = node->next;
        dq->size--;
    }
    free(dq);
}

// returns the number of elements in the deque
int deque_size(Deque dq)
{
    return dq->size;
}

// returns true/false depending on if deque is empty or not
bool deque_is_empty(Deque dq)
{
    if (!deque_size(dq)) return true;
    else return false;
}

// returns the front element of the deque
// retutns NULL if deque is empty
Pointer deque_front(Deque dq)
{
    if (deque_is_empty(dq)) return NULL;
    return dq->front->data;
}

// returns the rear element of the deque
// retutns NULL if deque is empty
Pointer deque_rear(Deque dq)
{
    if (deque_is_empty(dq)) return NULL;
    return dq->rear->data;
}

// sets as new DestroyFunc of given deque the given one
void deque_set_destroy(Deque dq, DestroyFunc destroy_func)
{
    dq->Destroy = destroy_func;
}

// sets as new PrintFunc of given deque the given one
void deque_set_print(Deque dq, PrintFunc print_func)
{
    dq->Print = print_func;
}