#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Stack.h"

// stack node struct
typedef struct stack_node{
    Pointer data; // pointer to the node data
    struct stack_node *next; // pointer to the next stack node
}stack_node;

// stack struct
struct stack_struct{
    stack_node *top; // pointer to the top node of the stack
    int size; // number of elements in the stack
    DestroyFunc Destroy;
    PrintFunc Print;
};

// Stack ADT functions

// initializes an empty stack
void stack_initialize(Stack *stack, DestroyFunc destroy_func, PrintFunc print_func)
{
    (*stack) = malloc(sizeof(struct stack_struct));
    assert(*stack);
    (*stack)->top = NULL;
    (*stack)->size = 0;
    stack_set_destroy(*stack, destroy_func);
    stack_set_print(*stack, print_func);
}

// pushes a new item on top of the stack
void stack_push(Pointer item, Stack stack)
{ 
    stack_node *new_node = malloc(sizeof(stack_node));
    assert(new_node);
    stack->size++;
    new_node->data = item;
    new_node->next = stack->top;
    stack->top = new_node;
}

// pops the top item of the stack and returns a pointer to it
// returns NULL if stack is empty
Pointer stack_pop(Stack stack)
{
    // check if stack is empty
    if (stack_is_empty(stack)) return NULL;
    // else; pop the top element
    Pointer item = stack->top->data;
    stack_node *new_top = stack->top->next;
    free(stack->top);
    stack->size--;
    stack->top = new_top;
    return item;
}

// prints items of the stack based on given PrintFunc
void stack_print(Stack stack)
{
    // check if a PrintFunc exists and if stack isn't empty
    if (stack->Print == NULL || stack_is_empty(stack)) return;
    // else; print stack's elements 
    stack_node *node = stack->top;
    while (node != NULL){
        stack->Print(node->data);
        node = node->next;
    }
    printf("\n");
}

// destroys the given stack
void stack_destroy(Stack stack)
{
    // check if stack is empty
    if (stack_is_empty(stack)){
        free(stack);
        return;
    }
    // else; destroy stack's elements 
    stack_node *node = stack->top->next;
    while (!stack_is_empty(stack)){
        if (stack->Destroy != NULL) stack->Destroy(stack->top->data);
        free(stack->top);
        stack->top = node;
        if (node != NULL) node = node->next;
        stack->size--;
    }
    free(stack);
}

// returns the number of elements in the stack
int stack_size(Stack stack)
{
    return stack->size;
}

// returns true/false depending on if stack is empty or not
bool stack_is_empty(Stack stack)
{
    if (!stack_size(stack)) return true;
    else return false;
}

// returns the element at the top of the stack
// returns NULL if stack is empty
Pointer stack_top(Stack stack)
{
    if (stack_is_empty(stack)) return NULL;
    return stack->top->data;
}

// sets as new DestroyFunc of given stack the given one
void stack_set_destroy(Stack stack, DestroyFunc destroy_func)
{
    stack->Destroy = destroy_func;
}

// sets as new PrintFunc of given stack the given one
void stack_set_print(Stack stack, PrintFunc print_func)
{
    stack->Print = print_func;
}