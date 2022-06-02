#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BinarySearchTree.h"

// bst node struct
typedef struct bst_node{
    Pointer data; // pointer to the node data
    struct bst_node *left; // pointer to node's left child
    struct bst_node *right; // pointer to node's right child
}bst_node;

// bst struct
struct binary_search_tree{
    bst_node *root; // pointer to the root of the bst
    int size; // number of elements in the bst
    CompareFunc Compare;
    DestroyFunc Destroy;
    PrintFunc Print;
};

// bst-node functions

// creates a new bst node with NULL-children
static bst_node *new_bst_node(Pointer item)
{
    bst_node *new_node = malloc(sizeof(bst_node));
    assert(new_node);
    new_node->data = item;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// finds the bst node of given item
// returns NULL if not found
static bst_node *find_node(bst_node *root_node, Pointer item, CompareFunc compare)
{
    if (root_node != NULL){
        if (!compare(item, root_node->data)) return root_node; // found
        // search in root's subtrees
        bst_node *left = find_node(root_node->left, item, compare);
        if (left != NULL) return left;
        bst_node *right = find_node(root_node->right, item, compare);
        if (right != NULL) return right; 
    }
    // if not found return NULL
    return NULL;
}

// finds the parent bst node of given item
// returns NULL if not found
static bst_node *find_parent(bst_node *root, bst_node *node)
{
    if (root != NULL){
        // if any of the nodes children is item, parent node is found
        if (root->left == node || root->right == node) return root;
        // else search for parent in root's subtrees
        bst_node *left = find_parent(root->left, node);
        if (left != NULL) return left;
        bst_node *right = find_parent(root->right, node);
        if (right != NULL) return right;
    }
    // if not found return NULL
    return NULL;
}

// returns the in order successor of given bst node
static bst_node *in_order_successor(bst_node *node)
{
    if (node == NULL) return NULL;
    // traverse the right subtree of node, going to the left child until NULL is found
    bst_node *successor = node->right;
    while (successor->left != NULL) successor = successor->left;
    return successor;
}

// removes given node from bst and returns the new form of the tree
static bst_node *node_remove(bst_node *root, bst_node *node, DestroyFunc destroy)
{
    // find the parent node
    bst_node *parent = find_parent(root, node);
    // if node has two children
    if (node->left != NULL && node->right != NULL){
        // replace node's value with the successor's value and delete the successor node
        bst_node *successor = in_order_successor(node);
        // swap contents of node and its successor
        Pointer data = node->data;
        node->data = successor->data;
        successor->data = data;
        // successor will have either 0 or 1 child; therefore one of the next cases will apply for its removal
        node = successor;
        parent = find_parent(root, successor);
    }
    // if leaf node
    if (node->left == NULL && node->right == NULL){
        if (parent != NULL){ // if node isn't root
            if (parent->left == node) parent->left = NULL;
            else parent->right = NULL;
        }
        else root = NULL; // if root was removed
        if (destroy != NULL) destroy(node->data);
        free(node);
        return root;
    }
    // if node has one child
    bst_node *child = node->left != NULL ? node->left : node->right;
    if (parent != NULL){ // if node isn't root
        if (parent->left == node) parent->left = child;
        else parent->right = child;
    }
    else root = child; // if root was removed
    if (destroy != NULL) destroy(node->data);
    free(node);
    return root;
}

// prints given bst's nodes, based on given PrintFunc, traversing the tree in-order
static void print_tree_nodes(bst_node *node, PrintFunc print)
{
    if (node == NULL) return;
    print_tree_nodes(node->left, print);
    print(node->data);
    print_tree_nodes(node->right, print);
}

// destroys given bst 
static void destroy_nodes(bst_node *node, DestroyFunc destroy_func)
{
    if (node == NULL) return;
    destroy_nodes(node->left, destroy_func);
    destroy_nodes(node->right, destroy_func);
    if (destroy_func != NULL) destroy_func(node->data);
    free(node);
}

// Binary Search Tree (BST) ADT functions

// initializes an empty bst
void bst_initialize(BinarySearchTree *bst, CompareFunc compare_func, DestroyFunc destroy_func, PrintFunc print_func)
{
    *bst = malloc(sizeof(struct binary_search_tree));
    assert(*bst);
    (*bst)->root = NULL;
    (*bst)->size = 0;
    bst_set_compare(*bst, compare_func);
    bst_set_destroy(*bst, destroy_func);
    bst_set_print(*bst, print_func);
}

// inserts a new item in the right place in the bst
void bst_insert(Pointer item, BinarySearchTree bst)
{
    bst_node *new_node = new_bst_node(item);
    // check if tree is empty
    if (bst_is_empty(bst)){
        // insert the root
        bst->root = new_node;
        bst->size++;
        return;
    }
    // pointer parent has the parent of the new node
    bst_node *parent = NULL;
    bst_node *current = bst->root;
    // traverse the tree and find the right place to insert the new node
    while (current != NULL){
        parent = current;
        int comp_result = bst->Compare(new_node->data, current->data);
        if (!comp_result){
            // item already exists, no duplicates are allowed
            free(new_node);
            return;
        }
        else if (comp_result < 0) current = current->left; // go in left subtree
        else current = current->right; // go in right subtree
    }
    // find which child of parent is the new_node; connect to the bst
    if (bst->Compare(new_node->data, parent->data) < 0) parent->left = new_node;
    else parent->right = new_node;
    bst->size++;
}

// removes and destroys given item from the bst
void bst_remove(Pointer item, BinarySearchTree bst)
{
    if (bst_is_empty(bst)) return;
    bst_node *node = find_node(bst->root, item, bst->Compare);
    if (node == NULL) return;
    // remove node from bst and return bst's new form
    bst->root = node_remove(bst->root, node, bst->Destroy);
    bst->size--;
}

// prints items of the bst 
void bst_print(BinarySearchTree bst)
{
    if (bst->Print == NULL || bst_is_empty(bst)) return;
    // print bst
    print_tree_nodes(bst->root, bst->Print);
    printf("\n");
}

// destroys the given bst by freeing all nodes
void bst_destroy(BinarySearchTree bst)
{
    if (!bst_is_empty(bst)) destroy_nodes(bst->root, bst->Destroy);
    free(bst);
}

// returns the number of elements in the bst
int bst_size(BinarySearchTree bst)
{
    return bst->size;
}

// returns true/false depending on if bst is empty or not
bool bst_is_empty(BinarySearchTree bst)
{
    if (!bst_size(bst)) return true;
    else return false;
}

// returns true/false based on if given item is found in the bst or not
bool bst_search(Pointer item, BinarySearchTree bst)
{
    return find_node(bst->root, item, bst->Compare) != NULL ? true : false;
}

// returns the root element of the bst
Pointer bst_root(BinarySearchTree bst)
{
    return bst->root->data;
}

// returns the smallest/element with min key of the bst
Pointer bst_min(BinarySearchTree bst)
{
    if (bst_is_empty(bst)) return NULL;
    bst_node *min = bst->root;
    while (min->left != NULL) min = min->left;
    return min->data;
}

// returns the largest/element with max key of the bst
Pointer bst_max(BinarySearchTree bst)
{
    if (bst_is_empty(bst)) return NULL;
    bst_node *max = bst->root;
    while (max->right != NULL) max = max->right;
    return max->data;
}

// sets as new CompareFunc of given bst the given one
void bst_set_compare(BinarySearchTree bst, CompareFunc compare_func)
{
    bst->Compare = compare_func;
}

// sets as new DestroyFunc of given bst the given one
void bst_set_destroy(BinarySearchTree bst, DestroyFunc destroy_func)
{
    bst->Destroy = destroy_func;
}

// sets as new PrintFunc of given bst the given one
void bst_set_print(BinarySearchTree bst, PrintFunc print_func)
{
    bst->Print = print_func;
}