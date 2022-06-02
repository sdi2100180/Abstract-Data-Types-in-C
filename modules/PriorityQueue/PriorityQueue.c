#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "PriorityQueue.h"

// priority queue node struct
typedef struct pq_node{
    Pointer data; // pointer to the node data
    struct pq_node *next; // pointer to the next priority queue node
}pq_node;

// priority queue struct
struct priority_queue{
    pq_node *head; // pointer to the first element in the priority queue
    int size; // number of elements in the priority queue
    CompareFunc Compare;
    DestroyFunc Destroy;
    PrintFunc Print;
};

// Priority Queue ADT functions

// initializes an empty priority queue
void pq_initialize(PriorityQueue *pq, CompareFunc compare_func, DestroyFunc destroy_func, PrintFunc print_func)
{
    *pq = malloc(sizeof(struct priority_queue));
    assert(*pq);
    (*pq)->head = NULL;
    (*pq)->size = 0;
    pq_set_compare(*pq, compare_func);
    pq_set_destroy(*pq, destroy_func);
    pq_set_print(*pq, print_func);
}

// inserts a new item in the priority queue, based on its priority
void pq_insert(Pointer item, PriorityQueue pq)
{
    // if a CompareFunc doesn't exist; return
    if (pq->Compare == NULL) return;

    pq_node *new_node = malloc(sizeof(pq_node));
    assert(new_node);
    new_node->data = item;
    // check if item should be inserted at the start of the pq
    if (pq_is_empty(pq) || pq->Compare(new_node->data, pq->head->data) <= 0){
        new_node->next = pq->head;
        pq->head = new_node;
        pq->size++;
        return;
    }
    // else; find where new_node should be placed
    pq_node *temp = pq->head;
    while(temp->next != NULL && pq->Compare(new_node->data, temp->next->data) > 0){
        temp = temp->next;
    }
    new_node->next = temp->next;
    temp->next = new_node;
    pq->size++;
}

// removes and returns the item with highest priority from the priority queue
// returns NULL if priority queue is empty
Pointer pq_remove(PriorityQueue pq)
{
    // check if pq is empty
    if (pq_is_empty(pq)) return NULL;
    // else; remove the item with highest priority
    Pointer item = pq->head->data;
    pq_node *new_head = pq->head->next;
    free(pq->head);
    pq->size--;
    pq->head = new_head;
    return item;
}

// prints items of the priority queue based on given PrintFunc
void pq_print(PriorityQueue pq)
{
    // check if a PrintFunc exists and pq isn't empty
    if (pq->Print == NULL || pq_is_empty(pq)) return;
    // else; print pq's elements 
    pq_node *node = pq->head;
    while (node != NULL){
        pq->Print(node->data);
        node = node->next;
    }
    printf("\n");
}

// destroys the given priority queue
void pq_destroy(PriorityQueue pq)
{
    // check if pq is empty
    if (pq_is_empty(pq)){
        free(pq);
        return;
    }
    // else; destroy pq's elements 
    pq_node *node = pq->head->next;
    while (!pq_is_empty(pq)){
        if (pq->Destroy != NULL) pq->Destroy(pq->head->data);
        free(pq->head);
        pq->head = node;
        if (node != NULL) node = node->next;
        pq->size--;
    }
    free(pq);
}

// returns the number of elements in the priority queue
int pq_size(PriorityQueue pq)
{
    return pq->size;
}

// returns true/false depending on if priority queue is empty or not
bool pq_is_empty(PriorityQueue pq)
{
    if (!pq_size(pq)) return true;
    else return false;
}

// sets as new CompareFunc of given priority the given one
void pq_set_compare(PriorityQueue pq, CompareFunc compare_func)
{
    pq->Compare = compare_func;
}

// sets as new DestroyFunc of given priority queue the given one
void pq_set_destroy(PriorityQueue pq, DestroyFunc destroy_func)
{
    pq->Destroy = destroy_func;
}

// sets as new PrintFunc of given priority queue the given one
void pq_set_print(PriorityQueue pq, PrintFunc print_func)
{
    pq->Print = print_func;
}