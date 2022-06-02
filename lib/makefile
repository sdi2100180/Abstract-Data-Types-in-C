# Makefile used to compile the libADT.a

# path to the modules directory
MODULES = ../modules/

# compiler
CC = gcc

# compiler options
CFLAGS = -Wall -Werror -g

# library
LIB = libADT.a

# .o files
OBJS = $(MODULES)BinarySearchTree/BinarySearchTree.o $(MODULES)CircularList/CircularList.o $(MODULES)Deque/Deque.o $(MODULES)PriorityQueue/PriorityQueue.o $(MODULES)Queue/Queue.o $(MODULES)RedBlackTree/RedBlackTree.o $(MODULES)Stack/Stack.o

# create the library
lib: $(OBJS)
	ar rcs $(LIB) $(OBJS)
	rm -f $(OBJS)

clean:
	rm -f $(LIB)