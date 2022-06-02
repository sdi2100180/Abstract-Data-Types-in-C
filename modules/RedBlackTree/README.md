<h1 align="center">Red Black Tree</h1>

A [Red-Black Tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) is a binary search tree with nodes colored red and black in a way that
satisfies the following properties:
- The root is black.
- Every external node is black.
- The children of a red node are black.
- All the external nodes have the same
**black depth**, defined as the number of black ancestors
minus one (recall that a node is an ancestor of itself).

<img align="right" src="https://static.javatpoint.com/core/images/red-black-tree-java.png" width=350 >
  
## Complexity
Algorithm | Amortized  | Worst case
---------- |---------- | ----------
Space	  | O(n) | O(n)
Insert	 | O(1)  | O(logn)
Remove	  | O(1) | O(logn)
Search | O(logn) | O(logn)
