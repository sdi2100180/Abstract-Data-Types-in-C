#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "RedBlackTree.h"

// node color enum
typedef enum{
    RED, BLACK
}Color;

// red black tree node struct
typedef struct rbt_node{
    Pointer data; // pointer to the node data
    Color color; // node's color
    struct rbt_node *left, *right; // pointers to node's left and right children
    struct rbt_node *parent; // pointer to node's parent-node
}rbt_node;

// red black tree struct
struct red_black_tree{
    rbt_node *root; // pointer to the root of the rbt
    int size; // number of elements in the rbt
    CompareFunc Compare;
    DestroyFunc Destroy;
    PrintFunc Print;
};

// dummy node used to keep the tree extended
static rbt_node z = {NULL, BLACK, NULL, NULL, NULL};
static rbt_node *NULLnode = &z;

// rbt-node functions

// creates a new rbt node with given arguments
static rbt_node *create_node(Pointer item, rbt_node *l, rbt_node *r, rbt_node *p)
{
    rbt_node *node = malloc(sizeof(rbt_node));
    assert(node);
    node->data = item;
    node->color = RED;
    node->left = l;
    node->right = r;
    node->parent = p;
    return node;
}

// finds the rbt node of given item
// returns NULLnode if not found
static rbt_node *find_node(rbt_node *root_node, Pointer item, CompareFunc compare)
{
    if (root_node == NULLnode) return NULLnode;
    int comp_result = compare(item, root_node->data);
    if (!comp_result) return root_node; // found
    // search in the appropriate root's subtree
    if (comp_result < 0) return find_node(root_node->left, item, compare);
    else return find_node(root_node->right, item, compare);
}

// returns sibling of given node
// returns NULLnode if non-existent
static rbt_node *find_sibling(rbt_node *node)
{
    rbt_node *parent = node->parent;
    // check if root
    if (parent == NULLnode) return NULLnode;
    return parent->left == node ? parent->right : parent->left;
}

// performs right rotation at head
static rbt_node *right_rotation(rbt_node *head)
{
    rbt_node *node = head->left;
    // need to update x->right's parent; after the rotation its parent will become head
    node->right->parent = head;
    head->left = node->right;
    node->right = head;
    return node;
}

// performs left rotation at head
static rbt_node *left_rotation(rbt_node *head)
{
    rbt_node *node = head->right;
    // need to update x->left's parent; after the rotation its parent will become head
    node->left->parent = head;
    head->right = node->left;
    node->left = head;
    return node;
}

// double left-right rotation
static rbt_node *left_right_rotation(rbt_node *head)
{
    // left rotation at head->left and then right rotation at head
    head->left = left_rotation(head->left);
    return right_rotation(head);
}

// double right-left rotation
static rbt_node *right_left_rotation(rbt_node *head)
{
    // right rotation at head->right and then left rotation at head
    head->right = right_rotation(head->right);
    return left_rotation(head);
}

// performs a simple trinode-restructuring algorithm
// used to solve double-red and double-black problems
static rbt_node *trinode_restructuring(rbt_node *root_node, rbt_node *z, CompareFunc compare, int problem)
{
    // z = node/child, v = parent of z, u = grandparent of z
    rbt_node *v = z->parent;
    rbt_node *u = z->parent->parent;

    // determine a, b, c; a,b,c are u,v,z in ascending order
    rbt_node *a, *b, *c;
    if (compare(z->data, v->data) < 0 && compare(z->data, u->data) < 0){
        a = z;
        if (compare(v->data, u->data) < 0) c = u;
        else c = v;
    }
    else if (compare(v->data, z->data) < 0 && compare(v->data, u->data) < 0){
        a = v;
        if (compare(z->data, u->data) < 0) c = u;
        else c = z;
    }
    else{
        a = u;
        if (compare(z->data, v->data) < 0) c = v;
        else c = z;
    }

    // create a new trinode-tree using a,b,c using rotations; restructure
    // determine the type of needed rotation(s), and make b the new "grandparent" node
    if (u->left == v && v->left == z) b = right_rotation(u);
    else if (u->right == v && v->right == z) b = left_rotation(u);
    else if (u->left == v && v->right == z) b = left_right_rotation(u);
    else b = right_left_rotation(u);

    // a will be the left child of b and c the right one
    // connect a and c with b
    b->left = a;
    b->right = c;

    // fix colors based on if double-red or double-black problem is present
    if (problem == 0){
        // double red problem
        // b will become black, a and c will become red
        b->color = BLACK;
        a->color = RED;
        c->color = RED;
    }else{
        // double black problem
        // b's color will be u's color
        b->color = u->color;
        // a and c will become black
        a->color = BLACK;
        c->color = BLACK;
    }

    // connect the new subtree a-b-c with root

    // if the root was restructured, make root = b
    if (root_node->data == u->data){
        b->parent = root_node->parent;
        root_node = b;
    }else{
        // else, connect new a-b-c subtree with "big" tree; connect u's parent with b
        if (u->parent->left == u) u->parent->left = b;
        else u->parent->right = b;
        b->parent = u->parent;
    }
    // connect parent pointers of a and c with b
    a->parent = b;
    c->parent = b;

    // return the new tree
    return root_node;
}

// returns the in order successor of given rbt node
static rbt_node *in_order_successor(rbt_node *node)
{
    if (node == NULLnode) return NULLnode;
    // traverse the right subtree of node, going to the left child until NULLnode is found
    rbt_node *successor = node->right;
    while (successor->left != NULLnode) successor = successor->left;
    return successor;
}

// removes given node from rbt and returns the new form of the tree
// basic bst-deletion
static rbt_node *node_remove(rbt_node *root, rbt_node *node, DestroyFunc destroy)
{
    // find the parent node
    rbt_node *parent = node->parent;
    // if node has two children
    if (node->left != NULLnode && node->right != NULLnode){
        // replace node's value with the successor's value and delete the successor node
        rbt_node *successor = in_order_successor(node);
        // swap contents of node and its successor
        Pointer data = node->data;
        node->data = successor->data;
        successor->data = data;
        // successor will have either 0 or 1 child; therefore one of the next cases will apply for its removal
        node = successor;
        parent = successor->parent;
    }
    // if leaf node
    if (node->left == NULLnode && node->right == NULLnode){
        if (parent != NULLnode){ // if node isn't root
            if (parent->left == node) parent->left = NULLnode;
            else parent->right = NULLnode;
        }
        else root = NULLnode; // if root was removed
        if (destroy != NULL) destroy(node->data);
        free(node);
        return root;
    }
    // if node has one child
    rbt_node *child = node->left != NULLnode ? node->left : node->right;
    if (parent != NULLnode){ // if node isn't root
        if (parent->left == node) parent->left = child;
        else parent->right = child;
    }
    else root = child; // if root was removed
    child->color = node->color;
    child->parent = node->parent;
    if (destroy != NULL) destroy(node->data);
    free(node);
    return root;
}

// adjustment operation, perfomed in deletion of node if double black sibling is red
static rbt_node *adjustment(rbt_node *head, rbt_node *y, CompareFunc compare)
{
    // y is double black node's sibling, x is y's parent, z is y's chosen child used for the restructure
    rbt_node *x = y->parent, *z;
    if (x->right == y) z = y->right;
    else z = y->left;
    // perform the appropriate adjustment using trinode-restructuring
    head = trinode_restructuring(head, z, compare, 1);
    // color y black and x red
    y->color = BLACK;
    x->color = RED;
    // return new tree
    return head;
}

// fixes the double-black problem, given the head of the tree and double black node's sibling
static rbt_node *fix_double_black(rbt_node *head, rbt_node *sibling, CompareFunc compare)
{
    // base case
    if (sibling == NULLnode) return head;

    // case 1: sibling color is red
    if (sibling->color == RED){
        // perform an adjustment operation and after that one of the next cases will apply
        // and the double-black problem will be resolved
        // store the double black node's new sibling
        rbt_node *new_sibling;
        // since the adjustment operation will perform a single left or right rotation
        // based on which rotation will take place, either sibling's right or left will be
        // the new sibling of the double black node
        if (sibling->parent->left == sibling) new_sibling = sibling->right;
        else new_sibling = sibling->left;
        // perform the adjustment
        head = adjustment(head, sibling, compare); 
        // assign to sibling the new_sibling, and apply one of the next cases
        sibling = new_sibling;
    }

    // case 2: sibling is black and has one red child
    if (sibling->color == BLACK){
        // perform trinode restructuring to resolve the depth property and fix colors
        if (sibling->left->color == RED){
            head = trinode_restructuring(head, sibling->left, compare, 1);
            return head;
        }else if (sibling->right->color == RED){
            head = trinode_restructuring(head, sibling->right, compare, 1);
            return head;
        }
    }

    // case 3: sibling is black and both its children are black
    if (sibling->color == BLACK && sibling->left->color == BLACK && sibling->right->color == BLACK){
        // perform recoloring
        sibling->color = RED;
        // check parent's color
        if (sibling->parent->color == RED){
            sibling->parent->color = BLACK;
        }else{
            // double black appeared at the parent
            head = fix_double_black(head, find_sibling(sibling->parent), compare);
        }
    }
    return head;
}

// prints given rbt's nodes, based on given PrintFunc, traversing the tree in-order
static void print_tree_nodes(rbt_node *node, PrintFunc print)
{
    if (node == NULLnode) return;
    print_tree_nodes(node->left, print);
    print(node->data);
    print_tree_nodes(node->right, print);
}

// performs recoloring operation, fixing the double-red problem
static rbt_node *recoloring(rbt_node *root_node, rbt_node *v)
{
    // v = parent, w = sibling of parent, u = grandparent
    rbt_node *w = find_sibling(v);
    rbt_node *u = v->parent;
    // recolor
    u->color = RED;
    v->color = BLACK;
    w->color = BLACK;
    return root_node;
}

// destroys given rbt nodes
static void destroy_nodes(rbt_node *node, DestroyFunc destroy_func)
{
    if (node == NULLnode) return;
    destroy_nodes(node->left, destroy_func);
    destroy_nodes(node->right, destroy_func);
    if (destroy_func != NULL) destroy_func(node->data);
    free(node);
}

// returns the node that will replace the node to be removed from a red-black tree
static rbt_node *find_replacement(rbt_node *node_rm)
{
    // if node is a leaf
    if (node_rm->left == NULLnode && node_rm->right == NULLnode) return NULLnode;
    // if node has 2 children
    if (node_rm->left != NULLnode && node_rm->right != NULLnode) return in_order_successor(node_rm);
    // if node has 1 child
    if (node_rm->left != NULLnode) return node_rm->left;
    else return node_rm->right;
}

// Red Black Tree ADT functions

// initializes an empty red black tree
void red_black_initialize(RedBlackTree *rbt, CompareFunc compare, DestroyFunc destroy, PrintFunc print)
{
    *rbt = malloc(sizeof(struct red_black_tree));
    assert(*rbt);
    (*rbt)->root = NULLnode;
    (*rbt)->size = 0;
    red_black_set_compare(*rbt, compare);
    red_black_set_destroy(*rbt, destroy);
    red_black_set_print(*rbt, print);
}

// inserts a new item in the right place in the red black tree
void red_black_insert(Pointer item, RedBlackTree rbt)
{
    // create item's node
    rbt_node *node = create_node(item, NULLnode, NULLnode, NULLnode); // Note: parent pointer will be found after inserting node in the tree
    // check if tree is empty
    if (red_black_is_empty(rbt)){
        // insert the root
        rbt->root = node;
        rbt->root->color = BLACK;
        rbt->size++;
        return;
    }
    // pointer parent has the parent of the new node
    rbt_node *parent = NULLnode;
    rbt_node *current = rbt->root;
    // traverse the tree and find the right place to insert the new node
    while (current != NULLnode){
        parent = current;
        int comp_result = rbt->Compare(node->data, current->data);
        if (!comp_result){
            // item already exists, no duplicates are allowed
            free(node);
            return;
        }
        else if (comp_result < 0) current = current->left; // go in left subtree
        else current = current->right; // go in right subtree
    }
    rbt->size++;
    // connect node with parent
    node->parent = parent;
    // find which child of parent is the node; connect to the rbt
    if (rbt->Compare(node->data, parent->data) < 0) parent->left = node;
    else parent->right = node;

    // check for double red issue; loop until completely fixed
    while (node->parent->color == RED){
        // case 1: sibling of parent node is black
        if (find_sibling(node->parent)->color == BLACK){
            // perform trinode restructuring and return
            rbt->root = trinode_restructuring(rbt->root, node, rbt->Compare, 0);
            break;
        }
        // case 2: sibling of parent node is red
        // perform recoloring
        rbt->root = recoloring(rbt->root, node->parent);
        // examine whether new double red issue appeared
        node = node->parent->parent; // new node is the grandparent of the old one
    }
    // assure root's color is black
    rbt->root->color = BLACK;
}

// removes and destroys given item from the red black tree
void red_black_remove(Pointer item, RedBlackTree rbt)
{
    // check if tree is empty
    if (red_black_is_empty(rbt)) return;
    // check if item doesn't exist in the rbt
    rbt_node *node = find_node(rbt->root, item, rbt->Compare);
    if (node == NULL) return;

    rbt_node *head = rbt->root;
    // find node's replacement node
    rbt_node *rep = find_replacement(node);
    // find node's sibling
    rbt_node *sibling = find_sibling(node);

    // case 1: replacement node is a child of the node to be removed
    if ((node->left == rep && node->right == NULLnode) || (node->right == rep && node->left == NULLnode)){
        // perform regular bst deletion and check if double-black problem appeared
        if (node->color != rep->color){
            head = node_remove(head, node, rbt->Destroy);
        }else{ 
            head = node_remove(head, node, rbt->Destroy);
            // double black problem
            head = fix_double_black(head, sibling, rbt->Compare); 
        }
    }else{
    // case 2: replacement node is the in-order successor of the node
        // sibling will become the sibling of the "actual" node to be removed, the replacement node
        sibling = find_sibling(rep);
        // check for double-black problem in the successor node
        if (rep->color == BLACK && find_replacement(rep)->color == BLACK){
            head = node_remove(head, node, rbt->Destroy);
            head = fix_double_black(head, sibling, rbt->Compare);
        }else{
            head = node_remove(head, node, rbt->Destroy);
        }
    }
    rbt->size--;
    // assure root's color is black
    head->color = BLACK;
}

// prints items of the rbt 
void red_black_print(RedBlackTree rbt)
{
    if (rbt->Print == NULL || red_black_is_empty(rbt)) return;
    // print rbt
    print_tree_nodes(rbt->root, rbt->Print);
    printf("\n");
}

// destroys the given rbt by freeing all nodes
void red_black_destroy(RedBlackTree rbt)
{
    if (!red_black_is_empty(rbt)) destroy_nodes(rbt->root, rbt->Destroy);
    free(rbt);
}

// returns the number of elements in the rbt
int red_black_size(RedBlackTree rbt)
{
    return rbt->size;
}

// returns true/false depending on if rbt is empty or not
bool red_black_is_empty(RedBlackTree rbt)
{
    if (!red_black_size(rbt)) return true;
    else return false;
}

// returns true/false based on if given item is found in the rbt or not
bool red_black_search(Pointer item, RedBlackTree rbt)
{
    return find_node(rbt->root, item, rbt->Compare) != NULLnode ? true : false;
}

// returns the root element of the rbt
Pointer red_black_root(RedBlackTree rbt)
{
    return rbt->root->data;
}

// returns the smallest/element with min key of the rbt
Pointer red_black_min(RedBlackTree rbt)
{
    if (red_black_is_empty(rbt)) return NULLnode;
    rbt_node *min = rbt->root;
    while (min->left != NULLnode) min = min->left;
    return min->data;
}

// returns the largest/element with max key of the rbt
Pointer red_black_max(RedBlackTree rbt)
{
    if (red_black_is_empty(rbt)) return NULLnode;
    rbt_node *max = rbt->root;
    while (max->right != NULLnode) max = max->right;
    return max->data;
}

// sets as new CompareFunc of rbt the given one
void red_black_set_compare(RedBlackTree rbt, CompareFunc compare)
{
    rbt->Compare = compare;
}

// sets as new DestroyFunc of rbt the given one
void red_black_set_destroy(RedBlackTree rbt, DestroyFunc destroy)
{
    rbt->Destroy = destroy;
}

// sets as new PrintFunc of rbt the given one
void red_black_set_print(RedBlackTree rbt, PrintFunc print)
{
    rbt->Print = print;
}