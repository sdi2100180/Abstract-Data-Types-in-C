#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Queue.h"

// queue node struct
typedef struct queue_node{
    Pointer data; // pointer to the node data
    struct queue_node *next; // pointer to the next queue node
}queue_node;

// queue struct
struct queue{
    queue_node *front; // pointer to the first/front queue element
    queue_node *rear; // pointer to the last/rear queue element
    int size; // number of elements in the queue
    DestroyFunc Destroy;
    PrintFunc Print;
};

// Queue ADT functions

// initializes an empty queue
void queue_initialize(Queue *q, DestroyFunc destroy_func, PrintFunc print_func)
{
    *q = malloc(sizeof(struct queue));
    assert(*q);
    (*q)->front = NULL;
    (*q)->rear = NULL;
    (*q)->size = 0;
    queue_set_destroy(*q, destroy_func);
    queue_set_print(*q, print_func);
}

// inserts a new item at the end of the queue
void queue_insert(Pointer item, Queue q)
{
    queue_node *new_node = malloc(sizeof(queue_node));
    assert(new_node);
    new_node->data = item;
    new_node->next = NULL;
    // check if queue is empty
    if (queue_is_empty(q)){
        q->front = new_node;
        q->rear = new_node;
        q->size++;
        return;
    }
    q->rear->next = new_node;
    q->rear = new_node;
    q->size++;
}

// removes and returns the item from the start of the queue
// returns NULL if queue is empty
Pointer queue_remove(Queue q)
{
    // check if queue is empty
    if (queue_is_empty(q)) return NULL;
    // else; remove the front element of the queue
    Pointer item = q->front->data;
    queue_node *new_front = q->front->next;
    free(q->front);
    q->size--;
    q->front = new_front;
    return item;
}

// prints items of the queue based on given PrintFunc
void queue_print(Queue q)
{
    // check if a PrintFunc exists and if queue isn't empty
    if (q->Print == NULL || queue_is_empty(q)) return;
    // else; print pq's elements 
    queue_node *node = q->front;
    while (node != NULL){
        q->Print(node->data);
        node = node->next;
    }
    printf("\n");
}

// destroys the given queue
void queue_destroy(Queue q)
{
    // check if queue is empty
    if (queue_is_empty(q)){
        free(q);
        return;
    }
    // else; destroy pq's elements 
    queue_node *node = q->front->next;
    while (!queue_is_empty(q)){
        if (q->Destroy != NULL) q->Destroy(q->front->data);
        free(q->front);
        q->front = node;
        if (node != NULL) node = node->next;
        q->size--;
    }
    free(q);
}

// returns the number of elements in the queue
int queue_size(Queue q)
{
    return q->size;
}

// returns true/false depending on if queue is empty or not
bool queue_is_empty(Queue q)
{
    if (!queue_size(q)) return true;
    else return false;
}

// returns the front element of the queue
// retutns NULL if queue is empty
Pointer queue_front(Queue q)
{
    if (queue_is_empty(q)) return NULL;
    return q->front->data;
}

// returns the rear element of the queue
// retutns NULL if queue is empty
Pointer queue_rear(Queue q)
{
    if (queue_is_empty(q)) return NULL;
    return q->rear->data;
}

// sets as new DestroyFunc of given queue the given one
void queue_set_destroy(Queue q, DestroyFunc destroy_func)
{
    q->Destroy = destroy_func;
}

// sets as new PrintFunc of given queue the given one
void queue_set_print(Queue q, PrintFunc print_func)
{
    q->Print = print_func;
}