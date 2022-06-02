<h1 align="center">Circular List</h1>

A [Circular List](https://en.wikipedia.org/wiki/Linked_list#Circular_linked_list) is an Abstract Data Type which is
a linear collection of data elements whose order is not given by their physical placement in memory. Instead, each element points to the next.
The main difference from a normal linked-list is the fact that the last node points back to the first list node, thus creating a "circle".
Access to the list is provided through a special node called cursor. The cursor can be considered "the first" list node. Insertions and Removals happen to the node right after the cursor.

<img align="right" src="https://cdn.programiz.com/sites/tutorial2program/files/circular-linked-list.png" width=500 >

## Complexity
Algorithm  | Worst case
---------- | ----------
Space	   | O(n)
Insert	   | O(1)
Remove	   | O(1)
