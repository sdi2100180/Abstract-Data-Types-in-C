#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "CircularList.h"

// circular list node struct
typedef struct cl_node{
    Pointer data; // pointer to the node data
    struct cl_node *next; // pointer to the next circular list node
}cl_node;

// circular list struct
struct circular_list{
    cl_node *cursor; // pointer to the cursor node of the circular list
    int size; // number of elements in the circular list
    DestroyFunc Destroy;
    PrintFunc Print;
};

// Circular List ADT functions

// initializes an empty circular list
void cl_initialize(CircularList *cl, DestroyFunc destroy_func, PrintFunc print_func)
{
    *cl = malloc(sizeof(struct circular_list));
    assert(*cl);
    (*cl)->cursor = NULL;
    (*cl)->size = 0;
    cl_set_destroy(*cl, destroy_func);
    cl_set_print(*cl, print_func);
}

// adds a new node to the circular list, right after the cursor or the cursor if cl was empty
void cl_insert(Pointer item, CircularList cl)
{
    cl_node *new_node = malloc(sizeof(cl_node));
    assert(new_node);
    new_node->data = item;
    // check if list is empty; insert the cursor
    if (cl_is_empty(cl)){
        new_node->next = new_node;
        cl->cursor = new_node;
        cl->size++;
        return;
    }
    // else; insert right after the cursor
    new_node->next = cl->cursor->next;
    cl->cursor->next = new_node;
    cl->size++;
}

// removes and returns the node after the cursor 
// or the cursor itself, if the list has only the cursor
Pointer cl_remove(CircularList cl)
{
    // check if list is empty
    if (cl_is_empty(cl)) return NULL;
    Pointer item;
    // check if cl has only the cursor node; remove the cursor
    if (cl_size(cl) == 1){
        item = cl->cursor->data;
        free(cl->cursor);
        cl->size--;
        return item;
    }
    // else; remove the node after the cursor
    item = cl->cursor->next->data;
    cl_node *new_cursor_next = cl->cursor->next->next;
    free(cl->cursor->next);
    cl->size--;
    cl->cursor->next = new_cursor_next;
    return item;
}

// prints items of the circular list based on given PrintFunc
void cl_print(CircularList cl)
{
    // check if a PrintFunc exists and if circular list isn't empty
    if (cl->Print == NULL || cl_is_empty(cl)) return;
    // else; print circular list's elements 
    cl_node *node = cl->cursor;
    do{
        cl->Print(node->data);
        node = node->next;
    }while (node != cl->cursor);
    printf("\n");
}

// destroys the given circular list
void cl_destroy(CircularList cl)
{
    // check if circular list is empty
    if (cl_is_empty(cl)){
        free(cl);
        return;
    }
    // else; destroy circular list's elements 
    cl_node *node = cl->cursor->next;
    while (!cl_is_empty(cl)){
        if (cl->Destroy != NULL) cl->Destroy(cl->cursor->data);
        free(cl->cursor);
        cl->cursor = node;
        if (node != NULL) node = node->next;
        cl->size--;
    }
    free(cl);
}

// returns the number of elements in the circular list
int cl_size(CircularList cl)
{
    return cl->size;
}

// returns true/false depending on if circular list is empty or not
bool cl_is_empty(CircularList cl)
{
    if (!cl_size(cl)) return true;
    else return false;
}

// advances the cursor of the circular list to the next node
void cl_advance_cursor(CircularList cl)
{
    cl->cursor = cl->cursor->next;
}

// returns the cursor of given circular list or NULL if cl is empty
Pointer cl_cursor(CircularList cl)
{
    if (cl_is_empty(cl)) return NULL;
    else return cl->cursor->data;
}

// sets as new DestroyFunc of given circular list the given one
void cl_set_destroy(CircularList cl, DestroyFunc destroy_func)
{
    cl->Destroy = destroy_func;
}

// sets as new PrintFunc of given circular list the given one
void cl_set_print(CircularList cl, PrintFunc print_func)
{
    cl->Print = print_func;
}